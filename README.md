# Arduino-ALEX

#### Arduino implementation of ALEX: Alternating Laser Excitation to synchronize illumination of two diode lasers with the exposure of an EMCCD camera in an interleaved manner.

This is the source code repository for the Arduino-ALEX firmware. The firmware was used in the following articles:

- [Article 1 Title](http://XX)
- [Article 2 Title](http://XX)

1. Article 1 Description
2. Article 2 Description

### FAQ

**Q: What is ALEX?**  
**A:** Refer to the [Original article](https://pubs.acs.org/doi/10.1021/ar0401348).

**Q: Why DIY ALEX using Arduino?**  
**A:** Most camera-based fluorescence microscopes are equipped with EMCCD and diode lasers, which can be digitally modulated. However, electronics to synchronize these components are not always available to the end user and could cost thousands of USD. In this implementation, the FIRE signal TTL (high) from the EMCCD is used to switch on the laser for a certain on-time (user-defined), bypassing the need for external clocking using an Arduino board (costing less than a hundred USD).

**Q: How to use the source code?**  
**A:** Assemble the Arduino board, install the firmware, and follow the instructions provided in the repository or [Article 3 Title](http://XX).
