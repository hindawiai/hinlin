<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <माला.स>

#समावेश "intel-pt-decoder/intel-pt-pkt-decoder.h"

#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "arch-tests.h"

/**
 * काष्ठा test_data - Test data.
 * @len: number of bytes to decode
 * @bytes: bytes to decode
 * @ctx: packet context to decode
 * @packet: expected packet
 * @new_ctx: expected new packet context
 * @ctx_unchanged: the packet context must not change
 */
काष्ठा test_data अणु
	पूर्णांक len;
	u8 bytes[INTEL_PT_PKT_MAX_SZ];
	क्रमागत पूर्णांकel_pt_pkt_ctx ctx;
	काष्ठा पूर्णांकel_pt_pkt packet;
	क्रमागत पूर्णांकel_pt_pkt_ctx new_ctx;
	पूर्णांक ctx_unchanged;
पूर्ण data[] = अणु
	/* Padding Packet */
	अणु1, अणु0पूर्ण, 0, अणुINTEL_PT_PAD, 0, 0पूर्ण, 0, 1 पूर्ण,
	/* Short Taken/Not Taken Packet */
	अणु1, अणु4पूर्ण, 0, अणुINTEL_PT_TNT, 1, 0पूर्ण, 0, 0 पूर्ण,
	अणु1, अणु6पूर्ण, 0, अणुINTEL_PT_TNT, 1, 0x20ULL << 58पूर्ण, 0, 0 पूर्ण,
	अणु1, अणु0x80पूर्ण, 0, अणुINTEL_PT_TNT, 6, 0पूर्ण, 0, 0 पूर्ण,
	अणु1, अणु0xfeपूर्ण, 0, अणुINTEL_PT_TNT, 6, 0x3fULL << 58पूर्ण, 0, 0 पूर्ण,
	/* Long Taken/Not Taken Packet */
	अणु8, अणु0x02, 0xa3, 2पूर्ण, 0, अणुINTEL_PT_TNT, 1, 0xa302ULL << 47पूर्ण, 0, 0 पूर्ण,
	अणु8, अणु0x02, 0xa3, 3पूर्ण, 0, अणुINTEL_PT_TNT, 1, 0x1a302ULL << 47पूर्ण, 0, 0 पूर्ण,
	अणु8, अणु0x02, 0xa3, 0, 0, 0, 0, 0, 0x80पूर्ण, 0, अणुINTEL_PT_TNT, 47, 0xa302ULL << 1पूर्ण, 0, 0 पूर्ण,
	अणु8, अणु0x02, 0xa3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण, 0, अणुINTEL_PT_TNT, 47, 0xffffffffffffa302ULL << 1पूर्ण, 0, 0 पूर्ण,
	/* Target IP Packet */
	अणु1, अणु0x0dपूर्ण, 0, अणुINTEL_PT_TIP, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु3, अणु0x2d, 1, 2पूर्ण, 0, अणुINTEL_PT_TIP, 1, 0x201पूर्ण, 0, 0 पूर्ण,
	अणु5, अणु0x4d, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_TIP, 2, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x6d, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP, 3, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x8d, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP, 4, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु9, अणु0xcd, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_TIP, 6, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	/* Packet Generation Enable */
	अणु1, अणु0x11पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु3, अणु0x31, 1, 2पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 1, 0x201पूर्ण, 0, 0 पूर्ण,
	अणु5, अणु0x51, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 2, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x71, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 3, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x91, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 4, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु9, अणु0xd1, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_TIP_PGE, 6, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	/* Packet Generation Disable */
	अणु1, अणु0x01पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु3, अणु0x21, 1, 2पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 1, 0x201पूर्ण, 0, 0 पूर्ण,
	अणु5, अणु0x41, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 2, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x61, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 3, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x81, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 4, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु9, अणु0xc1, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_TIP_PGD, 6, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	/* Flow Update Packet */
	अणु1, अणु0x1dपूर्ण, 0, अणुINTEL_PT_FUP, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु3, अणु0x3d, 1, 2पूर्ण, 0, अणुINTEL_PT_FUP, 1, 0x201पूर्ण, 0, 0 पूर्ण,
	अणु5, अणु0x5d, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_FUP, 2, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x7d, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_FUP, 3, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु7, अणु0x9d, 1, 2, 3, 4, 5, 6पूर्ण, 0, अणुINTEL_PT_FUP, 4, 0x60504030201पूर्ण, 0, 0 पूर्ण,
	अणु9, अणु0xdd, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_FUP, 6, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	/* Paging Inक्रमmation Packet */
	अणु8, अणु0x02, 0x43, 2, 4, 6, 8, 10, 12पूर्ण, 0, अणुINTEL_PT_PIP, 0, 0xC0A08060402पूर्ण, 0, 0 पूर्ण,
	अणु8, अणु0x02, 0x43, 3, 4, 6, 8, 10, 12पूर्ण, 0, अणुINTEL_PT_PIP, 0, 0xC0A08060403पूर्ण, 0, 0 पूर्ण,
	/* Mode Exec Packet */
	अणु2, अणु0x99, 0x00पूर्ण, 0, अणुINTEL_PT_MODE_EXEC, 0, 16पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x99, 0x01पूर्ण, 0, अणुINTEL_PT_MODE_EXEC, 0, 64पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x99, 0x02पूर्ण, 0, अणुINTEL_PT_MODE_EXEC, 0, 32पूर्ण, 0, 0 पूर्ण,
	/* Mode TSX Packet */
	अणु2, अणु0x99, 0x20पूर्ण, 0, अणुINTEL_PT_MODE_TSX, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x99, 0x21पूर्ण, 0, अणुINTEL_PT_MODE_TSX, 0, 1पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x99, 0x22पूर्ण, 0, अणुINTEL_PT_MODE_TSX, 0, 2पूर्ण, 0, 0 पूर्ण,
	/* Trace Stop Packet */
	अणु2, अणु0x02, 0x83पूर्ण, 0, अणुINTEL_PT_TRACESTOP, 0, 0पूर्ण, 0, 0 पूर्ण,
	/* Core:Bus Ratio Packet */
	अणु4, अणु0x02, 0x03, 0x12, 0पूर्ण, 0, अणुINTEL_PT_CBR, 0, 0x12पूर्ण, 0, 1 पूर्ण,
	/* Timestamp Counter Packet */
	अणु8, अणु0x19, 1, 2, 3, 4, 5, 6, 7पूर्ण, 0, अणुINTEL_PT_TSC, 0, 0x7060504030201पूर्ण, 0, 1 पूर्ण,
	/* Mini Time Counter Packet */
	अणु2, अणु0x59, 0x12पूर्ण, 0, अणुINTEL_PT_MTC, 0, 0x12पूर्ण, 0, 1 पूर्ण,
	/* TSC / MTC Alignment Packet */
	अणु7, अणु0x02, 0x73पूर्ण, 0, अणुINTEL_PT_TMA, 0, 0पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x02, 0x73, 1, 2पूर्ण, 0, अणुINTEL_PT_TMA, 0, 0x201पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x02, 0x73, 0, 0, 0, 0xff, 1पूर्ण, 0, अणुINTEL_PT_TMA, 0x1ff, 0पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x02, 0x73, 0x80, 0xc0, 0, 0xff, 1पूर्ण, 0, अणुINTEL_PT_TMA, 0x1ff, 0xc080पूर्ण, 0, 1 पूर्ण,
	/* Cycle Count Packet */
	अणु1, अणु0x03पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0पूर्ण, 0, 1 पूर्ण,
	अणु1, अणु0x0bपूर्ण, 0, अणुINTEL_PT_CYC, 0, 1पूर्ण, 0, 1 पूर्ण,
	अणु1, अणु0xfbपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x1fपूर्ण, 0, 1 पूर्ण,
	अणु2, अणु0x07, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x20पूर्ण, 0, 1 पूर्ण,
	अणु2, अणु0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0xfffपूर्ण, 0, 1 पूर्ण,
	अणु3, अणु0x07, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x1000पूर्ण, 0, 1 पूर्ण,
	अणु3, अणु0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x7ffffपूर्ण, 0, 1 पूर्ण,
	अणु4, अणु0x07, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x80000पूर्ण, 0, 1 पूर्ण,
	अणु4, अणु0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x3ffffffपूर्ण, 0, 1 पूर्ण,
	अणु5, अणु0x07, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x4000000पूर्ण, 0, 1 पूर्ण,
	अणु5, अणु0xff, 0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x1ffffffffपूर्ण, 0, 1 पूर्ण,
	अणु6, अणु0x07, 1, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x200000000पूर्ण, 0, 1 पूर्ण,
	अणु6, अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0xffffffffffपूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x07, 1, 1, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x10000000000पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x7fffffffffffपूर्ण, 0, 1 पूर्ण,
	अणु8, अणु0x07, 1, 1, 1, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x800000000000पूर्ण, 0, 1 पूर्ण,
	अणु8, अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x3fffffffffffffपूर्ण, 0, 1 पूर्ण,
	अणु9, अणु0x07, 1, 1, 1, 1, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x40000000000000पूर्ण, 0, 1 पूर्ण,
	अणु9, अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x1fffffffffffffffपूर्ण, 0, 1 पूर्ण,
	अणु10, अणु0x07, 1, 1, 1, 1, 1, 1, 1, 1, 2पूर्ण, 0, अणुINTEL_PT_CYC, 0, 0x2000000000000000पूर्ण, 0, 1 पूर्ण,
	अणु10, अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeपूर्ण, 0, अणुINTEL_PT_CYC, 0, 0xffffffffffffffffपूर्ण, 0, 1 पूर्ण,
	/* Virtual-Machine Control Structure Packet */
	अणु7, अणु0x02, 0xc8, 1, 2, 3, 4, 5पूर्ण, 0, अणुINTEL_PT_VMCS, 5, 0x504030201पूर्ण, 0, 0 पूर्ण,
	/* Overflow Packet */
	अणु2, अणु0x02, 0xf3पूर्ण, 0, अणुINTEL_PT_OVF, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x02, 0xf3पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_OVF, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x02, 0xf3पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_OVF, 0, 0पूर्ण, 0, 0 पूर्ण,
	/* Packet Stream Boundary*/
	अणु16, अणु0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82पूर्ण, 0, अणुINTEL_PT_PSB, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु16, अणु0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_PSB, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु16, अणु0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_PSB, 0, 0पूर्ण, 0, 0 पूर्ण,
	/* PSB End Packet */
	अणु2, अणु0x02, 0x23पूर्ण, 0, अणुINTEL_PT_PSBEND, 0, 0पूर्ण, 0, 0 पूर्ण,
	/* Maपूर्णांकenance Packet */
	अणु11, अणु0x02, 0xc3, 0x88, 1, 2, 3, 4, 5, 6, 7पूर्ण, 0, अणुINTEL_PT_MNT, 0, 0x7060504030201पूर्ण, 0, 1 पूर्ण,
	/* Write Data to PT Packet */
	अणु6, अणु0x02, 0x12, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_PTWRITE, 0, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु10, अणु0x02, 0x32, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_PTWRITE, 1, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	अणु6, अणु0x02, 0x92, 1, 2, 3, 4पूर्ण, 0, अणुINTEL_PT_PTWRITE_IP, 0, 0x4030201पूर्ण, 0, 0 पूर्ण,
	अणु10, अणु0x02, 0xb2, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_PTWRITE_IP, 1, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	/* Execution Stop Packet */
	अणु2, अणु0x02, 0x62पूर्ण, 0, अणुINTEL_PT_EXSTOP, 0, 0पूर्ण, 0, 1 पूर्ण,
	अणु2, अणु0x02, 0xe2पूर्ण, 0, अणुINTEL_PT_EXSTOP_IP, 0, 0पूर्ण, 0, 1 पूर्ण,
	/* Monitor Wait Packet */
	अणु10, अणु0x02, 0xc2पूर्ण, 0, अणुINTEL_PT_MWAIT, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु10, अणु0x02, 0xc2, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_MWAIT, 0, 0x807060504030201पूर्ण, 0, 0 पूर्ण,
	अणु10, अणु0x02, 0xc2, 0xff, 2, 3, 4, 7, 6, 7, 8पूर्ण, 0, अणुINTEL_PT_MWAIT, 0, 0x8070607040302ffपूर्ण, 0, 0 पूर्ण,
	/* Power Entry Packet */
	अणु4, अणु0x02, 0x22पूर्ण, 0, अणुINTEL_PT_PWRE, 0, 0पूर्ण, 0, 1 पूर्ण,
	अणु4, अणु0x02, 0x22, 1, 2पूर्ण, 0, अणुINTEL_PT_PWRE, 0, 0x0201पूर्ण, 0, 1 पूर्ण,
	अणु4, अणु0x02, 0x22, 0x80, 0x34पूर्ण, 0, अणुINTEL_PT_PWRE, 0, 0x3480पूर्ण, 0, 1 पूर्ण,
	अणु4, अणु0x02, 0x22, 0x00, 0x56पूर्ण, 0, अणुINTEL_PT_PWRE, 0, 0x5600पूर्ण, 0, 1 पूर्ण,
	/* Power Exit Packet */
	अणु7, अणु0x02, 0xa2पूर्ण, 0, अणुINTEL_PT_PWRX, 0, 0पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x02, 0xa2, 1, 2, 3, 4, 5पूर्ण, 0, अणुINTEL_PT_PWRX, 0, 0x504030201पूर्ण, 0, 1 पूर्ण,
	अणु7, अणु0x02, 0xa2, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण, 0, अणुINTEL_PT_PWRX, 0, 0xffffffffffपूर्ण, 0, 1 पूर्ण,
	/* Block Begin Packet */
	अणु3, अणु0x02, 0x63, 0x00पूर्ण, 0, अणुINTEL_PT_BBP, 0, 0पूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	अणु3, अणु0x02, 0x63, 0x80पूर्ण, 0, अणुINTEL_PT_BBP, 1, 0पूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	अणु3, अणु0x02, 0x63, 0x1fपूर्ण, 0, अणुINTEL_PT_BBP, 0, 0x1fपूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	अणु3, अणु0x02, 0x63, 0x9fपूर्ण, 0, अणुINTEL_PT_BBP, 1, 0x1fपूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	/* 4-byte Block Item Packet */
	अणु5, अणु0x04पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BIP, 0, 0पूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	अणु5, अणु0xfcपूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BIP, 0x1f, 0पूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	अणु5, अणु0x04, 1, 2, 3, 4पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BIP, 0, 0x04030201पूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	अणु5, अणु0xfc, 1, 2, 3, 4पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BIP, 0x1f, 0x04030201पूर्ण, INTEL_PT_BLK_4_CTX, 0 पूर्ण,
	/* 8-byte Block Item Packet */
	अणु9, अणु0x04पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BIP, 0, 0पूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	अणु9, अणु0xfcपूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BIP, 0x1f, 0पूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	अणु9, अणु0x04, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BIP, 0, 0x0807060504030201पूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	अणु9, अणु0xfc, 1, 2, 3, 4, 5, 6, 7, 8पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BIP, 0x1f, 0x0807060504030201पूर्ण, INTEL_PT_BLK_8_CTX, 0 पूर्ण,
	/* Block End Packet */
	अणु2, अणु0x02, 0x33पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BEP, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x02, 0xb3पूर्ण, INTEL_PT_BLK_4_CTX, अणुINTEL_PT_BEP_IP, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x02, 0x33पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BEP, 0, 0पूर्ण, 0, 0 पूर्ण,
	अणु2, अणु0x02, 0xb3पूर्ण, INTEL_PT_BLK_8_CTX, अणुINTEL_PT_BEP_IP, 0, 0पूर्ण, 0, 0 पूर्ण,
	/* Terminator */
	अणु0, अणु0पूर्ण, 0, अणु0, 0, 0पूर्ण, 0, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक dump_packet(काष्ठा पूर्णांकel_pt_pkt *packet, u8 *bytes, पूर्णांक len)
