/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 18/12/2014                                        */
/************************************************************************/
#include "interrupt_handlers.h"

// Exception(Supervisor Instruction)
void INT_Excep_SuperVisorInst(void) {/* brk(); */}

// Exception(Access Instruction)
void INT_Excep_AccessInst(void) {/* brk(); */}

// Exception(Undefined Instruction)
void INT_Excep_UndefinedInst(void) {/* brk(); */}

// Exception(Floating Point)
void INT_Excep_FloatingPoint(void) {/* brk(); */}

// NMI
void INT_NonMaskableInterrupt(void) {/* brk(); */}

// Dummy
void Dummy(void) {/* brk(); */}

// BRK
void INT_Excep_BRK(void) { /*wait();*/ }
//;0x0000  Reserved

//;0x0004  Reserved

//;0x0008  Reserved

//;0x000C  Reserved

//;0x0010  Reserved

//;0x0014  Reserved

//;0x0018  Reserved

//;0x001C  Reserved

//;0x0020  Reserved

//;0x0024  Reserved

//;0x0028  Reserved

//;0x002C  Reserved

//;0x0030  Reserved

//;0x0034  Reserved

//;0x0038  Reserved

//;0x003C  Reserved

//;0x0040  BUSERR
void  INT_Excep_BSC_BUSERR(void) { }
//;0x0044  Reserved

//;0x0048  RAMERR
void INT_Excep_RAM_RAMERR(void) { }
//;0x004C  Reserved

//;0x0050  Reserved

//;0x0054 FIFERR
void INT_Excep_FCU_FIFERR(void) { }
//;0x0058  Reserved

//;0x005C  FRDYI
void INT_Excep_FCU_FRDYI(void) { }
//;0x0060  Reserved

//;0x0064  Reserved

//;0x0068  SWINT2
void INT_Excep_ICU_SWINT2(void) { }

//;0x006C  SWINT
void INT_Excep_ICU_SWINT(void) { }

//;0x0070  CMI0
extern void timerInterrupt0();
void INT_Excep_CMT0_CMI0(void) {timerInterrupt0();}

//;0x0074  CMI1
extern void timerInterrupt1();
void INT_Excep_CMT1_CMI1(void) {timerInterrupt1();}

//;0x0078  CMWI0
void INT_Excep_CMTW0_CMWI0(void) { }

//;0x007C  CMWI1
void INT_Excep_CMTW1_CMWI1(void) { }

//;0x0080  D0FIFO2
void INT_Excep_USBA_D0FIFO2(void) { }

//;0x0084  D1FIFO2
void INT_Excep_USBA_D1FIFO2(void) { }

//;0x0088  D0FIFO0
void INT_Excep_USB0_D0FIFO0(void) { }

//;0x008C  D1FIFO0
void INT_Excep_USB0_D1FIFO0(void) { }
//;0x0090  Reserved

//;0x0094  Reserved

//;0x0098  SPRI0
void INT_Excep_RSPI0_SPRI0(void) { }

//;0x009C  SPTI0
void INT_Excep_RSPI0_SPTI0(void) { }

//;0x00A0  SPRI1
void INT_Excep_RSPI1_SPRI1(void) { }

//;0x00A4  SPTI1
void INT_Excep_RSPI1_SPTI1(void) { }

//;0x00A8  SPRI
void INT_Excep_QSPI_SPRI(void) { }

//;0x00AC  SPTI
void INT_Excep_QSPI_SPTI(void) { }

//;0x00B0  SBFAI
void INT_Excep_SDHI_SBFAI(void) { }

//;0x00B4  MBFAI
void INT_Excep_MMCIF_MBFAI(void) { }

//;0x00B8  SSITX0
void INT_Excep_SSI0_SSITXI0(void) { }

//;0x00BC  SSIRX0
void INT_Excep_SSI0_SSIRXI0(void) { }

//;0x00C0  SSIRTI1
void INT_Excep_SSI1_SSIRTI1(void) { }
//;0x00C4  Reserved

//;0x00C8  IDEI
void INT_Excep_SRC_IDEI(void) { }

//;0x00CC  ODFI
void INT_Excep_SRC_ODFI(void) { }

//;0x00D0  RXI0
void INT_Excep_RIIC0_RXI0(void) { }

//;0x00D4C  TXI0
void INT_Excep_RIIC0_TXI0(void) { }

//;0x00D8  RXI2
void INT_Excep_RIIC2_RXI2(void) { }

//;0x00DC TXI2
void INT_Excep_RIIC2_TXI2(void) { }
//;0x00E0  Reserved

//;0x00E4  Reserved

