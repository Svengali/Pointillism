


#pragma once


#include <thread>
#include <atomic>
#include <vector>
#include <string>





namespace ORB_SLAM2
{
class System;
}

namespace cv
{
class Mat;
}



class Orb
{
public:
	enum class EState
	{
		Invalid,
		Ready,
		LoadingVocab,
		Processing,
		Done,
	};



public:
	Orb();

	void start();
	void run();






	std::atomic<EState>	m_state = EState::Invalid;
	std::unique_ptr<std::thread> m_processing;


	std::unique_ptr<ORB_SLAM2::System> m_slam;

	std::vector<std::string> m_strImageFilenames;
	std::vector<double> m_timestamps;

	std::vector<cv::Mat> m_cameraPose;

	std::atomic<int> m_curFrame = 0;


};

