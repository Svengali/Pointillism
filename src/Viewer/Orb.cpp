



#include "stdafx.h"



#include "Orb.h"

#include "../third_party/ORB_SLAM2_dense/include/System.h"

#include <boost/filesystem.hpp>

//D:\prj\rob\Pointillism\src\Viewer\Orb.cpp
//D:\prj\rob\Pointillism\src\third_party\ORB_SLAM2_dense\include\System.h

#include <../../third_party/ORB_SLAM2_dense/include/System.h>

namespace fs = boost::filesystem;

static const std::string s_vocab = "ORBvoc.txt";
static const std::string s_settings = "settings.txt";
static const std::string s_directory = "backyard";









Orb::Orb()
{
	m_state = EState::Ready;
}

void Orb::start()
{

	m_processing.reset( new std::thread( [this]() { 
		run();
	} ) );

}

void LoadImages( const std::string &strPathToSequence, std::vector<std::string> *pFilenames, std::vector<double> *pTimestamps );


void Orb::run()
{
		// Retrieve paths to images
	LoadImages( s_directory, &m_strImageFilenames, &m_timestamps );

	m_state = EState::LoadingVocab;
	
	m_slam.reset( new ORB_SLAM2::System( s_vocab, s_settings, ORB_SLAM2::System::MONOCULAR, true ) );
	
	m_state = EState::Processing;


	while( m_curFrame < m_strImageFilenames.size() )
	{
		auto im = cv::imread( m_strImageFilenames[m_curFrame], cv::IMREAD_UNCHANGED );
		double tframe = m_timestamps[m_curFrame];

		const auto cam = m_slam->TrackMonocular( im, tframe );

		m_cameraPose.push_back( cam );

		++m_curFrame;
	}

	m_state = EState::Done;


}



void LoadImages( const std::string &strPathToSequence, std::vector<std::string> *pFilenames, std::vector<double> *pTimestamps )
{

	fs::directory_iterator itDir( strPathToSequence );

	double time = 0.0;

	for( ; itDir != fs::directory_iterator(); ++itDir )
	{
		pFilenames->push_back( itDir->path().string() );
		pTimestamps->push_back( time );
		time += 1.0 / 30.0;
	}
}