//;0x00E8 RXI0
void INT_Excep_SCI0_RXI0(void) { }

//;0x00EC TXI0
void INT_Excep_SCI0_TXI0(void) { }

//;0x00F0 RXI1
void INT_Excep_SCI1_RXI1(void) { }

//;0x00F4 TXI1
void INT_Excep_SCI1_TXI1(void) { }

//;0x00F8 RXI2
void INT_Excep_SCI2_RXI2(void) { }

//;0x00FC TXI2
void INT_Excep_SCI2_TXI2(void) { }

//;0x0100 IRQ0
void INT_Excep_ICU_IRQ0(void) { }

//;0x0104 IRQ1
void INT_Excep_ICU_IRQ1(void) { }

//;0x0108 IRQ2
void INT_Excep_ICU_IRQ2(void) { }

//;0x010C IRQ3
void INT_Excep_ICU_IRQ3(void) { }

//;0x0110 IRQ4
void INT_Excep_ICU_IRQ4(void) { }

//;0x0114 IRQ5
void INT_Excep_ICU_IRQ5(void) { }

//;0x0118 IRQ6
void INT_Excep_ICU_IRQ6(void) { }

//;0x011C IRQ7
void INT_Excep_ICU_IRQ7(void) { }

//;0x0120 IRQ8
void INT_Excep_ICU_IRQ8(void) { }

//;0x0124 IRQ9
void INT_Excep_ICU_IRQ9(void) { }

//;0x0128 IRQ10
void INT_Excep_ICU_IRQ10(void) { }

//;0x012C IRQ11
void INT_Excep_ICU_IRQ11(void) { }

//;0x0130 IRQ12
void INT_Excep_ICU_IRQ12(void) { }

//;0x0134 IRQ13
void INT_Excep_ICU_IRQ13(void) { }

//;0x0138 IRQ14
void INT_Excep_ICU_IRQ14(void) { }

//;0x013C IRQ15
void INT_Excep_ICU_IRQ15(void) { }

//;0x0140 RXI3
void INT_Excep_SCI3_RXI3(void) { }

//;0x0144 TXI3
void INT_Excep_SCI3_TXI3(void) { }

//;0x0148 RXI4
void INT_Excep_SCI4_RXI4(void) { }

//;0x014C TXI4
void INT_Excep_SCI4_TXI4(void) { }

//;0x0150 RXI5
void INT_Excep_SCI5_RXI5(void) { }

//;0x0154 TXI5
void INT_Excep_SCI5_TXI5(void) { }

//;0x0158 RXI6
void INT_Excep_SCI6_RXI6(void) { }

//;0x015C TXI6
void INT_Excep_SCI6_TXI6(void) { }

//;0x0160 COMPA1
void INT_Excep_LVD1_LVD1(void) { }

//;0x0164 COMPA2
void INT_Excep_LVD2_LVD2(void) { }

//;0x0168 USBR0
void INT_Excep_USB0_USBR0(void) { }
//;0x016C Reserved

//;0x0170 ALM
void INT_Excep_RTC_ALM(void) { }

//;0x0174 PRD
void INT_Excep_RTC_PRD(void) { }

//;0x0178 HSUSBR
void INT_Excep_USBA_USBAR(void) { }

//;0x017C IWUNI
void INT_Excep_IWDT_IWUNI(void) { }

//;0x0180 WUNI
void INT_Excep_WDT_WUNI(void) { }

//;0x0184 PCDFI
void INT_Excep_PDC_PCDFI(void) { }

//;0x0188 RXI7
void INT_Excep_SCI7_RXI7(void) { }

//;0x018C TXI7
void INT_Excep_SCI7_TXI7(void) { }

//;0x0190 RXIF8
void INT_Excep_SCIFA8_RXIF8(void) { }

//;0x0194 TXIF8
void INT_Excep_SCIFA8_TXIF8(void) { }

//;0x0198 RXIF9
void INT_Excep_SCIFA9_RXIF9(void) { }

//;0x019C TXIF9
void INT_Excep_SCIFA9_TXIF9(void) { }

//;0x01A0 RXIF10
void INT_Excep_SCIFA10_RXIF10(void) { }

//;0x01A4 TXIF10
void INT_Excep_SCIFA10_TXIF10(void) { }

//;0x01A8 GROUPBE0
void INT_Excep_ICU_GROUPBE0(void) { }
//;0x01AC Reserved

//;0x01B0 Reserved

//;0x01B4 Reserved

//;0x01B8 GROUPBL0
void INT_Excep_ICU_GROUPBL0(void) { }

