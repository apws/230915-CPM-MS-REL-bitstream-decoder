# 230915-CPM-MS-REL-bitstream-decoder

rel2relb.c IN.rel OUT.relb - converts REL bitstream to bytestream

relb2relt.c IN.relb OUT.relt - converts REL bytestream to quickly drafted text format according to spec

---

example result is in CPMLDR.RELT and BIOSKRNL.RELT

---

REL file specification
https://seasip.info/Cpm/rel.html

- SOME special items not named logically, only by format and number !!!
- SOME named, somehow, but NOT CLEAR HOW TO NAME THEM ALL
- *Rx   is easily findable
- *Sxxx is easily findable


*RB nn         - Regular Byte
*RP nnnn       - Regular Program relaive
*RD nnnn       - Regular Data relative
*RC nnnn       - Regular Common relative

*SPUBLIC aaaaaaaa    - ???

*SCOMMON aaaaaaaa    - ???

*SMODULE aaaaaaaa    - ???


*SE3 UNUSED

*SE4 UNUSED


*SCSIZE t nnnn aaaaaaaa    - ???

*SEXTRN t nnnn aaaaaaaa    - ???

*SPENTRY t nnnn aaaaaaaa   - ???


*SE8 UNUSED


*SEOFFSET t nnnn     - ???

*SDSIZE t nnnn       - ???

*SLOCATION t nnnn    - ???

*SVC t nnnn          - ???

*SMSIZE t nnnn       - ???

*SMEND t nnnn        - ???

*SEOF                - ???

