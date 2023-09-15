# 230915-CPM-MS-REL-bitstream-decoder

rel2relb.c IN.rel OUT.relb - converts REL bitstream to bytestream

relb2relt.c IN.relb OUT.relt - converts REL bytestream to quickly drafted text format according to spec

---

example result on CPMLDR.REL:

SN2 CPMLDR

SVA A 0000

SVD P BD1E

RB 3E

RB 0F

RB D3

RB 10

RB 11

...

...

RB 02

RB 82

RB 00

RB 84

RB F5

RB 87

SVN6 P 1812 @MXTPA

SVE A 0000

RB 04

RC 8000

RB 00

RB 00

---

REL file specification
https://seasip.info/Cpm/rel.html

- special items not named logically, only by format and number !!!
- NOT CLEAR HOW TO NAME THEM ALL
- Rx is easily findable
- Sx is easily findable


RB nn         - Regular Byte

RP nnnn       - Regular Program relaive

RD nnnn       - Regular Data relative

RC            - Regular Common relative


SN0 aaaaaaaa  - Special Name

SN1 aaaaaaaa  -

SN2 aaaaaaaa  -

SE3 UNUSED

SE4 UNUSED

SVN5 t nnnn aaaaaaaa - Special Value Name

SVN6 t nnnn aaaaaaaa - 

SVN7 t nnnn aaaaaaaa - 

SE8 UNUSED

SV9 t nnnn    - Special Value

SVA t nnnn    -

SVB t nnnn    -

SVC t nnnn    -

SVD t nnnn    -

SVE t nnnn    -

SVF t nnnn    -