//;0x01BC GROUPBL1
void INT_Excep_ICU_GROUPBL1(void) { }

//;0x01C0 GROUPAL0
void INT_Excep_ICU_GROUPAL0(void) { }

//;0x01C4 GROUPAL1
void INT_Excep_ICU_GROUPAL1(void) { }

//;0x01C8 RXIF11
void INT_Excep_SCIFA11_RXIF11(void) { }

//;0x01CC TXIF11
void INT_Excep_SCIFA11_TXIF11(void) { }

//;0x01D0 RXIF12
void INT_Excep_SCI12_RXI12(void) { }

//;0x01D4 TXIF12
void INT_Excep_SCI12_TXI12(void) { }

//;0x01D8 Reserved

//;0x01DC Reserved

//;0x01E0 DMAC0I
void INT_Excep_DMAC_DMAC0I(void) { }

//;0x01E4 DMAC1I
void INT_Excep_DMAC_DMAC1I(void) { }

//;0x01E8 DMAC2I
void INT_Excep_DMAC_DMAC2I(void) { }

//;0x01EC DMAC3I
void INT_Excep_DMAC_DMAC3I(void) { }

//;0x01F0 DMAC74I
void INT_Excep_DMAC_DMAC74I(void) { }

//;0x01F4 OST
void INT_Excep_OST_OST(void) { }

//;0x01F8  EXDMAC0I
void INT_Excep_EXDMAC_EXDMAC0I(void) { }

//;0x01FC  EXDMAC1I
void INT_Excep_EXDMAC_EXDMAC1I(void) { }

//;0x0200  INTB128
void INT_Excep_PERIB_INTB128(void) { }

//;0x0204 INTB129
void INT_Excep_PERIB_INTB129(void) { }

//;0x0208 INTB130
void INT_Excep_PERIB_INTB130(void) { }

//;0x020C INTB131
void INT_Excep_PERIB_INTB131(void) { }

//;0x0210 INTB132
void INT_Excep_PERIB_INTB132(void) { }

//;0x0214 INTB133
void INT_Excep_PERIB_INTB133(void) { }

//;0x0218 INTB134
void INT_Excep_PERIB_INTB134(void) { }

//;0x021C INTB135
void INT_Excep_PERIB_INTB135(void) { }

//;0x0220 INTB136
void INT_Excep_PERIB_INTB136(void) { }

//;0x0224 INTB137
void INT_Excep_PERIB_INTB137(void) { }

//;0x0228 INTB138
void INT_Excep_PERIB_INTB138(void) { }

//;0x022C INTB139
void INT_Excep_PERIB_INTB139(void) { }

//;0x0230 INTB140
void INT_Excep_PERIB_INTB140(void) { }

//;0x0234 INTB141
void INT_Excep_PERIB_INTB141(void) { }

//;0x0238 INTB142
void INT_Excep_PERIB_INTB142(void) { }

//;0x023C INTB143
void INT_Excep_PERIB_INTB143(void) { }

//;0x0240 INTB144
void INT_Excep_PERIB_INTB144(void) { }

//;0x0244 INTB145
void INT_Excep_PERIB_INTB145(void) { }

//;0x0248 INTB146
void INT_Excep_PERIB_INTB146(void) { }

//;0x024C INTB147
void INT_Excep_PERIB_INTB147(void) { }

//;0x0250 INTB148
void INT_Excep_PERIB_INTB148(void) { }

//;0x02540 INTB149
void INT_Excep_PERIB_INTB149(void) { }

//;0x0258 INTB150
void INT_Excep_PERIB_INTB150(void) { }

//;0x025C INTB151
void INT_Excep_PERIB_INTB151(void) { }

//;0x0260 INTB152
void INT_Excep_PERIB_INTB152(void) { }

//;0x0264 INTB153
void INT_Excep_PERIB_INTB153(void) { }

//;0x0268 INTB154
void INT_Excep_PERIB_INTB154(void) { }

//;0x026C INTB155
void INT_Excep_PERIB_INTB155(void) { }

//;0x0270 INTB156
void INT_Excep_PERIB_INTB156(void) { }

//;0x0274 INTB157
void INT_Excep_PERIB_INTB157(void) { }

//;0x0278 INTB158
void INT_Excep_PERIB_INTB158(void) { }

//;0x027C INTB159
void INT_Excep_PERIB_INTB159(void) { }

//;0x0280 INTB160
void INT_Excep_PERIB_INTB160(void) { }

//;0x0284 INTB161
void INT_Excep_PERIB_INTB161(void) { }

//;0x0288 INTB162
void INT_Excep_PERIB_INTB162(void) { }

