#include "BetaScope_Driver/include/BetaScope_Class.h"
#include "BetaScope_Driver/include/BetaScope_AnaFramework.h"
#include "Colorful_Cout/include/Colorful_Cout.h"


void BetaScope_AnaFramework::initialize( std::string addBranches, std::string rawBranches )
{
  beta_scope.rawTreeReader();
  beta_scope.newTreeMaker( addBranches );
}

void BetaScope_AnaFramework::loopEvents( )
{
  while( beta_scope.treeReader->Next())
  {
    //user put analysis codes here. This method will loop through all the events.

    BetaScope_AnaFramework::copyBranch();

    BetaScope_AnaFramework::filldata();
  }
}

void BetaScope_AnaFramework::filldata()
{
  this->event_counter++;
  beta_scope.fillEvent();
  if(this->event_counter%1000==0 || (this->event_counter%10==0 && this->event_counter <= 100) )
  {
    ColorCout::print( "   "+beta_scope.ifileNickName, " Proccessed events: "+std::to_string(this->event_counter)+" /" + std::to_string(beta_scope.numEvent), BOLDYELLOW);
  }
}

void BetaScope_AnaFramework::finalize()
{
  beta_scope.fileIO_Close();
}


void BetaScope_AnaFramework::copyBranch()
{
  for( int b = 0, max_b = beta_scope.channel.size(); b < max_b; b++ )
  {
    for(int i = 0, maxPnt = beta_scope.iTreeDoubleArrayMap[Form("w%d",beta_scope.channel.at(b))]->GetSize() ; i < maxPnt; i++)
    {
      //std::cout<<itreeReaderBranch[Form("w%d",this->channel.at(b))]->At(i)<<std::endl;
      beta_scope.oTreeVecDoubleMap[Form("w%d",beta_scope.channel.at(b))]->push_back( beta_scope.iTreeDoubleArrayMap[Form("w%d",beta_scope.channel.at(b))]->At(i) * 1000.0 );
      //std::cout<<this->vecDoubleBranch[Form("w%d",this->channel.at(b))][i]<<std::endl;
      beta_scope.oTreeVecDoubleMap[Form("t%d",beta_scope.channel.at(b))]->push_back( beta_scope.iTreeDoubleArrayMap[Form("t%d",beta_scope.channel.at(b))]->At(i) * 1.0e12 );
    }
  }
}
