// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/VisibleFinalState.hh"

namespace Rivet {


  /// @brief Add a short analysis description here
  class Pileup : public Analysis {
  public:

    /// Constructor
    RIVET_DEFAULT_ANALYSIS_CTOR(Pileup);


    /// @name Analysis methods
    /// @{

    /// Book histograms and initialise projections before the run
    void init() {

      // Initialise and register projections

      // The basic final-state projection:
      // all final-state particles within
      // the given eta acceptance
      const VisibleFinalState vfs(Cuts::abseta < 2.5 && Cuts::pT > 1*GeV);
      declare(vfs, "VisibleFinalState");

      csv = ofstream();
      csv.open("Pileup.csv");

      evtnumber = 0;

      csv
        << "eventnumber"
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
      const Particles& particles =
        apply<VisibleFinalState>(event, "VisibleFinalState").particles();

      for (const Particle &part : particles) {
        csv
          << evtnumber
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

      evtnumber++;
    }


    /// Normalise histograms etc., after the run
    void finalize() { csv.close(); }


    /// @}

    private:
      ofstream csv;
      int evtnumber;

  };


  RIVET_DECLARE_PLUGIN(Pileup);

}