//;0x028C INTB163
void INT_Excep_PERIB_INTB163(void) { }

//;0x0290 INTB164
void INT_Excep_PERIB_INTB164(void) { }

//;0x0294 PERIB INTB165
void INT_Excep_PERIB_INTB165(void) { }

//;0x0298 PERIB INTB166
void INT_Excep_PERIB_INTB166(void) { }

//;0x029C PERIB INTB167
void INT_Excep_PERIB_INTB167(void) { }

//;0x02A0 PERIB INTB168
void INT_Excep_PERIB_INTB168(void) { }

//;0x02A4 PERIB INTB169
void INT_Excep_PERIB_INTB169(void) { }

//;0x02A8 PERIB INTB170
void INT_Excep_PERIB_INTB170(void) { }

//;0x02AC PERIB INTB171
void INT_Excep_PERIB_INTB171(void) { }

//;0x02B0 PERIB INTB172
void INT_Excep_PERIB_INTB172(void) { }

//;0x02B4 PERIB INTB173
void INT_Excep_PERIB_INTB173(void) { }

//;0x02B8 PERIB INTB174
void INT_Excep_PERIB_INTB174(void) { }

//;0x02BC PERIB INTB175
void INT_Excep_PERIB_INTB175(void) { }

//;0x02C0 PERIB INTB176
void INT_Excep_PERIB_INTB176(void) { }

//;0x02C4 PERIB INTB177
void INT_Excep_PERIB_INTB177(void) { }

//;0x02C8 PERIB INTB178
void INT_Excep_PERIB_INTB178(void) { }

//;0x02CC PERIB INTB179
void INT_Excep_PERIB_INTB179(void) { }

//;0x02D0 PERIB INTB180
void INT_Excep_PERIB_INTB180(void) { }

//;0x02D4 PERIB INTB181
void INT_Excep_PERIB_INTB181(void) { }

//;0x02D8 PERIB INTB182
void INT_Excep_PERIB_INTB182(void) { }

//;0x02DC PERIB INTB183
void INT_Excep_PERIB_INTB183(void) { }

//;0x02E0 PERIB INTB184
void INT_Excep_PERIB_INTB184(void) { }

//;0x02E4 PERIB INTB185
void INT_Excep_PERIB_INTB185(void) { }

//;0x02E8 PERIB INTB186
void INT_Excep_PERIB_INTB186(void) { }

//;0x02EC PERIB INTB187
void INT_Excep_PERIB_INTB187(void) { }

//;0x02F0 PERIB INTB188
void INT_Excep_PERIB_INTB188(void) { }

//;0x02F4 PERIB INTB189
void INT_Excep_PERIB_INTB189(void) { }

//;0x02F8 PERIB INTB190
void INT_Excep_PERIB_INTB190(void) { }

//;0x02FC PERIB INTB191
void INT_Excep_PERIB_INTB191(void) { }

//;0x0300 PERIB INTB192
void INT_Excep_PERIB_INTB192(void) { }

//;0x0304 PERIB INTB193
void INT_Excep_PERIB_INTB193(void) { }

//;0x0308 PERIB INTB194
void INT_Excep_PERIB_INTB194(void) { }

//;0x030C PERIB INTB195
void INT_Excep_PERIB_INTB195(void) { }

//;0x0310 PERIB INTB196
void INT_Excep_PERIB_INTB196(void) { }

//;0x0314 PERIB INTB197
void INT_Excep_PERIB_INTB197(void) { }

//;0x0318 PERIB INTB198
void INT_Excep_PERIB_INTB198(void) { }

//;0x031C PERIB INTB199
void INT_Excep_PERIB_INTB199(void) { }

//;0x0320 PERIB INTB200
void INT_Excep_PERIB_INTB200(void) { }

//;0x0324 PERIB INTB201
void INT_Excep_PERIB_INTB201(void) { }

//;0x0328 PERIB INTB202
void INT_Excep_PERIB_INTB202(void) { }

//;0x032C PERIB INTB203
void INT_Excep_PERIB_INTB203(void) { }

//;0x0320 PERIB INTB204
void INT_Excep_PERIB_INTB204(void) { }

//;0x0334 PERIB INTB205
void INT_Excep_PERIB_INTB205(void) { }

//;0x0338 PERIB INTB206
void INT_Excep_PERIB_INTB206(void) { }

//;0x033C PERIB INTB207
void INT_Excep_PERIB_INTB207(void) { }

//;0x0340 PERIA INTA208
void INT_Excep_PERIA_INTA208(void) { }

//;0x0344 PERIA INTA209
void INT_Excep_PERIA_INTA209(void) { }

