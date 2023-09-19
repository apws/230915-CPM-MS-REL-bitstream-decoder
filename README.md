# 230915-CPM-MS-REL-bitstream-decoder

rel2relb.c IN.rel OUT.relb - converts REL bitstream to bytestream

relb2relt.c IN.relb OUT.relt - converts REL bytestream to quickly drafted text format according to spec

- currently, I think will make these integrated using single tmp file and to be really useable as REL comparison tool will be good to have normalized symbol tables by sorting them; then its easy to do automated comparisons;

---

example result is mostly in BIOSKRNL.RELT

---

REL file specification
https://seasip.info/Cpm/rel.html

- tried to name items by common asm/linker terms, not sure yet
- *Rx   is easily findable
- *Sxxx is easily findable


 - 00 *RB nn         - Regular Byte
 - 01 *RP nnnn       - Regular Program relative
 - 02 *RD nnnn       - Regular Data relative
 - 03 *RC nnnn       - Regular Common relative


 - 00 *SGLOBAL aaaaaaaa    - symbol declaration (at the module begin)
 - 01 *SCOMMON aaaaaaaa    - common block start/name
 - 02 *SMODULE aaaaaaaa    - module start/name

 - 03 *S3 UNUSED
 - 04 *S4 UNUSED

 - 05 *SCOMMSIZE t nnnn aaaaaaaa   - common block size
 - 06 *SEXTERN t nnnn aaaaaaaa     - "EXTRN" in symbol table (at the module end)
 - 07 *SPUBLIC t nnnn aaaaaaaa     - "PUBLIC" in symbol table (at the module end)

 - 08 *S8 UNUSED

 - 09 *SOFFSET t nnnn      - offset for next chained 16bit item
 - 10 *SDATASIZE t nnnn    - data section/segment size
 - 11 *SSECTION t nnnn     - section begin (P=cseg, D=dseg, A=aseg)
 - 12 *SLOCAL t nnnn       - ??? ... never shown in CP/M file, yet; purpose?
 - 13 *SCODESIZE t nnnn    - code/text section/segment size
 - 14 *SEND t nnnn         - module end
 - 15 *SEOF                - ??? ... never shown in CP/M file; something unclear? diffs after *SEND !


---

interesting resource, Nestor80 assmebler in C#:
https://github.com/Konamiman/Nestor80/blob/master/docs/LanguageReference.md


yes, here is REL format described in greater detail, as Nestor80 bases on it:
https://github.com/Konamiman/Nestor80/blob/master/docs/RelocatableFileFormat.md


also interesting resource about REL + PRL / SPR support in z88dk:
https://github.com/z88dk/z88dk/issues/935###


next interesting generic support in FUZIX:
https://github.com/EtchedPixels/FUZIX/issues/649


LINKPRL simple linker, maybe rather directly in ASMX? target FUZIX?
http://www.znode51.de/articles/tcj/hal/linkprl.txt


rel2z80 tool:
https://github.com/z88dk/z88dk/issues/243


MISOSYS UNREL tool:
https://www.tim-mann.org/trs80/doc/unrel.pdf


something slightly related to banking/pages in RomWBW:
https://github.com/wwarthen/RomWBW/issues/131


