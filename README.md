# PCBench

PCBench is a free open-source benckmark for board-level hardware attacks and Trojans.

## What's News

## Motivation
Most modern electronic systems are hosted by printed circuit boards(PCBs), making them a ubiquitous system component that can take many different shapes and forms. In order to achieve a high level of economy of scale, the global supply chain of electronic systems has evolved into disparate segments for the design, fabrication, assembly, and testing of PCB boards and their various associated components. 
As a consequence, the modern PCB supply chain exposes many vulnerabilities along its different stages, allowing adversaries to introduce malicious alterations to facilitate board-level attacks. As an emerging hardware threat, the attack and defense techniques at the board level have not yet been systemically explored and thus require a thorough and comprehensive investigation. 
In the absence of a standard board-level attack benchmark, current re-search on perspective countermeasures is likely to be evaluated on proprietary variants of ad-hoc attacks, preventing credible and verifiable comparison among different techniques. Upon this request, we have created the PCBench, which is a set of board-level attack benchmarks for open-source release.

## Benchmarking Methodology

We generated the benchmarks based on the methodology proposed in our 2021'ASP-DAC paper: [PCBench: Benchmarking of Board-Level Hardware Attacks and Trojans]().
In this paper, we systematically defined and categorize a broad range of board-level attacks. 
For the first time, the attack vectors and construction rules for board-level attacks are developed.
A practical and reliable board-level attack benchmark generation scheme is also developed, which can be used to produce references for evaluating countermeasures. 

## Released Benchmarks


## Contributiors
The PCBench is mainly developed by Huifeng Zhu and Dr.Silvia Zhang from Washington University in St.Louis; Dr.Yier Jin from the University of Florida; and Dr.Xiaolong Guo from Kansas State University.

We also appreciate the efforts of below contributors: 

## How to Refer to PCBench?
If you are using the benchmarks provided in PCBench to develop either threat mitigation methods or new threat exploitations, please cite our official paper of PCBench. 
You can find the paper in the website of IEEE:.
A typical BibTeX citation would be, for example:
```
@software{PySpice,
  author = {Fabrice Salvaire}, % actual author and maintainer
  title = {PySpice},
  url = {https://pyspice.fabrice-salvaire.fr},
  version = {x.y},
  date = {yyyy-mm-dd}, % set to the release date
}
```
## Get Feedback
Feel free to contact us if you have questions about PCBench: **Huifeng Zhu(zhuhuifeng@wustl.edu)**.

## License
