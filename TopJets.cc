// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/PromptFinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"


namespace Rivet {


  /// @brief Add a short analysis description here
  class TopJets : public Analysis {
  public:

    /// Constructor
    RIVET_DEFAULT_ANALYSIS_CTOR(TopJets);


    /// @name Analysis methods
    /// @{

    /// Book histograms and initialise projections before the run
    void init() {

      // Initialise and register projections

      // The basic final-state projection:
      // all final-state particles within
      // the given eta acceptance
      const VisibleFinalState vfs(Cuts::abseta < 2.5 && Cuts::pT > 1*GeV);

      PromptFinalState prompt(vfs);
      prompt.acceptTauDecays(true);

      IdentifiedFinalState photons(prompt);
      photons.acceptIdPair(PID::PHOTON);

      IdentifiedFinalState electrons(prompt);
      electrons.acceptIdPair(PID::ELECTRON);

      IdentifiedFinalState muons(prompt);
      muons.acceptIdPair(PID::MUON);

      Cut leptoncuts = Cuts::abseta < 2.5 && Cuts::pT > 25*GeV;

      DressedLeptons dressedelectrons(photons, electrons, 0.1, leptoncuts);
      declare(dressedelectrons, "dressedelectrons");

      DressedLeptons dressedmuons(photons, muons, 0.1, leptoncuts);
      declare(dressedmuons, "dressedmuons");


      VetoedFinalState jetfs(vfs);
      jetfs.addVetoOnThisFinalState(dressedelectrons);
      jetfs.addVetoOnThisFinalState(dressedmuons);

      FastJets jets
        ( jetfs
        , FastJets::ANTIKT
        , 1.0
        , JetAlg::Muons::ALL, JetAlg::Invisibles::ALL
        );

      declare(jets, "jets");


      csv = ofstream();
      csv.open("ttbar.csv");

      jetnumber = 0;

      csv
        << "jetnumber"
        << " , "
        << "pdgid"
        << " , "
        << "charge"
        << " , "
        << "px"
        << " , "
        << "py"
        << " , "
        << "pz"
        << endl;

      return;
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {

      // Retrieve dressed leptons, sorted by pT
      const Jets& jets = apply<FastJets>(event, "jets").jetsByPt(250*GeV);

      if (!jets.size()) vetoEvent;

      // only look at the leading jet
      const Jet& jet = jets.at(0);

      for (const Particle& part : jet.constituents()) {
        csv
          << jetnumber
          << " , "
          << part.pid()
          << " , "
          << part.charge3()
          << " , "
          << part.px()/GeV 
          << " , "
          << part.py()/GeV
          << " , "
          << part.pz()/GeV
          << endl;
      }

      jetnumber++;
    }


    /// Normalise histograms etc., after the run
    void finalize() { csv.close(); }


    /// @}

    private:
      ofstream csv;
      int jetnumber;

  };


  RIVET_DECLARE_PLUGIN(TopJets);

}
