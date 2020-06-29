/*
 *  Copyright 2019-2020 Diligent Graphics LLC
 *  Copyright 2015-2019 Egor Yusov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  In no event and under no legal theory, whether in tort (including negligence),
 *  contract, or otherwise, unless required by applicable law (such as deliberate
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental,
 *  or consequential damages of any character arising as a result of this License or
 *  out of the use or inability to use the software (including but not limited to damages
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and
 *  all other commercial damages or losses), even if such Contributor has been advised
 *  of the possibility of such damages.
 */

#include "stdafx.h"
#include "ImguiDemo.hpp"
#include "imgui.h"


namespace Diligent
{

SampleBase *CreateSample()
{
	return new ImguiDemo();
}

ImguiDemo::~ImguiDemo()
{
}

void ImguiDemo::Initialize( const SampleInitInfo &InitInfo )
{
	SampleBase::Initialize( InitInfo );

	m_orb.start();

}

void ImguiDemo::UpdateUI()
{
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (m_ShowDemoWindow)
		//    ImGui::ShowDemoWindow(&m_ShowDemoWindow);


		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin( "Processing" ); // Create a window called "Hello, world!" and append into it.

		const auto currentFrame = m_orb.m_curFrame.load();
		const auto state = m_orb.m_state.load();

		ImGui::Text( "Current frame %i", currentFrame );
		ImGui::Text( "State %i", state );







		ImGui::End();
	}

	// 3. Show another simple window.
	if( m_ShowAnotherWindow )
	{
		ImGui::Begin( "Another Window", &m_ShowAnotherWindow ); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text( "Hello from another window!" );
		if( ImGui::Button( "Close Me" ) )
			m_ShowAnotherWindow = false;
		ImGui::End();
	}
}

// Render a frame
void ImguiDemo::Render()
{
	auto *pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
	m_pImmediateContext->ClearRenderTarget( pRTV, &m_ClearColor.x, RESOURCE_STATE_TRANSITION_MODE_TRANSITION );

}


void ImguiDemo::Update( double CurrTime, double ElapsedTime )
{
	SampleBase::Update( CurrTime, ElapsedTime );

	UpdateUI();

	const auto currentFrame = m_orb.m_curFrame.load();

	if( currentFrame > m_lastProcessedFrame )
	{
    const auto curKeyframe = m_orb.m_slam->mpMap->KeyFramesInMap();

    for( auto kfIndex = m_lastProcessedKeyframe; kfIndex < curKeyframe; ++kfIndex )
    {
      auto kf = m_orb.m_slam->mpMap->GetKeyFrame( kfIndex );

      const auto id = kf->mnId;

      auto mapPoints = kf->GetMapPoints();
      for( auto mp : mapPoints )
      {
        const auto worldPos = mp->GetWorldPos();


      }

      m_lastProcessedKeyframe = curKeyframe;
    }
  }

}






/*
    cv::Mat im;
    vector<cv::KeyPoint> vIniKeys; // Initialization: KeyPoints in reference frame
    vector<int> vMatches; // Initialization: correspondeces with reference keypoints
    vector<cv::KeyPoint> vCurrentKeys; // KeyPoints in current frame
    vector<bool> vbVO, vbMap; // Tracked MapPoints in current frame
    int state; // Tracking state

    //Copy variables within scoped mutex
    {
        unique_lock<mutex> lock(mMutex);
        state=mState;
        if(mState==Tracking::SYSTEM_NOT_READY)
            mState=Tracking::NO_IMAGES_YET;

        mIm.copyTo(im);

        if(mState==Tracking::NOT_INITIALIZED)
        {
            vCurrentKeys = mvCurrentKeys;
            vIniKeys = mvIniKeys;
            vMatches = mvIniMatches;
        }
        else if(mState==Tracking::OK)
        {
            vCurrentKeys = mvCurrentKeys;
            vbVO = mvbVO;
            vbMap = mvbMap;
        }
        else if(mState==Tracking::LOST)
        {
            vCurrentKeys = mvCurrentKeys;
        }
    } // destroy scoped mutex -> release mutex

    if(im.channels()<3) //this should be always true
        cvtColor(im,im, cv::ColorConversionCodes::COLOR_GRAY2BGR);

    //Draw
    if(state==Tracking::NOT_INITIALIZED) //INITIALIZING
    {
        for(unsigned int i=0; i<vMatches.size(); i++)
        {
            if(vMatches[i]>=0)
            {
                cv::line(im,vIniKeys[i].pt,vCurrentKeys[vMatches[i]].pt,
                        cv::Scalar(0,255,0));
            }
        }
    }
    else if(state==Tracking::OK) //TRACKING
    {
        mnTracked=0;
        mnTrackedVO=0;
        const float r = 5;

        const auto frameCount = vbVO.size();

        for(int i=0;i<frameCount;i++)
        {
            if(vbVO[i] || vbMap[i])
            {
                cv::Point2f pt1,pt2;
                pt1.x=vCurrentKeys[i].pt.x-r;
                pt1.y=vCurrentKeys[i].pt.y-r;
                pt2.x=vCurrentKeys[i].pt.x+r;
                pt2.y=vCurrentKeys[i].pt.y+r;

                // This is a match to a MapPoint in the map
                if(vbMap[i])
                {
                    cv::rectangle(im,pt1,pt2,cv::Scalar(0,255,0));
                    cv::circle(im,vCurrentKeys[i].pt,2,cv::Scalar(0,255,0),-1);
                    mnTracked++;
                }
                else // This is match to a "visual odometry" MapPoint created in the last frame
                {
                    cv::rectangle(im,pt1,pt2,cv::Scalar(255,0,0));
                    cv::circle(im,vCurrentKeys[i].pt,2,cv::Scalar(255,0,0),-1);
                    mnTrackedVO++;
                }
            }
        }
    }

    cv::Mat imWithInfo;
    DrawTextInfo(im,state, imWithInfo);
*/









void ImguiDemo::WindowResize( Uint32 Width, Uint32 Height )
{
}

} // namespace Diligent


