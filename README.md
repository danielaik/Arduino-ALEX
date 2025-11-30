# Arduino-ALEX

Arduino implementation of ALEX (Alternating Laser Excitation) to synchronize illumination of two diode lasers with the exposure of an EMCCD (camera as master) in an interleaved manner. Note that using microcontroller for timing is not recommended for <100 µs precision, but fine for ms-control.

This is the source code repository for the Arduino-ALEX firmware. The firmware was initially designed and used for:

- [Aik, D. Y. K. (2023). Real-Time Measurements of Biological Membrane Dynamics by Imaging Fluorescence Correlation and Cross-Correlation Spectroscopy (Doctoral dissertation, National University of Singapore (Singapore)).](https://www.proquest.com/openview/b4090bb22008e01606fd059c08726425/1?cbl=2026366&diss=y&pq-origsite=gscholar)

- [Wohland, T., & Aik, D. (2024). Transmembrane bilayer coupling in live cell—an Alex-imaging FCCS study. Biophysical Journal, 123(3), 173a.](<https://www.cell.com/biophysj/fulltext/S0006-3495(23)01844-1>)

- [Kamal Kant SHARMA, Palur Venkata Raghuvamsi, Daniel Y. K. Aik et al. Structural flexibility in the ordered domain of the dengue virus strain 2 capsid protein is critical for chaperoning viral RNA replication, 05 February 2025, PREPRINT (Version 1) available at Research Square [https://doi.org/10.21203/rs.3.rs-5869980/v1]](https://www.researchsquare.com/article/rs-5869980/v1)

## FAQ

**Q: What is ALEX?**  
**A:** Refer to [Kapanidis AN, Laurence TA, Lee NK, Margeat E, Kong X, Weiss S. Alternating-laser excitation of single molecules. Acc Chem Res. 2005.](https://pubs.acs.org/doi/10.1021/ar0401348)

**Q: Why DIY ALEX using Arduino?**  
**A:** Most camera-based fluorescence microscopes are equipped with EMCCD and diode lasers, which can be digitally modulated. However, electronics to synchronize these components are not always available to the end user and could cost thousands of USD. In this implementation, the FIRE signal TTL (high) from the EMCCD is used to switch on the laser for a certain on-time (user-defined), bypassing the need for external clocking using an Arduino board (costing less than a hundred USD).

**Q: How do I use the source code?**  
**A:** You will need to assemble the Arduino board, install the firmware, and follow the instructions provided in this repository.

## If you find it useful

The code is licensed under the GNU General Public License (GPL). If this repo significantly influenced your work, do:

- Include the original license (e.g., LICENSE file).
- Include the copyright notice of the original author(s).
- Disclose your own source code if you distribute the combined/modified work.
- Ideally, acknowledge the original repo in your README or documentation, e.g., **_This project uses code from [Arduino-ALEX](https://github.com/danielaik/Arduino-ALEX), licensed under the GNU General Public License v3.0._**
