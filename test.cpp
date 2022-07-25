// Uncomment the following line if you are compiling this code in Visual Studio

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <thread>
#include <mutex>

using namespace cv;
using namespace std;

mutex M1,M2;

void open_camera(shared_ptr<Mat> frame)
{
    M1.lock();
    // Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        cin.get(); // wait for any key press
    }

    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);   // get the width of frames of the video
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
    int i = 0;
    while (true)
    {
        bool bSuccess = cap.read(*frame); // read a new frame from video
        cv::putText(*frame, to_string(i), cv::Point(250, 250), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(100, 255, 100), 2, false);
        if (bSuccess == true)
            i++;
        // Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get(); // Wait for any key press
            break;
        }
        M2.unlock();
    }
}

void show_screen(shared_ptr<Mat> frame)
{
    
    string window_name = "My Camera Feed";
    namedWindow(window_name); // create a window called "My Camera Feed"
    while (true)
    {
        M2.lock();
        if (frame == nullptr)
        {
            cout << "No photo read\n";
            M1.unlock();
        }
        else if (frame->empty())
        {
            cout << "No photo read\n";
            M1.unlock();
        }
        else
        {
            // show the frame in the created window
            imshow(window_name, *frame);
            // wait for for 10 ms until any key is pressed.
            // If the 'Esc' key is pressed, break the while loop.
            // If the any other key is pressed, continue the loop
            // If any key is not pressed withing 10 ms, continue the loop
            if (waitKey(10) == 27)
            {
                cout << "Esc key is pressed by user. Stoppig the video" << endl;
                exit(EXIT_FAILURE);
            }
            M1.unlock();
        }
    }
}
int main(int argc, char *argv[])
{
    M2.lock();
    shared_ptr<Mat> frame = make_shared<Mat>();
    thread camera(open_camera, frame);
    thread screen(show_screen, frame);
    camera.join();
    screen.join();

    return 0;
}
