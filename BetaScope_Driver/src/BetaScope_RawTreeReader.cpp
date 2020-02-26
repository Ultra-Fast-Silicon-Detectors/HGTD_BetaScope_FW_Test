#include "BetaScope_Driver/include/BetaScope_Class.h"
#include "BetaScope_Driver/include/BetaScope_Templates.h"

#include <iostream>
#include <string>

#include <TThread.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

bool BetaScope::RawTreeReader(const char *itreeName) {
  std::string cout_prefix = "BetaScope::RawTreeReader => ";
  logger.info(__func__, "Entering");
  logger.info(__func__, "Preparing raw tree reader.");

  this->input_tree_reader_ = new TTreeReader(itreeName, this->input_tfile_);
  this->input_num_event_ = this->input_tree_reader_->GetEntries(true);

  logger.info( __func__, "Number of events: " + std::to_string(this->input_num_event_));

  logger.info(__func__, "Looping through raw scope channels.");

  // int branch_counter = 0;
  bool br_check;

  for (int b = 1, max = 5; b < max; b++) {
    bool isBranch = BetaScope::IsBranchExists(Form("t%i", b));
    if (isBranch)
    {
      br_check = BetaScope::SetInBranch<TTreeReaderArray, double>( Form("w%i", b), Form("w%i", b));
      br_check = BetaScope::SetInBranch<TTreeReaderArray, double>( Form("t%i", b), Form("t%i", b));
      this->channel.push_back(b);
    }
  }

  logger.info(__func__, "Finished, exiting");

  return true;
}
