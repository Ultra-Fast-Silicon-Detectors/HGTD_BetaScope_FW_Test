#include "ArgoneXrayAna.h"

void ArgoneXrayAna::initialize( )
{
  this->beta_scope.fileIO_Open( this->ifile.c_str() );
  BetaScope_AnaFramework::initialize( "/home/yuzhan/HGTD_BetaScope_FW_Test/BetaScope_Ana/ArgoneXrayAna/AnaTemplate/myOwnTree.ini" );

  //do your own stuffs here
  for(int ch = 0; ch < 16; ch++)
  {
    auto br_check = simple_readBranch( this->beta_scope, "TTreeReaderArray<double>", Form("w%i",ch), Form("w%i",ch) );

    br_check = makeBranch<std::vector<double>>(this->beta_scope.oTree, Form("w%i", ch ), Form("w%i", ch ), &this->beta_scope.oTreeVecDoubleMap, this->beta_scope.oTreeVecDouble[this->beta_scope.newBranchCounterKeeper], this->beta_scope.newBranchCounterKeeper, &this->beta_scope.oTreeVecDoubleMapIndex, this->beta_scope.newBranchCounterKeeper );
    this->beta_scope.oTreeVecDouble[this->beta_scope.newBranchCounterKeeper-1]->reserve(1000000);

    if(ch==0){ br_check = simple_readBranch( this->beta_scope, "TTreeReaderArray<double>", "t", "t"); }
  }

}

void ArgoneXrayAna::loopEvents()
{
  while( this->beta_scope.treeReader->Next() )
  {
    for(int ch = 0; ch < 16; ch++)
    {
      for(int i = 0; i < this->beta_scope.iTreeDoubleArrayMap[Form("w%i",ch)]->GetSize(); i++)
      {
        this->beta_scope.oTreeVecDoubleMap[Form("w%i",ch)]->push_back( this->beta_scope.iTreeDoubleArrayMap[Form("w%i",ch)]->At(i) );
      }
    }

    for(int i = 0; i < this->beta_scope.iTreeDoubleArrayMap["t"]->GetSize(); i++)
    {
      this->beta_scope.oTreeVecDoubleMap["Time"]->push_back( this->beta_scope.iTreeDoubleArrayMap["t"]->At(i) );
    }







    BetaScope_AnaFramework::filldata();
  }
}

void ArgoneXrayAna::finalize()
{
  //do your own stuffs here


  BetaScope_AnaFramework::finalize();
}
