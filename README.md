# PCBench

PCBench is a free open-source benckmark for board-level hardware attacks and Trojans.

## What's News

## Motivation
Most modern electronic systems are hosted by printed circuit boards(PCBs), making them a ubiquitous system component that can take many different shapes and forms. In order to achieve a high level of economy of scale, the global supply chain of electronic systems has evolved into disparate segments for the design, fabrication, assembly, and testing of PCB boards and their various associated components. 
As a consequence, the modern PCB supply chain exposes many vulnerabilities along its different stages, allowing adversaries to introduce malicious alterations to facilitate board-level attacks. As an emerging hardware threat, the attack and defense techniques at the board level have not yet been systemically explored and thus require a thorough and comprehensive investigation. 
In the absence of a standard board-level attack benchmark, current re-search on perspective countermeasures is likely to be evaluated on proprietary variants of ad-hoc attacks, preventing credible and verifiable comparison among different techniques. Upon this request, we have created the PCBench, which is a set of board-level attack benchmarks for open-source release.

## Benchmarking Methodology

We generated the benchmarks based on the methodology proposed in our **2021'ASP-DAC paper: *[PCBench: Benchmarking of Board-Level Hardware Attacks and Trojans](http://jin.ece.ufl.edu/papers/ASPDAC2021_PCB.PDF)***.
In this paper, we systematically defined and categorized a broad range of board-level attacks. 
For the first time, the attack vectors and construction rules for board-level attacks were developed.
A practical and reliable board-level attack benchmark generation scheme was also developed, which can be used to produce references for evaluating countermeasures.

## Released Benchmarks
To facilitate the development of board-level attack benchmarks, representative circuit boards are chosen as the victim designs. 
Open-source hardware projects are mainly selected due to their modern design styles, the availability of PCB designs as well as detailed documents, firmware, and/or application software. 
As a result, researchers can easily reconstruct the board-level security evaluation benchmarks. 

**The following table lists the released benchmarks:**

 Design Name | Description | Dimension (mm^2) | No. of Components | No. of Layers
 ----------- | ----------- | :---------: | :-----------------: | :-------------:
 [arduino-due]() | Microcontroller devlopment board based on ATsam3x8e with ARM Cortex-M3 core | 102x53 | 141 | 2
 [a13-olinuxino]() | Single-board Linux computer based on Allwinner-A13 with Cortex-A8 core | 120x120|370|4


*This is not the full list of benchmarks as we continue developing the new benchmarks.* 

## Contributiors
The PCBench is mainly developed by *Huifeng Zhu* and *[Dr.Silvia Zhang](https://xzgroup.wustl.edu/people/xuan-silvia-zhang/)* from *Washington University in St.Louis*; *[Dr.Yier Jin](http://jin.ece.ufl.edu/)* from the *University of Florida*; and *[Dr.Xiaolong Guo](https://www.ece.k-state.edu/people/faculty/guo/)* from *Kansas State University*.

We also appreciate the efforts of below contributors: 

## How to Refer to PCBench?
If you are using the benchmarks provided in PCBench to develop either threat mitigation methods or new threat exploitations, please cite our official paper of PCBench. 
You can find the paper in the website of IEEE: [link]() or at [link](http://jin.ece.ufl.edu/papers/ASPDAC2021_PCB.PDF).

A typical BibTeX citation would be, for example:
```
@software{PCBench,
  author = {Huifeng Zhu and Xiaolong Guo and Yier Jin and Xuan Zhang}, % actual author and maintainer
  title = {PCBench: Benchmarking of Board-Level Hardware Attacks and Trojans},
  booktitle = {26th Asia and South Pacific Design Automation Conference (ASP-DAC)},
  year = {2021},
  url = {https://github.com/xz-group/PCBench},
  version = {1.0},
  date = {2020-10-15}, % set to the release date
}
```
## Get Feedback
Feel free to contact us if you have questions about PCBench: **Huifeng Zhu (zhuhuifeng@wustl.edu)**.

## License