//;0x0348 PERIA INTA210
void INT_Excep_PERIA_INTA210(void) { }

//;0x034C PERIA INTA211
void INT_Excep_PERIA_INTA211(void) { }

//;0x0350 PERIA INTA212
void INT_Excep_PERIA_INTA212(void) { }

//;0x0354 PERIA INTA213
void INT_Excep_PERIA_INTA213(void) { }

//;0x0358 PERIA INTA214
void INT_Excep_PERIA_INTA214(void) { }

//;0x035C PERIA INTA215
void INT_Excep_PERIA_INTA215(void) { }

//;0x0360 PERIA INTA216
void INT_Excep_PERIA_INTA216(void) { }

//;0x0364 PERIA INTA217
void INT_Excep_PERIA_INTA217(void) { }

//;0x0368 PERIA INTA218
void INT_Excep_PERIA_INTA218(void) { }

//;0x036C PERIA INTA219
void INT_Excep_PERIA_INTA219(void) { }

//;0x0370 PERIA INTA220
void INT_Excep_PERIA_INTA220(void) { }

//;0x0374 PERIA INTA221
void INT_Excep_PERIA_INTA221(void) { }

//;0x0378 PERIA INTA222
void INT_Excep_PERIA_INTA222(void) { }

//;0x037C PERIA INTA223
void INT_Excep_PERIA_INTA223(void) { }

//;0x0380 PERIA INTA224
void INT_Excep_PERIA_INTA224(void) { }

//;0x0384 PERIA INTA225
void INT_Excep_PERIA_INTA225(void) { }

//;0x0388 PERIA INTA226
void INT_Excep_PERIA_INTA226(void) { }

//;0x038C PERIA INTA227
void INT_Excep_PERIA_INTA227(void) { }

//;0x0390 PERIA INTA228
void INT_Excep_PERIA_INTA228(void) { }

//;0x0394 PERIA INTA229
void INT_Excep_PERIA_INTA229(void) { }

//;0x0398 PERIA INTA230
void INT_Excep_PERIA_INTA230(void) { }

//;0x039C PERIA INTA231
void INT_Excep_PERIA_INTA231(void) { }

//;0x03A0 PERIA INTA232
void INT_Excep_PERIA_INTA232(void) { }

//;0x03A4 PERIA INTA233
void INT_Excep_PERIA_INTA233(void) { }

//;0x03A8 PERIA INTA234
void INT_Excep_PERIA_INTA234(void) { }

//;0x03AC PERIA INTA235
void INT_Excep_PERIA_INTA235(void) { }

//;0x03B0 PERIA INTA236
void INT_Excep_PERIA_INTA236(void) { }

//;0x04B4 PERIA INTA237
void INT_Excep_PERIA_INTA237(void) { }

//;0x03B8 PERIA INTA238
void INT_Excep_PERIA_INTA238(void) { }

//;0x03BC PERIA INTA239
void INT_Excep_PERIA_INTA239(void) { }

//;0x03C0 PERIA INTA240
void INT_Excep_PERIA_INTA240(void) { }

//;0x03C4 PERIA INTA241
void INT_Excep_PERIA_INTA241(void) { }

//;0x03C8 PERIA INTA242
void INT_Excep_PERIA_INTA242(void) { }

//;0x03CC PERIA INTA243
void INT_Excep_PERIA_INTA243(void) { }

//;0x03D0 PERIA INTA244
void INT_Excep_PERIA_INTA244(void) { }

//;0x03D4 PERIA INTA245
void INT_Excep_PERIA_INTA245(void) { }

//;0x03D8 PERIA INTA246
void INT_Excep_PERIA_INTA246(void) { }

//;0x03DC PERIA INTA247
void INT_Excep_PERIA_INTA247(void) { }

//;0x03E0 PERIA INTA248
void INT_Excep_PERIA_INTA248(void) { }

//;0x03E4 PERIA INTA249
void INT_Excep_PERIA_INTA249(void) { }

//;0x03E8 PERIA INTA250
void INT_Excep_PERIA_INTA250(void) { }

//;0x03EC PERIA INTA251
void INT_Excep_PERIA_INTA251(void) { }

//;0x03F0 PERIA INTA252
void INT_Excep_PERIA_INTA252(void) { }

//;0x03F4 PERIA INTA253
void INT_Excep_PERIA_INTA253(void) { }

//;0x03F8 PERIA INTA254
void INT_Excep_PERIA_INTA254(void) { }

//;0x03FC PERIA INTA255
void INT_Excep_PERIA_INTA255(void) { }