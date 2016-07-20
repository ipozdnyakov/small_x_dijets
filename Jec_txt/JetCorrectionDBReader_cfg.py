
import FWCore.ParameterSet.Config as cms
process = cms.Process("jectxt")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# define your favorite global tag
#process.GlobalTag.globaltag = '76X_dataRun2_v15'
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v8'

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source("EmptySource")
process.readJEC    = cms.EDAnalyzer('JetCorrectorDBReader',  

      # below is the communication to the database 
      payloadName    = cms.untracked.string('ak4PFJetsCHS'),

      # this is used ONLY for the name of the printed txt files. You can use any name that you like, 
      # but it is recommended to use the GT name that you retrieved the files from.
#      globalTag      = cms.untracked.string('76X_dataRun2_v15'),  
      globalTag      = cms.untracked.string('80X_dataRun2_Prompt_v8'),  
      printScreen    = cms.untracked.bool(False),
      createTextFile = cms.untracked.bool(True)
)
process.p = cms.Path(process.readJEC )