अणु
	अक्षर desc[INTEL_PT_PKT_DESC_MAX];
	पूर्णांक ret, i;

	क्रम (i = 0; i < len; i++)
		pr_debug(" %02x", bytes[i]);
	क्रम (; i < INTEL_PT_PKT_MAX_SZ; i++)
		pr_debug("   ");
	pr_debug("   ");
	ret = पूर्णांकel_pt_pkt_desc(packet, desc, INTEL_PT_PKT_DESC_MAX);
	अगर (ret < 0) अणु
		pr_debug("intel_pt_pkt_desc failed!\n");
		वापस TEST_FAIL;
	पूर्ण
	pr_debug("%s\n", desc);

	वापस TEST_OK;
पूर्ण

अटल व्योम decoding_failed(काष्ठा test_data *d)
अणु
	pr_debug("Decoding failed!\n");
	pr_debug("Decoding:  ");
	dump_packet(&d->packet, d->bytes, d->len);
पूर्ण

अटल पूर्णांक fail(काष्ठा test_data *d, काष्ठा पूर्णांकel_pt_pkt *packet, पूर्णांक len,
		क्रमागत पूर्णांकel_pt_pkt_ctx new_ctx)
अणु
	decoding_failed(d);

	अगर (len != d->len)
		pr_debug("Expected length: %d   Decoded length %d\n",
			 d->len, len);

	अगर (packet->type != d->packet.type)
		pr_debug("Expected type: %d   Decoded type %d\n",
			 d->packet.type, packet->type);

	अगर (packet->count != d->packet.count)
		pr_debug("Expected count: %d   Decoded count %d\n",
			 d->packet.count, packet->count);

	अगर (packet->payload != d->packet.payload)
		pr_debug("Expected payload: 0x%llx   Decoded payload 0x%llx\n",
			 (अचिन्हित दीर्घ दीर्घ)d->packet.payload,
			 (अचिन्हित दीर्घ दीर्घ)packet->payload);

	अगर (new_ctx != d->new_ctx)
		pr_debug("Expected packet context: %d   Decoded packet context %d\n",
			 d->new_ctx, new_ctx);

	वापस TEST_FAIL;
