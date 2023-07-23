# Instructions for Analyzing Particle Physics CSV Data

The goal is to analyze particle data from simulated pileup and ttbar events. There are two CSV files provided:

## pileup.csv

- A CSV file containing simulated "pileup" events. Pileup refers to multiple proton-proton collisions within a single beam crossing.

- Each line represents a single particle with $p_T > 1$ GeV and $|η| < 2.5$

- Columns:
  - `event_number`: The event ID 
  - `pdg_id`: The PDG particle ID
  - `charge`: The particle charge
  - `px`: x-component of momentum 
  - `py`: y-component of momentum
  - `pz`: z-component of momentum

- If `event_number` is missing, there was no particle reconstruction for that event. These "missing" events should still be accounted for in analyses.

- Example rows:
```
event_number,pdg_id,charge,px,py,pz
12345,211,-1,0.5,0.3,-0.2
12345,321,1,1.0,-0.5,0.0
23456,11,0,0.2,0.1,0.3
```


## ttbar.csv 

- A CSV file containing simulated jets from ttbar events. ttbar refers to top quark-antiquark pair production.

- Each line represents a single particle within a high pT jet ($p_T > 250$ GeV, R=1.0). Particles have $p_T > 1$ GeV and $|η| < 2.5$.

- Columns:
  - `jet_number`: The jet ID
  - `pdg_id`: The PDG particle ID 
  - `charge`: The particle charge
  - `px`: x-component of momentum
  - `py`: y-component of momentum 
  - `pz`: z-component of momentum
  
- Only jets above 250 GeV are included. Events without high pT jets are not represented in the CSV.

- Example rows:
```
jet_number,pdg_id,charge,px,py,pz
1,2212,1,500,0,0
1,-11,0,100,50,80
2,321,-1,350,0,-220
```