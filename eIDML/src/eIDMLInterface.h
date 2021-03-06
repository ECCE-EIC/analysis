#ifndef eIDMLInterface_H__
#define eIDMLInterface_H__

#include <fun4all/SubsysReco.h>

/// Class declarations for use in the analysis module
class Fun4AllHistoManager;
class PHCompositeNode;
class TFile;
class TTree;
class TH1;
class TH2;
class PHCompositeNode;
class RawClusterContainer;
class RawCluster;
class SvtxTrackMap;
class JetMap;
class GlobalVertex;
class PHHepMCGenEventMap;
class JetEvalStack;
class JetRecoEval;
class PHG4TruthInfoContainer;
class PHHepMCGenEvent;
class CaloTriggerInfo;
class JetTruthEval;
class JetEvalStack;
class SvtxEvalStack;

#include <map>
#include <utility>
#include <vector>

/// Definition of this analysis module class
class eIDMLInterface : public SubsysReco
{
 public:
  /// Constructor
  eIDMLInterface(const std::vector<std::string> &names = {"BECAL"},
                 const std::string &fname = "eIDMLInterface.root");

  // Destructor
  virtual ~eIDMLInterface();

  /// SubsysReco initialize processing method
  int Init(PHCompositeNode *);

  /// SubsysReco event processing method
  int process_event(PHCompositeNode *);

  /// SubsysReco end processing method
  int End(PHCompositeNode *);

  /// Set the minimum jet pT to cut on
  void setMinJetPt(float minjetpt) { m_minjetpt = minjetpt; }

  /// Set the minimum cluster pT to cut on
  void setMinClusPt(float mincluspt) { m_mincluspt = mincluspt; }

  /// Set things to analyze
  void analyzeTracks(bool analyzeTracks) { m_analyzeTracks = analyzeTracks; }
  void analyzeClusters(bool analyzeClusters) { m_analyzeClusters = analyzeClusters; }
  void analyzeJets(bool analyzeJets) { m_analyzeJets = analyzeJets; }
  void analyzeTruth(bool analyzeTruth) { m_analyzeTruth = analyzeTruth; }

  void setEtaRange(double min, double max)
  {
    m_etaRange.first = min;
    m_etaRange.second = max;
  }

 private:
  std::pair<double, double> m_etaRange{-.5, .5};
  // eval stack
  SvtxEvalStack *_svtxevalstack = nullptr;
  ;

  std::vector<std::string> _calo_names;

  struct CaloData
  {
    std::vector<float> m_TTree_proj_vec = {0, 0, 0, 0};
    std::vector<float> m_TTree_proj_p_vec = {0, 0, 0};
    static const int m_sizeTowerPatch = 7;
    int nTowerInPatch = m_sizeTowerPatch * m_sizeTowerPatch;
    std::vector<float> m_TTree_Tower_dEta = std::vector<float>(m_sizeTowerPatch * m_sizeTowerPatch, 0);
    std::vector<float> m_TTree_Tower_dPhi = std::vector<float>(m_sizeTowerPatch * m_sizeTowerPatch, 0);
    std::vector<int> m_TTree_Tower_iEta_patch = std::vector<int>(m_sizeTowerPatch * m_sizeTowerPatch, 0);
    std::vector<int> m_TTree_Tower_iPhi_patch = std::vector<int>(m_sizeTowerPatch * m_sizeTowerPatch, 0);
    std::vector<float> m_TTree_Tower_E = std::vector<float>(m_sizeTowerPatch * m_sizeTowerPatch, 0);
    float m_E3x3 = 0;
    float m_E5x5 = 0;
    float m_E7x7 = 0;
    int m_centralTowerBinEta = 0;
    int m_centralTowerBinPhi = 0;

    void initializeVariables();
  };

  std::map<std::string, CaloData> m_CaloDataMap;

  /// String to contain the outfile name containing the trees
  std::string m_outfilename;

  /// Fun4All Histogram Manager tool
  Fun4AllHistoManager *m_hm;

  /// A float for cutting on jet pt
  float m_minjetpt;

  /// A float for cutting on cluster pt
  float m_mincluspt;

  /// A boolean for running over tracks
  bool m_analyzeTracks;

  /// A boolean for running over clusters
  bool m_analyzeClusters;

  /// A boolean for running over jets
  bool m_analyzeJets;

  /// A boolean for collecting hepmc information
  bool m_analyzeTruth;

  /// TFile to hold the following TTrees and histograms
  TFile *m_outfile;
  TTree *m_clustertree;
  TTree *m_tracktree;
  TTree *m_hepmctree;
  TTree *m_truthtree;
  TTree *m_recojettree;
  TTree *m_truthjettree;
  TH1 *m_phi_h;
  TH2 *m_eta_phi_h;

  JetEvalStack *m_jetEvalStack = nullptr;

  /// Methods for grabbing the data
  void getTracks(PHCompositeNode *topNode);
  void getTruthJets(PHCompositeNode *topNode);
  void getReconstructedJets(PHCompositeNode *topNode);
  void getEMCalClusters(PHCompositeNode *topNode);
  void getHEPMCTruth(PHCompositeNode *topNode);
  void getPHG4Truth(PHCompositeNode *topNode);

  void initializeVariables();
  void initializeTrees();

  /**
   * Make variables for the relevant trees
   */

  /// HEPMC Tree variables
  int m_partid1;
  int m_partid2;
  double m_x1;
  double m_x2;
  int m_mpi;
  int m_process_id;
  double m_truthenergy;
  double m_trutheta;
  double m_truthphi;
  double m_truthpx;
  double m_truthpy;
  double m_truthpz;
  double m_truthpt;
  double m_truthp;
  int m_numparticlesinevent;
  int m_truthpid;

  /// Track variables
  double m_tr_px;
  double m_tr_py;
  double m_tr_pz;
  double m_tr_p;
  double m_tr_pt;
  double m_tr_phi;
  double m_tr_eta;
  int m_charge;
  double m_chisq;
  int m_ndf;
  double m_dca;
  double m_tr_x;
  double m_tr_y;
  double m_tr_z;
  float m_tr_pion_loglikelihood;
  float m_tr_kaon_loglikelihood;
  float m_tr_proton_loglikelihood;
  int m_truth_is_primary;
  double m_truthtrackpx;
  double m_truthtrackpy;
  double m_truthtrackpz;
  double m_truthtrackp;
  double m_truthtracke;
  double m_truthtrackpt;
  double m_truthtrackphi;
  double m_truthtracketa;
  int m_truthtrackpid;

  /// Reconstructed jet variables
  double m_recojetpt;
  int m_recojetid;
  double m_recojetpx;
  double m_recojetpy;
  double m_recojetpz;
  double m_recojetphi;
  double m_recojetp;
  double m_recojetenergy;
  double m_recojeteta;
  int m_truthjetid;
  double m_truthjetp;
  double m_truthjetphi;
  double m_truthjeteta;
  double m_truthjetpt;
  double m_truthjetenergy;
  double m_truthjetpx;
  double m_truthjetpy;
  double m_truthjetpz;
  double m_dR;

  /// Cluster variables
  double m_clusenergy;
  double m_cluseta;
  double m_clustheta;
  double m_cluspt;
  double m_clusphi;
  double m_cluspx;
  double m_cluspy;
  double m_cluspz;
  double m_E_4x4;
};

#endif
