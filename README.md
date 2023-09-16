# 230915-CPM-MS-REL-bitstream-decoder

rel2relb.c IN.rel OUT.relb - converts REL bitstream to bytestream

relb2relt.c IN.relb OUT.relt - converts REL bytestream to quickly drafted text format according to spec

---

example result is mostly in BIOSKRNL.RELT

---

REL file specification
https://seasip.info/Cpm/rel.html

- tried to name items by common asm/linker terms, not sure yet
- *Rx   is easily findable
- *Sxxx is easily findable


 - 00 *RB nn         - Regular Byte
 - 01 *RP nnnn       - Regular Program relaive
 - 02 *RD nnnn       - Regular Data relative
 - 03 *RC nnnn       - Regular Common relative


 - 00 *SPUBLIC aaaaaaaa    - ???
 - 01 *SCOMMON aaaaaaaa    - ??? shared? sseg?
 - 02 *SMODULE aaaaaaaa    - ??? module start

 - 03 *S3 UNUSED
 - 04 *S4 UNUSED

 - 05 *SCOMMSIZE t nnnn aaaaaaaa   - ??? shared? sseg?
 - 06 *SEXTRN t nnnn aaaaaaaa      - ???
 - 07 *SGLOBL t nnnn aaaaaaaa      - ???

 - 08 *S8 UNUSED

 - 09 *SOFFSET t nnnn      - ???
 - 10 *SDATSSIZE t nnnn    - ???
 - 11 *SSEG t nnnn         - ???
 - 12 *SLOCAL t nnnn       - ??? (really?)
 - 13 *SCODESIZE t nnnn    - ??? (prog/text ?)
 - 14 *SEND t nnnn         - ??? module end
 - 15 *SEOF                - ???