पूर्ण

अटल पूर्णांक test_ctx_unchanged(काष्ठा test_data *d, काष्ठा पूर्णांकel_pt_pkt *packet,
			      क्रमागत पूर्णांकel_pt_pkt_ctx ctx)
अणु
	क्रमागत पूर्णांकel_pt_pkt_ctx old_ctx = ctx;

	पूर्णांकel_pt_upd_pkt_ctx(packet, &ctx);

	अगर (ctx != old_ctx) अणु
		decoding_failed(d);
		pr_debug("Packet context changed!\n");
		वापस TEST_FAIL;
	पूर्ण

	वापस TEST_OK;
पूर्ण

अटल पूर्णांक test_one(काष्ठा test_data *d)
अणु
	काष्ठा पूर्णांकel_pt_pkt packet;
	क्रमागत पूर्णांकel_pt_pkt_ctx ctx = d->ctx;
	पूर्णांक ret;

	स_रखो(&packet, 0xff, माप(packet));

	/* Decode a packet */
	ret = पूर्णांकel_pt_get_packet(d->bytes, d->len, &packet, &ctx);
	अगर (ret < 0 || ret > INTEL_PT_PKT_MAX_SZ) अणु
		decoding_failed(d);
		pr_debug("intel_pt_get_packet returned %d\n", ret);
		वापस TEST_FAIL;
	पूर्ण

	/* Some packets must always leave the packet context unchanged */
	अगर (d->ctx_unchanged) अणु
		पूर्णांक err;

		err = test_ctx_unchanged(d, &packet, INTEL_PT_NO_CTX);
		अगर (err)
			वापस err;
		err = test_ctx_unchanged(d, &packet, INTEL_PT_BLK_4_CTX);
		अगर (err)
			वापस err;
		err = test_ctx_unchanged(d, &packet, INTEL_PT_BLK_8_CTX);
		अगर (err)
			वापस err;
	पूर्ण

	/* Compare to the expected values */
	अगर (ret != d->len || packet.type != d->packet.type ||
	    packet.count != d->packet.count ||
	    packet.payload != d->packet.payload || ctx != d->new_ctx)
		वापस fail(d, &packet, ret, ctx);

	pr_debug("Decoded ok:");
	ret = dump_packet(&d->packet, d->bytes, d->len);

	वापस ret;
पूर्ण

/*
 * This test feeds byte sequences to the Intel PT packet decoder and checks the
 * results. Changes to the packet context are also checked.
 */
पूर्णांक test__पूर्णांकel_pt_pkt_decoder(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा test_data *d = data;
	पूर्णांक ret;

	क्रम (d = data; d->len; d++) अणु
		ret = test_one(d);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस TEST_OK;
पूर्ण
