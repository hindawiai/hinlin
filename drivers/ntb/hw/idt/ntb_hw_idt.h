<शैली गुरु>
/*
 *   This file is provided under a GPLv2 license.  When using or
 *   redistributing this file, you may करो so under that license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2016-2018 T-Platक्रमms JSC All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy it
 *   under the terms and conditions of the GNU General Public License,
 *   version 2, as published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 *   Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License aदीर्घ
 *   with this program; अगर not, one can be found http://www.gnu.org/licenses/.
 *
 *   The full GNU General Public License is included in this distribution in
 *   the file called "COPYING".
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * IDT PCIe-चयन NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Serge Semin <fancer.lancer@gmail.com>, <Sergey.Semin@t-platक्रमms.ru>
 */

#अगर_अघोषित NTB_HW_IDT_H
#घोषणा NTB_HW_IDT_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ntb.h>

/*
 * Macro is used to create the काष्ठा pci_device_id that matches
 * the supported IDT PCIe-चयनes
 * @devname: Capitalized name of the particular device
 * @data: Variable passed to the driver of the particular device
 */
#घोषणा IDT_PCI_DEVICE_IDS(devname, data) \
	.venकरोr = PCI_VENDOR_ID_IDT, .device = PCI_DEVICE_ID_IDT_##devname, \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, \
	.class = (PCI_CLASS_BRIDGE_OTHER << 8), .class_mask = (0xFFFF00), \
	.driver_data = (kernel_uदीर्घ_t)&data

/*
 * IDT PCIe-चयनes device IDs
 */
#घोषणा PCI_DEVICE_ID_IDT_89HPES24NT6AG2  0x8091
#घोषणा PCI_DEVICE_ID_IDT_89HPES32NT8AG2  0x808F
#घोषणा PCI_DEVICE_ID_IDT_89HPES32NT8BG2  0x8088
#घोषणा PCI_DEVICE_ID_IDT_89HPES12NT12G2  0x8092
#घोषणा PCI_DEVICE_ID_IDT_89HPES16NT16G2  0x8090
#घोषणा PCI_DEVICE_ID_IDT_89HPES24NT24G2  0x808E
#घोषणा PCI_DEVICE_ID_IDT_89HPES32NT24AG2 0x808C
#घोषणा PCI_DEVICE_ID_IDT_89HPES32NT24BG2 0x808A

/*
 * NT-function Configuration Space रेजिस्टरs
 * NOTE 1) The IDT PCIe-चयन पूर्णांकernal data is little-endian
 *      so it must be taken पूर्णांकo account in the driver
 *      पूर्णांकernals.
 *      2) Additionally the रेजिस्टरs should be accessed either
 *      with byte-enables corresponding to their native size or
 *      the size of one DWORD
 *
 * So to simplअगरy the driver code, there is only DWORD-sized पढ़ो/ग_लिखो
 * operations utilized.
 */
/* PCI Express Configuration Space */
/* PCI Express command/status रेजिस्टर	(DWORD) */
#घोषणा IDT_NT_PCICMDSTS		0x00004U
/* PCI Express Device Capabilities	(DWORD) */
#घोषणा IDT_NT_PCIEDCAP			0x00044U
/* PCI Express Device Control/Status	(WORD+WORD) */
#घोषणा IDT_NT_PCIEDCTLSTS		0x00048U
/* PCI Express Link Capabilities	(DWORD) */
#घोषणा IDT_NT_PCIELCAP			0x0004CU
/* PCI Express Link Control/Status	(WORD+WORD) */
#घोषणा IDT_NT_PCIELCTLSTS		0x00050U
/* PCI Express Device Capabilities 2	(DWORD) */
#घोषणा IDT_NT_PCIEDCAP2		0x00064U
/* PCI Express Device Control 2		(WORD+WORD) */
#घोषणा IDT_NT_PCIEDCTL2		0x00068U
/* PCI Power Management Control and Status (DWORD) */
#घोषणा IDT_NT_PMCSR			0x000C4U
/*==========================================*/
/* IDT Proprietary NT-port-specअगरic रेजिस्टरs */
/* NT-function मुख्य control रेजिस्टरs */
/* NT Endpoपूर्णांक Control			(DWORD) */
#घोषणा IDT_NT_NTCTL			0x00400U
/* NT Endpoपूर्णांक Interrupt Status/Mask	(DWORD) */
#घोषणा IDT_NT_NTINTSTS			0x00404U
#घोषणा IDT_NT_NTINTMSK			0x00408U
/* NT Endpoपूर्णांक Signal Data		(DWORD) */
#घोषणा IDT_NT_NTSDATA			0x0040CU
/* NT Endpoपूर्णांक Global Signal		(DWORD) */
#घोषणा IDT_NT_NTGSIGNAL		0x00410U
/* Internal Error Reporting Mask 0/1	(DWORD) */
#घोषणा IDT_NT_NTIERRORMSK0		0x00414U
#घोषणा IDT_NT_NTIERRORMSK1		0x00418U
/* Doorbel रेजिस्टरs */
/* NT Outbound Doorbell Set		(DWORD) */
#घोषणा IDT_NT_OUTDBELLSET		0x00420U
/* NT Inbound Doorbell Status/Mask	(DWORD) */
#घोषणा IDT_NT_INDBELLSTS		0x00428U
#घोषणा IDT_NT_INDBELLMSK		0x0042CU
/* Message रेजिस्टरs */
/* Outbound Message N			(DWORD) */
#घोषणा IDT_NT_OUTMSG0			0x00430U
#घोषणा IDT_NT_OUTMSG1			0x00434U
#घोषणा IDT_NT_OUTMSG2			0x00438U
#घोषणा IDT_NT_OUTMSG3			0x0043CU
/* Inbound Message N			(DWORD) */
#घोषणा IDT_NT_INMSG0			0x00440U
#घोषणा IDT_NT_INMSG1			0x00444U
#घोषणा IDT_NT_INMSG2			0x00448U
#घोषणा IDT_NT_INMSG3			0x0044CU
/* Inbound Message Source N		(DWORD) */
#घोषणा IDT_NT_INMSGSRC0		0x00450U
#घोषणा IDT_NT_INMSGSRC1		0x00454U
#घोषणा IDT_NT_INMSGSRC2		0x00458U
#घोषणा IDT_NT_INMSGSRC3		0x0045CU
/* Message Status			(DWORD) */
#घोषणा IDT_NT_MSGSTS			0x00460U
/* Message Status Mask			(DWORD) */
#घोषणा IDT_NT_MSGSTSMSK		0x00464U
/* BAR-setup रेजिस्टरs */
/* BAR N Setup/Limit Address/Lower and Upper Translated Base Address (DWORD) */
#घोषणा IDT_NT_BARSETUP0		0x00470U
#घोषणा IDT_NT_BARLIMIT0		0x00474U
#घोषणा IDT_NT_BARLTBASE0		0x00478U
#घोषणा IDT_NT_BARUTBASE0		0x0047CU
#घोषणा IDT_NT_BARSETUP1		0x00480U
#घोषणा IDT_NT_BARLIMIT1		0x00484U
#घोषणा IDT_NT_BARLTBASE1		0x00488U
#घोषणा IDT_NT_BARUTBASE1		0x0048CU
#घोषणा IDT_NT_BARSETUP2		0x00490U
#घोषणा IDT_NT_BARLIMIT2		0x00494U
#घोषणा IDT_NT_BARLTBASE2		0x00498U
#घोषणा IDT_NT_BARUTBASE2		0x0049CU
#घोषणा IDT_NT_BARSETUP3		0x004A0U
#घोषणा IDT_NT_BARLIMIT3		0x004A4U
#घोषणा IDT_NT_BARLTBASE3		0x004A8U
#घोषणा IDT_NT_BARUTBASE3		0x004ACU
#घोषणा IDT_NT_BARSETUP4		0x004B0U
#घोषणा IDT_NT_BARLIMIT4		0x004B4U
#घोषणा IDT_NT_BARLTBASE4		0x004B8U
#घोषणा IDT_NT_BARUTBASE4		0x004BCU
#घोषणा IDT_NT_BARSETUP5		0x004C0U
#घोषणा IDT_NT_BARLIMIT5		0x004C4U
#घोषणा IDT_NT_BARLTBASE5		0x004C8U
#घोषणा IDT_NT_BARUTBASE5		0x004CCU
/* NT mapping table रेजिस्टरs */
/* NT Mapping Table Address/Status/Data	(DWORD) */
#घोषणा IDT_NT_NTMTBLADDR		0x004D0U
#घोषणा IDT_NT_NTMTBLSTS		0x004D4U
#घोषणा IDT_NT_NTMTBLDATA		0x004D8U
/* Requester ID (Bus:Device:Function) Capture	(DWORD) */
#घोषणा IDT_NT_REQIDCAP			0x004DCU
/* Memory Winकरोws Lookup table रेजिस्टरs */
/* Lookup Table Offset/Lower, Middle and Upper data	(DWORD) */
#घोषणा IDT_NT_LUTOFFSET		0x004E0U
#घोषणा IDT_NT_LUTLDATA			0x004E4U
#घोषणा IDT_NT_LUTMDATA			0x004E8U
#घोषणा IDT_NT_LUTUDATA			0x004ECU
/* NT Endpoपूर्णांक Uncorrectable/Correctable Errors Emulation रेजिस्टरs (DWORD) */
#घोषणा IDT_NT_NTUEEM			0x004F0U
#घोषणा IDT_NT_NTCEEM			0x004F4U
/* Global Address Space Access/Data रेजिस्टरs	(DWARD) */
#घोषणा IDT_NT_GASAADDR			0x00FF8U
#घोषणा IDT_NT_GASADATA			0x00FFCU

/*
 * IDT PCIe-चयन Global Configuration and Status रेजिस्टरs
 */
/* Port N Configuration रेजिस्टर in global space */
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP0_PCIECMDSTS		0x01004U
#घोषणा IDT_SW_NTP0_PCIELCTLSTS		0x01050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP0_NTCTL		0x01400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP0_BARSETUP0		0x01470U
#घोषणा IDT_SW_NTP0_BARLIMIT0		0x01474U
#घोषणा IDT_SW_NTP0_BARLTBASE0		0x01478U
#घोषणा IDT_SW_NTP0_BARUTBASE0		0x0147CU
#घोषणा IDT_SW_NTP0_BARSETUP1		0x01480U
#घोषणा IDT_SW_NTP0_BARLIMIT1		0x01484U
#घोषणा IDT_SW_NTP0_BARLTBASE1		0x01488U
#घोषणा IDT_SW_NTP0_BARUTBASE1		0x0148CU
#घोषणा IDT_SW_NTP0_BARSETUP2		0x01490U
#घोषणा IDT_SW_NTP0_BARLIMIT2		0x01494U
#घोषणा IDT_SW_NTP0_BARLTBASE2		0x01498U
#घोषणा IDT_SW_NTP0_BARUTBASE2		0x0149CU
#घोषणा IDT_SW_NTP0_BARSETUP3		0x014A0U
#घोषणा IDT_SW_NTP0_BARLIMIT3		0x014A4U
#घोषणा IDT_SW_NTP0_BARLTBASE3		0x014A8U
#घोषणा IDT_SW_NTP0_BARUTBASE3		0x014ACU
#घोषणा IDT_SW_NTP0_BARSETUP4		0x014B0U
#घोषणा IDT_SW_NTP0_BARLIMIT4		0x014B4U
#घोषणा IDT_SW_NTP0_BARLTBASE4		0x014B8U
#घोषणा IDT_SW_NTP0_BARUTBASE4		0x014BCU
#घोषणा IDT_SW_NTP0_BARSETUP5		0x014C0U
#घोषणा IDT_SW_NTP0_BARLIMIT5		0x014C4U
#घोषणा IDT_SW_NTP0_BARLTBASE5		0x014C8U
#घोषणा IDT_SW_NTP0_BARUTBASE5		0x014CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP2_PCIECMDSTS		0x05004U
#घोषणा IDT_SW_NTP2_PCIELCTLSTS		0x05050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP2_NTCTL		0x05400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP2_BARSETUP0		0x05470U
#घोषणा IDT_SW_NTP2_BARLIMIT0		0x05474U
#घोषणा IDT_SW_NTP2_BARLTBASE0		0x05478U
#घोषणा IDT_SW_NTP2_BARUTBASE0		0x0547CU
#घोषणा IDT_SW_NTP2_BARSETUP1		0x05480U
#घोषणा IDT_SW_NTP2_BARLIMIT1		0x05484U
#घोषणा IDT_SW_NTP2_BARLTBASE1		0x05488U
#घोषणा IDT_SW_NTP2_BARUTBASE1		0x0548CU
#घोषणा IDT_SW_NTP2_BARSETUP2		0x05490U
#घोषणा IDT_SW_NTP2_BARLIMIT2		0x05494U
#घोषणा IDT_SW_NTP2_BARLTBASE2		0x05498U
#घोषणा IDT_SW_NTP2_BARUTBASE2		0x0549CU
#घोषणा IDT_SW_NTP2_BARSETUP3		0x054A0U
#घोषणा IDT_SW_NTP2_BARLIMIT3		0x054A4U
#घोषणा IDT_SW_NTP2_BARLTBASE3		0x054A8U
#घोषणा IDT_SW_NTP2_BARUTBASE3		0x054ACU
#घोषणा IDT_SW_NTP2_BARSETUP4		0x054B0U
#घोषणा IDT_SW_NTP2_BARLIMIT4		0x054B4U
#घोषणा IDT_SW_NTP2_BARLTBASE4		0x054B8U
#घोषणा IDT_SW_NTP2_BARUTBASE4		0x054BCU
#घोषणा IDT_SW_NTP2_BARSETUP5		0x054C0U
#घोषणा IDT_SW_NTP2_BARLIMIT5		0x054C4U
#घोषणा IDT_SW_NTP2_BARLTBASE5		0x054C8U
#घोषणा IDT_SW_NTP2_BARUTBASE5		0x054CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP4_PCIECMDSTS		0x09004U
#घोषणा IDT_SW_NTP4_PCIELCTLSTS		0x09050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP4_NTCTL		0x09400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP4_BARSETUP0		0x09470U
#घोषणा IDT_SW_NTP4_BARLIMIT0		0x09474U
#घोषणा IDT_SW_NTP4_BARLTBASE0		0x09478U
#घोषणा IDT_SW_NTP4_BARUTBASE0		0x0947CU
#घोषणा IDT_SW_NTP4_BARSETUP1		0x09480U
#घोषणा IDT_SW_NTP4_BARLIMIT1		0x09484U
#घोषणा IDT_SW_NTP4_BARLTBASE1		0x09488U
#घोषणा IDT_SW_NTP4_BARUTBASE1		0x0948CU
#घोषणा IDT_SW_NTP4_BARSETUP2		0x09490U
#घोषणा IDT_SW_NTP4_BARLIMIT2		0x09494U
#घोषणा IDT_SW_NTP4_BARLTBASE2		0x09498U
#घोषणा IDT_SW_NTP4_BARUTBASE2		0x0949CU
#घोषणा IDT_SW_NTP4_BARSETUP3		0x094A0U
#घोषणा IDT_SW_NTP4_BARLIMIT3		0x094A4U
#घोषणा IDT_SW_NTP4_BARLTBASE3		0x094A8U
#घोषणा IDT_SW_NTP4_BARUTBASE3		0x094ACU
#घोषणा IDT_SW_NTP4_BARSETUP4		0x094B0U
#घोषणा IDT_SW_NTP4_BARLIMIT4		0x094B4U
#घोषणा IDT_SW_NTP4_BARLTBASE4		0x094B8U
#घोषणा IDT_SW_NTP4_BARUTBASE4		0x094BCU
#घोषणा IDT_SW_NTP4_BARSETUP5		0x094C0U
#घोषणा IDT_SW_NTP4_BARLIMIT5		0x094C4U
#घोषणा IDT_SW_NTP4_BARLTBASE5		0x094C8U
#घोषणा IDT_SW_NTP4_BARUTBASE5		0x094CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP6_PCIECMDSTS		0x0D004U
#घोषणा IDT_SW_NTP6_PCIELCTLSTS		0x0D050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP6_NTCTL		0x0D400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP6_BARSETUP0		0x0D470U
#घोषणा IDT_SW_NTP6_BARLIMIT0		0x0D474U
#घोषणा IDT_SW_NTP6_BARLTBASE0		0x0D478U
#घोषणा IDT_SW_NTP6_BARUTBASE0		0x0D47CU
#घोषणा IDT_SW_NTP6_BARSETUP1		0x0D480U
#घोषणा IDT_SW_NTP6_BARLIMIT1		0x0D484U
#घोषणा IDT_SW_NTP6_BARLTBASE1		0x0D488U
#घोषणा IDT_SW_NTP6_BARUTBASE1		0x0D48CU
#घोषणा IDT_SW_NTP6_BARSETUP2		0x0D490U
#घोषणा IDT_SW_NTP6_BARLIMIT2		0x0D494U
#घोषणा IDT_SW_NTP6_BARLTBASE2		0x0D498U
#घोषणा IDT_SW_NTP6_BARUTBASE2		0x0D49CU
#घोषणा IDT_SW_NTP6_BARSETUP3		0x0D4A0U
#घोषणा IDT_SW_NTP6_BARLIMIT3		0x0D4A4U
#घोषणा IDT_SW_NTP6_BARLTBASE3		0x0D4A8U
#घोषणा IDT_SW_NTP6_BARUTBASE3		0x0D4ACU
#घोषणा IDT_SW_NTP6_BARSETUP4		0x0D4B0U
#घोषणा IDT_SW_NTP6_BARLIMIT4		0x0D4B4U
#घोषणा IDT_SW_NTP6_BARLTBASE4		0x0D4B8U
#घोषणा IDT_SW_NTP6_BARUTBASE4		0x0D4BCU
#घोषणा IDT_SW_NTP6_BARSETUP5		0x0D4C0U
#घोषणा IDT_SW_NTP6_BARLIMIT5		0x0D4C4U
#घोषणा IDT_SW_NTP6_BARLTBASE5		0x0D4C8U
#घोषणा IDT_SW_NTP6_BARUTBASE5		0x0D4CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP8_PCIECMDSTS		0x11004U
#घोषणा IDT_SW_NTP8_PCIELCTLSTS		0x11050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP8_NTCTL		0x11400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP8_BARSETUP0		0x11470U
#घोषणा IDT_SW_NTP8_BARLIMIT0		0x11474U
#घोषणा IDT_SW_NTP8_BARLTBASE0		0x11478U
#घोषणा IDT_SW_NTP8_BARUTBASE0		0x1147CU
#घोषणा IDT_SW_NTP8_BARSETUP1		0x11480U
#घोषणा IDT_SW_NTP8_BARLIMIT1		0x11484U
#घोषणा IDT_SW_NTP8_BARLTBASE1		0x11488U
#घोषणा IDT_SW_NTP8_BARUTBASE1		0x1148CU
#घोषणा IDT_SW_NTP8_BARSETUP2		0x11490U
#घोषणा IDT_SW_NTP8_BARLIMIT2		0x11494U
#घोषणा IDT_SW_NTP8_BARLTBASE2		0x11498U
#घोषणा IDT_SW_NTP8_BARUTBASE2		0x1149CU
#घोषणा IDT_SW_NTP8_BARSETUP3		0x114A0U
#घोषणा IDT_SW_NTP8_BARLIMIT3		0x114A4U
#घोषणा IDT_SW_NTP8_BARLTBASE3		0x114A8U
#घोषणा IDT_SW_NTP8_BARUTBASE3		0x114ACU
#घोषणा IDT_SW_NTP8_BARSETUP4		0x114B0U
#घोषणा IDT_SW_NTP8_BARLIMIT4		0x114B4U
#घोषणा IDT_SW_NTP8_BARLTBASE4		0x114B8U
#घोषणा IDT_SW_NTP8_BARUTBASE4		0x114BCU
#घोषणा IDT_SW_NTP8_BARSETUP5		0x114C0U
#घोषणा IDT_SW_NTP8_BARLIMIT5		0x114C4U
#घोषणा IDT_SW_NTP8_BARLTBASE5		0x114C8U
#घोषणा IDT_SW_NTP8_BARUTBASE5		0x114CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP12_PCIECMDSTS		0x19004U
#घोषणा IDT_SW_NTP12_PCIELCTLSTS	0x19050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP12_NTCTL		0x19400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP12_BARSETUP0		0x19470U
#घोषणा IDT_SW_NTP12_BARLIMIT0		0x19474U
#घोषणा IDT_SW_NTP12_BARLTBASE0		0x19478U
#घोषणा IDT_SW_NTP12_BARUTBASE0		0x1947CU
#घोषणा IDT_SW_NTP12_BARSETUP1		0x19480U
#घोषणा IDT_SW_NTP12_BARLIMIT1		0x19484U
#घोषणा IDT_SW_NTP12_BARLTBASE1		0x19488U
#घोषणा IDT_SW_NTP12_BARUTBASE1		0x1948CU
#घोषणा IDT_SW_NTP12_BARSETUP2		0x19490U
#घोषणा IDT_SW_NTP12_BARLIMIT2		0x19494U
#घोषणा IDT_SW_NTP12_BARLTBASE2		0x19498U
#घोषणा IDT_SW_NTP12_BARUTBASE2		0x1949CU
#घोषणा IDT_SW_NTP12_BARSETUP3		0x194A0U
#घोषणा IDT_SW_NTP12_BARLIMIT3		0x194A4U
#घोषणा IDT_SW_NTP12_BARLTBASE3		0x194A8U
#घोषणा IDT_SW_NTP12_BARUTBASE3		0x194ACU
#घोषणा IDT_SW_NTP12_BARSETUP4		0x194B0U
#घोषणा IDT_SW_NTP12_BARLIMIT4		0x194B4U
#घोषणा IDT_SW_NTP12_BARLTBASE4		0x194B8U
#घोषणा IDT_SW_NTP12_BARUTBASE4		0x194BCU
#घोषणा IDT_SW_NTP12_BARSETUP5		0x194C0U
#घोषणा IDT_SW_NTP12_BARLIMIT5		0x194C4U
#घोषणा IDT_SW_NTP12_BARLTBASE5		0x194C8U
#घोषणा IDT_SW_NTP12_BARUTBASE5		0x194CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP16_PCIECMDSTS		0x21004U
#घोषणा IDT_SW_NTP16_PCIELCTLSTS	0x21050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP16_NTCTL		0x21400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP16_BARSETUP0		0x21470U
#घोषणा IDT_SW_NTP16_BARLIMIT0		0x21474U
#घोषणा IDT_SW_NTP16_BARLTBASE0		0x21478U
#घोषणा IDT_SW_NTP16_BARUTBASE0		0x2147CU
#घोषणा IDT_SW_NTP16_BARSETUP1		0x21480U
#घोषणा IDT_SW_NTP16_BARLIMIT1		0x21484U
#घोषणा IDT_SW_NTP16_BARLTBASE1		0x21488U
#घोषणा IDT_SW_NTP16_BARUTBASE1		0x2148CU
#घोषणा IDT_SW_NTP16_BARSETUP2		0x21490U
#घोषणा IDT_SW_NTP16_BARLIMIT2		0x21494U
#घोषणा IDT_SW_NTP16_BARLTBASE2		0x21498U
#घोषणा IDT_SW_NTP16_BARUTBASE2		0x2149CU
#घोषणा IDT_SW_NTP16_BARSETUP3		0x214A0U
#घोषणा IDT_SW_NTP16_BARLIMIT3		0x214A4U
#घोषणा IDT_SW_NTP16_BARLTBASE3		0x214A8U
#घोषणा IDT_SW_NTP16_BARUTBASE3		0x214ACU
#घोषणा IDT_SW_NTP16_BARSETUP4		0x214B0U
#घोषणा IDT_SW_NTP16_BARLIMIT4		0x214B4U
#घोषणा IDT_SW_NTP16_BARLTBASE4		0x214B8U
#घोषणा IDT_SW_NTP16_BARUTBASE4		0x214BCU
#घोषणा IDT_SW_NTP16_BARSETUP5		0x214C0U
#घोषणा IDT_SW_NTP16_BARLIMIT5		0x214C4U
#घोषणा IDT_SW_NTP16_BARLTBASE5		0x214C8U
#घोषणा IDT_SW_NTP16_BARUTBASE5		0x214CCU
/* PCI Express command/status and link control/status रेजिस्टरs (WORD+WORD) */
#घोषणा IDT_SW_NTP20_PCIECMDSTS		0x29004U
#घोषणा IDT_SW_NTP20_PCIELCTLSTS	0x29050U
/* NT-function control रेजिस्टर		(DWORD) */
#घोषणा IDT_SW_NTP20_NTCTL		0x29400U
/* BAR setup/limit/base address रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_NTP20_BARSETUP0		0x29470U
#घोषणा IDT_SW_NTP20_BARLIMIT0		0x29474U
#घोषणा IDT_SW_NTP20_BARLTBASE0		0x29478U
#घोषणा IDT_SW_NTP20_BARUTBASE0		0x2947CU
#घोषणा IDT_SW_NTP20_BARSETUP1		0x29480U
#घोषणा IDT_SW_NTP20_BARLIMIT1		0x29484U
#घोषणा IDT_SW_NTP20_BARLTBASE1		0x29488U
#घोषणा IDT_SW_NTP20_BARUTBASE1		0x2948CU
#घोषणा IDT_SW_NTP20_BARSETUP2		0x29490U
#घोषणा IDT_SW_NTP20_BARLIMIT2		0x29494U
#घोषणा IDT_SW_NTP20_BARLTBASE2		0x29498U
#घोषणा IDT_SW_NTP20_BARUTBASE2		0x2949CU
#घोषणा IDT_SW_NTP20_BARSETUP3		0x294A0U
#घोषणा IDT_SW_NTP20_BARLIMIT3		0x294A4U
#घोषणा IDT_SW_NTP20_BARLTBASE3		0x294A8U
#घोषणा IDT_SW_NTP20_BARUTBASE3		0x294ACU
#घोषणा IDT_SW_NTP20_BARSETUP4		0x294B0U
#घोषणा IDT_SW_NTP20_BARLIMIT4		0x294B4U
#घोषणा IDT_SW_NTP20_BARLTBASE4		0x294B8U
#घोषणा IDT_SW_NTP20_BARUTBASE4		0x294BCU
#घोषणा IDT_SW_NTP20_BARSETUP5		0x294C0U
#घोषणा IDT_SW_NTP20_BARLIMIT5		0x294C4U
#घोषणा IDT_SW_NTP20_BARLTBASE5		0x294C8U
#घोषणा IDT_SW_NTP20_BARUTBASE5		0x294CCU
/* IDT PCIe-चयन control रेजिस्टर	(DWORD) */
#घोषणा IDT_SW_CTL			0x3E000U
/* Boot Configuration Vector Status	(DWORD) */
#घोषणा IDT_SW_BCVSTS			0x3E004U
/* Port Clocking Mode			(DWORD) */
#घोषणा IDT_SW_PCLKMODE			0x3E008U
/* Reset Drain Delay			(DWORD) */
#घोषणा IDT_SW_RDRAINDELAY		0x3E080U
/* Port Operating Mode Change Drain Delay (DWORD) */
#घोषणा IDT_SW_POMCDELAY		0x3E084U
/* Side Effect Delay			(DWORD) */
#घोषणा IDT_SW_SEDELAY			0x3E088U
/* Upstream Secondary Bus Reset Delay	(DWORD) */
#घोषणा IDT_SW_SSBRDELAY		0x3E08CU
/* Switch partition N Control/Status/Failover रेजिस्टरs */
#घोषणा IDT_SW_SWPART0CTL		0x3E100U
#घोषणा IDT_SW_SWPART0STS		0x3E104U
#घोषणा IDT_SW_SWPART0FCTL		0x3E108U
#घोषणा IDT_SW_SWPART1CTL		0x3E120U
#घोषणा IDT_SW_SWPART1STS		0x3E124U
#घोषणा IDT_SW_SWPART1FCTL		0x3E128U
#घोषणा IDT_SW_SWPART2CTL		0x3E140U
#घोषणा IDT_SW_SWPART2STS		0x3E144U
#घोषणा IDT_SW_SWPART2FCTL		0x3E148U
#घोषणा IDT_SW_SWPART3CTL		0x3E160U
#घोषणा IDT_SW_SWPART3STS		0x3E164U
#घोषणा IDT_SW_SWPART3FCTL		0x3E168U
#घोषणा IDT_SW_SWPART4CTL		0x3E180U
#घोषणा IDT_SW_SWPART4STS		0x3E184U
#घोषणा IDT_SW_SWPART4FCTL		0x3E188U
#घोषणा IDT_SW_SWPART5CTL		0x3E1A0U
#घोषणा IDT_SW_SWPART5STS		0x3E1A4U
#घोषणा IDT_SW_SWPART5FCTL		0x3E1A8U
#घोषणा IDT_SW_SWPART6CTL		0x3E1C0U
#घोषणा IDT_SW_SWPART6STS		0x3E1C4U
#घोषणा IDT_SW_SWPART6FCTL		0x3E1C8U
#घोषणा IDT_SW_SWPART7CTL		0x3E1E0U
#घोषणा IDT_SW_SWPART7STS		0x3E1E4U
#घोषणा IDT_SW_SWPART7FCTL		0x3E1E8U
/* Switch port N control and status रेजिस्टरs */
#घोषणा IDT_SW_SWPORT0CTL		0x3E200U
#घोषणा IDT_SW_SWPORT0STS		0x3E204U
#घोषणा IDT_SW_SWPORT0FCTL		0x3E208U
#घोषणा IDT_SW_SWPORT2CTL		0x3E240U
#घोषणा IDT_SW_SWPORT2STS		0x3E244U
#घोषणा IDT_SW_SWPORT2FCTL		0x3E248U
#घोषणा IDT_SW_SWPORT4CTL		0x3E280U
#घोषणा IDT_SW_SWPORT4STS		0x3E284U
#घोषणा IDT_SW_SWPORT4FCTL		0x3E288U
#घोषणा IDT_SW_SWPORT6CTL		0x3E2C0U
#घोषणा IDT_SW_SWPORT6STS		0x3E2C4U
#घोषणा IDT_SW_SWPORT6FCTL		0x3E2C8U
#घोषणा IDT_SW_SWPORT8CTL		0x3E300U
#घोषणा IDT_SW_SWPORT8STS		0x3E304U
#घोषणा IDT_SW_SWPORT8FCTL		0x3E308U
#घोषणा IDT_SW_SWPORT12CTL		0x3E380U
#घोषणा IDT_SW_SWPORT12STS		0x3E384U
#घोषणा IDT_SW_SWPORT12FCTL		0x3E388U
#घोषणा IDT_SW_SWPORT16CTL		0x3E400U
#घोषणा IDT_SW_SWPORT16STS		0x3E404U
#घोषणा IDT_SW_SWPORT16FCTL		0x3E408U
#घोषणा IDT_SW_SWPORT20CTL		0x3E480U
#घोषणा IDT_SW_SWPORT20STS		0x3E484U
#घोषणा IDT_SW_SWPORT20FCTL		0x3E488U
/* Switch Event रेजिस्टरs */
/* Switch Event Status/Mask/Partition mask (DWORD) */
#घोषणा IDT_SW_SESTS			0x3EC00U
#घोषणा IDT_SW_SEMSK			0x3EC04U
#घोषणा IDT_SW_SEPMSK			0x3EC08U
/* Switch Event Link Up/Down Status/Mask (DWORD) */
#घोषणा IDT_SW_SELINKUPSTS		0x3EC0CU
#घोषणा IDT_SW_SELINKUPMSK		0x3EC10U
#घोषणा IDT_SW_SELINKDNSTS		0x3EC14U
#घोषणा IDT_SW_SELINKDNMSK		0x3EC18U
/* Switch Event Fundamental Reset Status/Mask (DWORD) */
#घोषणा IDT_SW_SEFRSTSTS		0x3EC1CU
#घोषणा IDT_SW_SEFRSTMSK		0x3EC20U
/* Switch Event Hot Reset Status/Mask	(DWORD) */
#घोषणा IDT_SW_SEHRSTSTS		0x3EC24U
#घोषणा IDT_SW_SEHRSTMSK		0x3EC28U
/* Switch Event Failover Mask		(DWORD) */
#घोषणा IDT_SW_SEFOVRMSK		0x3EC2CU
/* Switch Event Global Signal Status/Mask (DWORD) */
#घोषणा IDT_SW_SEGSIGSTS		0x3EC30U
#घोषणा IDT_SW_SEGSIGMSK		0x3EC34U
/* NT Global Doorbell Status		(DWORD) */
#घोषणा IDT_SW_GDBELLSTS		0x3EC3CU
/* Switch partition N message M control (msgs routing table) (DWORD) */
#घोषणा IDT_SW_SWP0MSGCTL0		0x3EE00U
#घोषणा IDT_SW_SWP1MSGCTL0		0x3EE04U
#घोषणा IDT_SW_SWP2MSGCTL0		0x3EE08U
#घोषणा IDT_SW_SWP3MSGCTL0		0x3EE0CU
#घोषणा IDT_SW_SWP4MSGCTL0		0x3EE10U
#घोषणा IDT_SW_SWP5MSGCTL0		0x3EE14U
#घोषणा IDT_SW_SWP6MSGCTL0		0x3EE18U
#घोषणा IDT_SW_SWP7MSGCTL0		0x3EE1CU
#घोषणा IDT_SW_SWP0MSGCTL1		0x3EE20U
#घोषणा IDT_SW_SWP1MSGCTL1		0x3EE24U
#घोषणा IDT_SW_SWP2MSGCTL1		0x3EE28U
#घोषणा IDT_SW_SWP3MSGCTL1		0x3EE2CU
#घोषणा IDT_SW_SWP4MSGCTL1		0x3EE30U
#घोषणा IDT_SW_SWP5MSGCTL1		0x3EE34U
#घोषणा IDT_SW_SWP6MSGCTL1		0x3EE38U
#घोषणा IDT_SW_SWP7MSGCTL1		0x3EE3CU
#घोषणा IDT_SW_SWP0MSGCTL2		0x3EE40U
#घोषणा IDT_SW_SWP1MSGCTL2		0x3EE44U
#घोषणा IDT_SW_SWP2MSGCTL2		0x3EE48U
#घोषणा IDT_SW_SWP3MSGCTL2		0x3EE4CU
#घोषणा IDT_SW_SWP4MSGCTL2		0x3EE50U
#घोषणा IDT_SW_SWP5MSGCTL2		0x3EE54U
#घोषणा IDT_SW_SWP6MSGCTL2		0x3EE58U
#घोषणा IDT_SW_SWP7MSGCTL2		0x3EE5CU
#घोषणा IDT_SW_SWP0MSGCTL3		0x3EE60U
#घोषणा IDT_SW_SWP1MSGCTL3		0x3EE64U
#घोषणा IDT_SW_SWP2MSGCTL3		0x3EE68U
#घोषणा IDT_SW_SWP3MSGCTL3		0x3EE6CU
#घोषणा IDT_SW_SWP4MSGCTL3		0x3EE70U
#घोषणा IDT_SW_SWP5MSGCTL3		0x3EE74U
#घोषणा IDT_SW_SWP6MSGCTL3		0x3EE78U
#घोषणा IDT_SW_SWP7MSGCTL3		0x3EE7CU
/* SMBus Status and Control रेजिस्टरs	(DWORD) */
#घोषणा IDT_SW_SMBUSSTS			0x3F188U
#घोषणा IDT_SW_SMBUSCTL			0x3F18CU
/* Serial EEPROM Interface		(DWORD) */
#घोषणा IDT_SW_EEPROMINTF		0x3F190U
/* MBus I/O Expander Address N		(DWORD) */
#घोषणा IDT_SW_IOEXPADDR0		0x3F198U
#घोषणा IDT_SW_IOEXPADDR1		0x3F19CU
#घोषणा IDT_SW_IOEXPADDR2		0x3F1A0U
#घोषणा IDT_SW_IOEXPADDR3		0x3F1A4U
#घोषणा IDT_SW_IOEXPADDR4		0x3F1A8U
#घोषणा IDT_SW_IOEXPADDR5		0x3F1ACU
/* General Purpose Events Control and Status रेजिस्टरs (DWORD) */
#घोषणा IDT_SW_GPECTL			0x3F1B0U
#घोषणा IDT_SW_GPESTS			0x3F1B4U
/* Temperature sensor Control/Status/Alarm/Adjusपंचांगent/Slope रेजिस्टरs */
#घोषणा IDT_SW_TMPCTL			0x3F1D4U
#घोषणा IDT_SW_TMPSTS			0x3F1D8U
#घोषणा IDT_SW_TMPALARM			0x3F1DCU
#घोषणा IDT_SW_TMPADJ			0x3F1E0U
#घोषणा IDT_SW_TSSLOPE			0x3F1E4U
/* SMBus Configuration Block header log	(DWORD) */
#घोषणा IDT_SW_SMBUSCBHL		0x3F1E8U

/*
 * Common रेजिस्टरs related स्थिरants
 * @IDT_REG_ALIGN:	Registers alignment used in the driver
 * @IDT_REG_PCI_MAX:	Maximum PCI configuration space रेजिस्टर value
 * @IDT_REG_SW_MAX:	Maximum global रेजिस्टर value
 */
#घोषणा IDT_REG_ALIGN			4
#घोषणा IDT_REG_PCI_MAX			0x00FFFU
#घोषणा IDT_REG_SW_MAX			0x3FFFFU

/*
 * PCICMDSTS रेजिस्टर fields related स्थिरants
 * @IDT_PCICMDSTS_IOAE:	I/O access enable
 * @IDT_PCICMDSTS_MAE:	Memory access enable
 * @IDT_PCICMDSTS_BME:	Bus master enable
 */
#घोषणा IDT_PCICMDSTS_IOAE		0x00000001U
#घोषणा IDT_PCICMDSTS_MAE		0x00000002U
#घोषणा IDT_PCICMDSTS_BME		0x00000004U

/*
 * PCIEDCAP रेजिस्टर fields related स्थिरants
 * @IDT_PCIEDCAP_MPAYLOAD_MASK:	 Maximum payload size mask
 * @IDT_PCIEDCAP_MPAYLOAD_FLD:	 Maximum payload size field offset
 * @IDT_PCIEDCAP_MPAYLOAD_S128:	 Max supported payload size of 128 bytes
 * @IDT_PCIEDCAP_MPAYLOAD_S256:	 Max supported payload size of 256 bytes
 * @IDT_PCIEDCAP_MPAYLOAD_S512:	 Max supported payload size of 512 bytes
 * @IDT_PCIEDCAP_MPAYLOAD_S1024: Max supported payload size of 1024 bytes
 * @IDT_PCIEDCAP_MPAYLOAD_S2048: Max supported payload size of 2048 bytes
 */
#घोषणा IDT_PCIEDCAP_MPAYLOAD_MASK	0x00000007U
#घोषणा IDT_PCIEDCAP_MPAYLOAD_FLD	0
#घोषणा IDT_PCIEDCAP_MPAYLOAD_S128	0x00000000U
#घोषणा IDT_PCIEDCAP_MPAYLOAD_S256	0x00000001U
#घोषणा IDT_PCIEDCAP_MPAYLOAD_S512	0x00000002U
#घोषणा IDT_PCIEDCAP_MPAYLOAD_S1024	0x00000003U
#घोषणा IDT_PCIEDCAP_MPAYLOAD_S2048	0x00000004U

/*
 * PCIEDCTLSTS रेजिस्टरs fields related स्थिरants
 * @IDT_PCIEDCTL_MPS_MASK:	Maximum payload size mask
 * @IDT_PCIEDCTL_MPS_FLD:	MPS field offset
 * @IDT_PCIEDCTL_MPS_S128:	Max payload size of 128 bytes
 * @IDT_PCIEDCTL_MPS_S256:	Max payload size of 256 bytes
 * @IDT_PCIEDCTL_MPS_S512:	Max payload size of 512 bytes
 * @IDT_PCIEDCTL_MPS_S1024:	Max payload size of 1024 bytes
 * @IDT_PCIEDCTL_MPS_S2048:	Max payload size of 2048 bytes
 * @IDT_PCIEDCTL_MPS_S4096:	Max payload size of 4096 bytes
 */
#घोषणा IDT_PCIEDCTLSTS_MPS_MASK	0x000000E0U
#घोषणा IDT_PCIEDCTLSTS_MPS_FLD		5
#घोषणा IDT_PCIEDCTLSTS_MPS_S128	0x00000000U
#घोषणा IDT_PCIEDCTLSTS_MPS_S256	0x00000020U
#घोषणा IDT_PCIEDCTLSTS_MPS_S512	0x00000040U
#घोषणा IDT_PCIEDCTLSTS_MPS_S1024	0x00000060U
#घोषणा IDT_PCIEDCTLSTS_MPS_S2048	0x00000080U
#घोषणा IDT_PCIEDCTLSTS_MPS_S4096	0x000000A0U

/*
 * PCIELCAP रेजिस्टर fields related स्थिरants
 * @IDT_PCIELCAP_PORTNUM_MASK:	Port number field mask
 * @IDT_PCIELCAP_PORTNUM_FLD:	Port number field offset
 */
#घोषणा IDT_PCIELCAP_PORTNUM_MASK	0xFF000000U
#घोषणा IDT_PCIELCAP_PORTNUM_FLD	24

/*
 * PCIELCTLSTS रेजिस्टरs fields related स्थिरants
 * @IDT_PCIELSTS_CLS_MASK:	Current link speed mask
 * @IDT_PCIELSTS_CLS_FLD:	Current link speed field offset
 * @IDT_PCIELSTS_NLW_MASK:	Negotiated link width mask
 * @IDT_PCIELSTS_NLW_FLD:	Negotiated link width field offset
 * @IDT_PCIELSTS_SCLK_COM:	Common slot घड़ी configuration
 */
#घोषणा IDT_PCIELCTLSTS_CLS_MASK	0x000F0000U
#घोषणा IDT_PCIELCTLSTS_CLS_FLD		16
#घोषणा IDT_PCIELCTLSTS_NLW_MASK	0x03F00000U
#घोषणा IDT_PCIELCTLSTS_NLW_FLD		20
#घोषणा IDT_PCIELCTLSTS_SCLK_COM	0x10000000U

/*
 * NTCTL रेजिस्टर fields related स्थिरants
 * @IDT_NTCTL_IDPROTDIS:	ID Protection check disable (disable MTBL)
 * @IDT_NTCTL_CPEN:		Completion enable
 * @IDT_NTCTL_RNS:		Request no snoop processing (अगर MTBL disabled)
 * @IDT_NTCTL_ATP:		Address type processing (अगर MTBL disabled)
 */
#घोषणा IDT_NTCTL_IDPROTDIS		0x00000001U
#घोषणा IDT_NTCTL_CPEN			0x00000002U
#घोषणा IDT_NTCTL_RNS			0x00000004U
#घोषणा IDT_NTCTL_ATP			0x00000008U

/*
 * NTINTSTS रेजिस्टर fields related स्थिरants
 * @IDT_NTINTSTS_MSG:		Message पूर्णांकerrupt bit
 * @IDT_NTINTSTS_DBELL:		Doorbell पूर्णांकerrupt bit
 * @IDT_NTINTSTS_SEVENT:	Switch Event पूर्णांकerrupt bit
 * @IDT_NTINTSTS_TMPSENSOR:	Temperature sensor पूर्णांकerrupt bit
 */
#घोषणा IDT_NTINTSTS_MSG		0x00000001U
#घोषणा IDT_NTINTSTS_DBELL		0x00000002U
#घोषणा IDT_NTINTSTS_SEVENT		0x00000008U
#घोषणा IDT_NTINTSTS_TMPSENSOR		0x00000080U

/*
 * NTINTMSK रेजिस्टर fields related स्थिरants
 * @IDT_NTINTMSK_MSG:		Message पूर्णांकerrupt mask bit
 * @IDT_NTINTMSK_DBELL:		Doorbell पूर्णांकerrupt mask bit
 * @IDT_NTINTMSK_SEVENT:	Switch Event पूर्णांकerrupt mask bit
 * @IDT_NTINTMSK_TMPSENSOR:	Temperature sensor पूर्णांकerrupt mask bit
 * @IDT_NTINTMSK_ALL:		NTB-related पूर्णांकerrupts mask
 */
#घोषणा IDT_NTINTMSK_MSG		0x00000001U
#घोषणा IDT_NTINTMSK_DBELL		0x00000002U
#घोषणा IDT_NTINTMSK_SEVENT		0x00000008U
#घोषणा IDT_NTINTMSK_TMPSENSOR		0x00000080U
#घोषणा IDT_NTINTMSK_ALL \
	(IDT_NTINTMSK_MSG | IDT_NTINTMSK_DBELL | IDT_NTINTMSK_SEVENT)

/*
 * NTGSIGNAL रेजिस्टर fields related स्थिरants
 * @IDT_NTGSIGNAL_SET:	Set global संकेत of the local partition
 */
#घोषणा IDT_NTGSIGNAL_SET		0x00000001U

/*
 * BARSETUP रेजिस्टर fields related स्थिरants
 * @IDT_BARSETUP_TYPE_MASK:	Mask of the TYPE field
 * @IDT_BARSETUP_TYPE_32:	32-bit addressing BAR
 * @IDT_BARSETUP_TYPE_64:	64-bit addressing BAR
 * @IDT_BARSETUP_PREF:		Value of the BAR prefetchable field
 * @IDT_BARSETUP_SIZE_MASK:	Mask of the SIZE field
 * @IDT_BARSETUP_SIZE_FLD:	SIZE field offset
 * @IDT_BARSETUP_SIZE_CFG:	SIZE field value in हाल of config space MODE
 * @IDT_BARSETUP_MODE_CFG:	Configuration space BAR mode
 * @IDT_BARSETUP_ATRAN_MASK:	ATRAN field mask
 * @IDT_BARSETUP_ATRAN_FLD:	ATRAN field offset
 * @IDT_BARSETUP_ATRAN_सूची:	Direct address translation memory winकरोw
 * @IDT_BARSETUP_ATRAN_LUT12:	12-entry lookup table
 * @IDT_BARSETUP_ATRAN_LUT24:	24-entry lookup table
 * @IDT_BARSETUP_TPART_MASK:	TPART field mask
 * @IDT_BARSETUP_TPART_FLD:	TPART field offset
 * @IDT_BARSETUP_EN:		BAR enable bit
 */
#घोषणा IDT_BARSETUP_TYPE_MASK		0x00000006U
#घोषणा IDT_BARSETUP_TYPE_FLD		0
#घोषणा IDT_BARSETUP_TYPE_32		0x00000000U
#घोषणा IDT_BARSETUP_TYPE_64		0x00000004U
#घोषणा IDT_BARSETUP_PREF		0x00000008U
#घोषणा IDT_BARSETUP_SIZE_MASK		0x000003F0U
#घोषणा IDT_BARSETUP_SIZE_FLD		4
#घोषणा IDT_BARSETUP_SIZE_CFG		0x000000C0U
#घोषणा IDT_BARSETUP_MODE_CFG		0x00000400U
#घोषणा IDT_BARSETUP_ATRAN_MASK		0x00001800U
#घोषणा IDT_BARSETUP_ATRAN_FLD		11
#घोषणा IDT_BARSETUP_ATRAN_सूची		0x00000000U
#घोषणा IDT_BARSETUP_ATRAN_LUT12	0x00000800U
#घोषणा IDT_BARSETUP_ATRAN_LUT24	0x00001000U
#घोषणा IDT_BARSETUP_TPART_MASK		0x0000E000U
#घोषणा IDT_BARSETUP_TPART_FLD		13
#घोषणा IDT_BARSETUP_EN			0x80000000U

/*
 * NTMTBLDATA रेजिस्टर fields related स्थिरants
 * @IDT_NTMTBLDATA_VALID:	Set the MTBL entry being valid
 * @IDT_NTMTBLDATA_REQID_MASK:	Bus:Device:Function field mask
 * @IDT_NTMTBLDATA_REQID_FLD:	Bus:Device:Function field offset
 * @IDT_NTMTBLDATA_PART_MASK:	Partition field mask
 * @IDT_NTMTBLDATA_PART_FLD:	Partition field offset
 * @IDT_NTMTBLDATA_ATP_TRANS:	Enable AT field translation on request TLPs
 * @IDT_NTMTBLDATA_CNS_INV:	Enable No Snoop attribute inversion of
 *				Completion TLPs
 * @IDT_NTMTBLDATA_RNS_INV:	Enable No Snoop attribute inversion of
 *				Request TLPs
 */
#घोषणा IDT_NTMTBLDATA_VALID		0x00000001U
#घोषणा IDT_NTMTBLDATA_REQID_MASK	0x0001FFFEU
#घोषणा IDT_NTMTBLDATA_REQID_FLD	1
#घोषणा IDT_NTMTBLDATA_PART_MASK	0x000E0000U
#घोषणा IDT_NTMTBLDATA_PART_FLD		17
#घोषणा IDT_NTMTBLDATA_ATP_TRANS	0x20000000U
#घोषणा IDT_NTMTBLDATA_CNS_INV		0x40000000U
#घोषणा IDT_NTMTBLDATA_RNS_INV		0x80000000U

/*
 * REQIDCAP रेजिस्टर fields related स्थिरants
 * @IDT_REQIDCAP_REQID_MASK:	Request ID field mask
 * @IDT_REQIDCAP_REQID_FLD:	Request ID field offset
 */
#घोषणा IDT_REQIDCAP_REQID_MASK		0x0000FFFFU
#घोषणा IDT_REQIDCAP_REQID_FLD		0

/*
 * LUTOFFSET रेजिस्टर fields related स्थिरants
 * @IDT_LUTOFFSET_INDEX_MASK:	Lookup table index field mask
 * @IDT_LUTOFFSET_INDEX_FLD:	Lookup table index field offset
 * @IDT_LUTOFFSET_BAR_MASK:	Lookup table BAR select field mask
 * @IDT_LUTOFFSET_BAR_FLD:	Lookup table BAR select field offset
 */
#घोषणा IDT_LUTOFFSET_INDEX_MASK	0x0000001FU
#घोषणा IDT_LUTOFFSET_INDEX_FLD		0
#घोषणा IDT_LUTOFFSET_BAR_MASK		0x00000700U
#घोषणा IDT_LUTOFFSET_BAR_FLD		8

/*
 * LUTUDATA रेजिस्टर fields related स्थिरants
 * @IDT_LUTUDATA_PART_MASK:	Partition field mask
 * @IDT_LUTUDATA_PART_FLD:	Partition field offset
 * @IDT_LUTUDATA_VALID:		Lookup table entry valid bit
 */
#घोषणा IDT_LUTUDATA_PART_MASK		0x0000000FU
#घोषणा IDT_LUTUDATA_PART_FLD		0
#घोषणा IDT_LUTUDATA_VALID		0x80000000U

/*
 * SWPARTxSTS रेजिस्टर fields related स्थिरants
 * @IDT_SWPARTxSTS_SCI:		Switch partition state change initiated
 * @IDT_SWPARTxSTS_SCC:		Switch partition state change completed
 * @IDT_SWPARTxSTS_STATE_MASK:	Switch partition state mask
 * @IDT_SWPARTxSTS_STATE_FLD:	Switch partition state field offset
 * @IDT_SWPARTxSTS_STATE_DIS:	Switch partition disabled
 * @IDT_SWPARTxSTS_STATE_ACT:	Switch partition enabled
 * @IDT_SWPARTxSTS_STATE_RES:	Switch partition in reset
 * @IDT_SWPARTxSTS_US:		Switch partition has upstream port
 * @IDT_SWPARTxSTS_USID_MASK:	Switch partition upstream port ID mask
 * @IDT_SWPARTxSTS_USID_FLD:	Switch partition upstream port ID field offset
 * @IDT_SWPARTxSTS_NT:		Upstream port has NT function
 * @IDT_SWPARTxSTS_DMA:		Upstream port has DMA function
 */
#घोषणा IDT_SWPARTxSTS_SCI		0x00000001U
#घोषणा IDT_SWPARTxSTS_SCC		0x00000002U
#घोषणा IDT_SWPARTxSTS_STATE_MASK	0x00000060U
#घोषणा IDT_SWPARTxSTS_STATE_FLD	5
#घोषणा IDT_SWPARTxSTS_STATE_DIS	0x00000000U
#घोषणा IDT_SWPARTxSTS_STATE_ACT	0x00000020U
#घोषणा IDT_SWPARTxSTS_STATE_RES	0x00000060U
#घोषणा IDT_SWPARTxSTS_US		0x00000100U
#घोषणा IDT_SWPARTxSTS_USID_MASK	0x00003E00U
#घोषणा IDT_SWPARTxSTS_USID_FLD		9
#घोषणा IDT_SWPARTxSTS_NT		0x00004000U
#घोषणा IDT_SWPARTxSTS_DMA		0x00008000U

/*
 * SWPORTxSTS रेजिस्टर fields related स्थिरants
 * @IDT_SWPORTxSTS_OMCI:	Operation mode change initiated
 * @IDT_SWPORTxSTS_OMCC:	Operation mode change completed
 * @IDT_SWPORTxSTS_LINKUP:	Link up status
 * @IDT_SWPORTxSTS_DS:		Port lanes behave as करोwnstream lanes
 * @IDT_SWPORTxSTS_MODE_MASK:	Port mode field mask
 * @IDT_SWPORTxSTS_MODE_FLD:	Port mode field offset
 * @IDT_SWPORTxSTS_MODE_DIS:	Port mode - disabled
 * @IDT_SWPORTxSTS_MODE_DS:	Port mode - करोwnstream चयन port
 * @IDT_SWPORTxSTS_MODE_US:	Port mode - upstream चयन port
 * @IDT_SWPORTxSTS_MODE_NT:	Port mode - NT function
 * @IDT_SWPORTxSTS_MODE_USNT:	Port mode - upstream चयन port with NTB
 * @IDT_SWPORTxSTS_MODE_UNAT:	Port mode - unattached
 * @IDT_SWPORTxSTS_MODE_USDMA:	Port mode - upstream चयन port with DMA
 * @IDT_SWPORTxSTS_MODE_USNTDMA:Port mode - upstream port with NTB and DMA
 * @IDT_SWPORTxSTS_MODE_NTDMA:	Port mode - NT function with DMA
 * @IDT_SWPORTxSTS_SWPART_MASK:	Port partition field mask
 * @IDT_SWPORTxSTS_SWPART_FLD:	Port partition field offset
 * @IDT_SWPORTxSTS_DEVNUM_MASK:	Port device number field mask
 * @IDT_SWPORTxSTS_DEVNUM_FLD:	Port device number field offset
 */
#घोषणा IDT_SWPORTxSTS_OMCI		0x00000001U
#घोषणा IDT_SWPORTxSTS_OMCC		0x00000002U
#घोषणा IDT_SWPORTxSTS_LINKUP		0x00000010U
#घोषणा IDT_SWPORTxSTS_DS		0x00000020U
#घोषणा IDT_SWPORTxSTS_MODE_MASK	0x000003C0U
#घोषणा IDT_SWPORTxSTS_MODE_FLD		6
#घोषणा IDT_SWPORTxSTS_MODE_DIS		0x00000000U
#घोषणा IDT_SWPORTxSTS_MODE_DS		0x00000040U
#घोषणा IDT_SWPORTxSTS_MODE_US		0x00000080U
#घोषणा IDT_SWPORTxSTS_MODE_NT		0x000000C0U
#घोषणा IDT_SWPORTxSTS_MODE_USNT	0x00000100U
#घोषणा IDT_SWPORTxSTS_MODE_UNAT	0x00000140U
#घोषणा IDT_SWPORTxSTS_MODE_USDMA	0x00000180U
#घोषणा IDT_SWPORTxSTS_MODE_USNTDMA	0x000001C0U
#घोषणा IDT_SWPORTxSTS_MODE_NTDMA	0x00000200U
#घोषणा IDT_SWPORTxSTS_SWPART_MASK	0x00001C00U
#घोषणा IDT_SWPORTxSTS_SWPART_FLD	10
#घोषणा IDT_SWPORTxSTS_DEVNUM_MASK	0x001F0000U
#घोषणा IDT_SWPORTxSTS_DEVNUM_FLD	16

/*
 * SEMSK रेजिस्टर fields related स्थिरants
 * @IDT_SEMSK_LINKUP:	Link Up event mask bit
 * @IDT_SEMSK_LINKDN:	Link Down event mask bit
 * @IDT_SEMSK_GSIGNAL:	Global Signal event mask bit
 */
#घोषणा IDT_SEMSK_LINKUP		0x00000001U
#घोषणा IDT_SEMSK_LINKDN		0x00000002U
#घोषणा IDT_SEMSK_GSIGNAL		0x00000020U

/*
 * SWPxMSGCTL रेजिस्टर fields related स्थिरants
 * @IDT_SWPxMSGCTL_REG_MASK:	Register select field mask
 * @IDT_SWPxMSGCTL_REG_FLD:	Register select field offset
 * @IDT_SWPxMSGCTL_PART_MASK:	Partition select field mask
 * @IDT_SWPxMSGCTL_PART_FLD:	Partition select field offset
 */
#घोषणा IDT_SWPxMSGCTL_REG_MASK		0x00000003U
#घोषणा IDT_SWPxMSGCTL_REG_FLD		0
#घोषणा IDT_SWPxMSGCTL_PART_MASK	0x00000070U
#घोषणा IDT_SWPxMSGCTL_PART_FLD		4

/*
 * TMPCTL रेजिस्टर fields related स्थिरants
 * @IDT_TMPCTL_LTH_MASK:	Low temperature threshold field mask
 * @IDT_TMPCTL_LTH_FLD:		Low temperature threshold field offset
 * @IDT_TMPCTL_MTH_MASK:	Middle temperature threshold field mask
 * @IDT_TMPCTL_MTH_FLD:		Middle temperature threshold field offset
 * @IDT_TMPCTL_HTH_MASK:	High temperature threshold field mask
 * @IDT_TMPCTL_HTH_FLD:		High temperature threshold field offset
 * @IDT_TMPCTL_PDOWN:		Temperature sensor घातer करोwn
 */
#घोषणा IDT_TMPCTL_LTH_MASK		0x000000FFU
#घोषणा IDT_TMPCTL_LTH_FLD		0
#घोषणा IDT_TMPCTL_MTH_MASK		0x0000FF00U
#घोषणा IDT_TMPCTL_MTH_FLD		8
#घोषणा IDT_TMPCTL_HTH_MASK		0x00FF0000U
#घोषणा IDT_TMPCTL_HTH_FLD		16
#घोषणा IDT_TMPCTL_PDOWN		0x80000000U

/*
 * TMPSTS रेजिस्टर fields related स्थिरants
 * @IDT_TMPSTS_TEMP_MASK:	Current temperature field mask
 * @IDT_TMPSTS_TEMP_FLD:	Current temperature field offset
 * @IDT_TMPSTS_LTEMP_MASK:	Lowest temperature field mask
 * @IDT_TMPSTS_LTEMP_FLD:	Lowest temperature field offset
 * @IDT_TMPSTS_HTEMP_MASK:	Highest temperature field mask
 * @IDT_TMPSTS_HTEMP_FLD:	Highest temperature field offset
 */
#घोषणा IDT_TMPSTS_TEMP_MASK		0x000000FFU
#घोषणा IDT_TMPSTS_TEMP_FLD		0
#घोषणा IDT_TMPSTS_LTEMP_MASK		0x0000FF00U
#घोषणा IDT_TMPSTS_LTEMP_FLD		8
#घोषणा IDT_TMPSTS_HTEMP_MASK		0x00FF0000U
#घोषणा IDT_TMPSTS_HTEMP_FLD		16

/*
 * TMPALARM रेजिस्टर fields related स्थिरants
 * @IDT_TMPALARM_LTEMP_MASK:	Lowest temperature field mask
 * @IDT_TMPALARM_LTEMP_FLD:	Lowest temperature field offset
 * @IDT_TMPALARM_HTEMP_MASK:	Highest temperature field mask
 * @IDT_TMPALARM_HTEMP_FLD:	Highest temperature field offset
 * @IDT_TMPALARM_IRQ_MASK:	Alarm IRQ status mask
 */
#घोषणा IDT_TMPALARM_LTEMP_MASK		0x0000FF00U
#घोषणा IDT_TMPALARM_LTEMP_FLD		8
#घोषणा IDT_TMPALARM_HTEMP_MASK		0x00FF0000U
#घोषणा IDT_TMPALARM_HTEMP_FLD		16
#घोषणा IDT_TMPALARM_IRQ_MASK		0x3F000000U

/*
 * TMPADJ रेजिस्टर fields related स्थिरants
 * @IDT_TMPADJ_OFFSET_MASK:	Temperature value offset field mask
 * @IDT_TMPADJ_OFFSET_FLD:	Temperature value offset field offset
 */
#घोषणा IDT_TMPADJ_OFFSET_MASK		0x000000FFU
#घोषणा IDT_TMPADJ_OFFSET_FLD		0

/*
 * Helper macro to get/set the corresponding field value
 * @GET_FIELD:		Retrieve the value of the corresponding field
 * @SET_FIELD:		Set the specअगरied field up
 * @IS_FLD_SET:		Check whether a field is set with value
 */
#घोषणा GET_FIELD(field, data) \
	(((u32)(data) & IDT_ ##field## _MASK) >> IDT_ ##field## _FLD)
#घोषणा SET_FIELD(field, data, value) \
	(((u32)(data) & ~IDT_ ##field## _MASK) | \
	 ((u32)(value) << IDT_ ##field## _FLD))
#घोषणा IS_FLD_SET(field, data, value) \
	(((u32)(data) & IDT_ ##field## _MASK) == IDT_ ##field## _ ##value)

/*
 * Useful रेजिस्टरs masks:
 * @IDT_DBELL_MASK:	Doorbell bits mask
 * @IDT_OUTMSG_MASK:	Out messages status bits mask
 * @IDT_INMSG_MASK:	In messages status bits mask
 * @IDT_MSG_MASK:	Any message status bits mask
 */
#घोषणा IDT_DBELL_MASK		((u32)0xFFFFFFFFU)
#घोषणा IDT_OUTMSG_MASK		((u32)0x0000000FU)
#घोषणा IDT_INMSG_MASK		((u32)0x000F0000U)
#घोषणा IDT_MSG_MASK		(IDT_INMSG_MASK | IDT_OUTMSG_MASK)

/*
 * Number of IDT NTB resources:
 * @IDT_MSG_CNT:	Number of Message रेजिस्टरs
 * @IDT_BAR_CNT:	Number of BARs of each port
 * @IDT_MTBL_ENTRY_CNT:	Number mapping table entries
 */
#घोषणा IDT_MSG_CNT		4
#घोषणा IDT_BAR_CNT		6
#घोषणा IDT_MTBL_ENTRY_CNT	64

/*
 * General IDT PCIe-चयन स्थिरant
 * @IDT_MAX_NR_PORTS:	Maximum number of ports per IDT PCIe-चयन
 * @IDT_MAX_NR_PARTS:	Maximum number of partitions per IDT PCIe-चयन
 * @IDT_MAX_NR_PEERS:	Maximum number of NT-peers per IDT PCIe-चयन
 * @IDT_MAX_NR_MWS:	Maximum number of Memory Wiकरोws
 * @IDT_PCIE_REGSIZE:	Size of the रेजिस्टरs in bytes
 * @IDT_TRANS_ALIGN:	Alignment of translated base address
 * @IDT_सूची_SIZE_ALIGN:	Alignment of size setting क्रम direct translated MWs.
 *			Even though the lower 10 bits are reserved, they are
 *			treated by IDT as one's so basically there is no any
 *			alignment of size limit क्रम सूची address translation.
 */
#घोषणा IDT_MAX_NR_PORTS	24
#घोषणा IDT_MAX_NR_PARTS	8
#घोषणा IDT_MAX_NR_PEERS	8
#घोषणा IDT_MAX_NR_MWS		29
#घोषणा IDT_PCIE_REGSIZE	4
#घोषणा IDT_TRANS_ALIGN		4
#घोषणा IDT_सूची_SIZE_ALIGN	1

/*
 * IDT PCIe-चयन temperature sensor value limits
 * @IDT_TEMP_MIN_MDEG:	Minimal पूर्णांकeger value of temperature
 * @IDT_TEMP_MAX_MDEG:	Maximal पूर्णांकeger value of temperature
 * @IDT_TEMP_MIN_OFFSET:Minimal पूर्णांकeger value of temperature offset
 * @IDT_TEMP_MAX_OFFSET:Maximal पूर्णांकeger value of temperature offset
 */
#घोषणा IDT_TEMP_MIN_MDEG	0
#घोषणा IDT_TEMP_MAX_MDEG	127500
#घोषणा IDT_TEMP_MIN_OFFSET	-64000
#घोषणा IDT_TEMP_MAX_OFFSET	63500

/*
 * Temperature sensor values क्रमागतeration
 * @IDT_TEMP_CUR:	Current temperature
 * @IDT_TEMP_LOW:	Lowest historical temperature
 * @IDT_TEMP_HIGH:	Highest historical temperature
 * @IDT_TEMP_OFFSET:	Current temperature offset
 */
क्रमागत idt_temp_val अणु
	IDT_TEMP_CUR,
	IDT_TEMP_LOW,
	IDT_TEMP_HIGH,
	IDT_TEMP_OFFSET
पूर्ण;

/*
 * IDT Memory Winकरोws type. Depending on the device settings, IDT supports
 * Direct Address Translation MW रेजिस्टरs and Lookup Table रेजिस्टरs
 * @IDT_MW_सूची:		Direct address translation
 * @IDT_MW_LUT12:	12-entry lookup table entry
 * @IDT_MW_LUT24:	24-entry lookup table entry
 *
 * NOTE These values are exactly the same as one of the BARSETUP ATRAN field
 */
क्रमागत idt_mw_type अणु
	IDT_MW_सूची = 0x0,
	IDT_MW_LUT12 = 0x1,
	IDT_MW_LUT24 = 0x2
पूर्ण;

/*
 * IDT PCIe-चयन model निजी data
 * @name:	Device name
 * @port_cnt:	Total number of NT endpoपूर्णांक ports
 * @ports:	Port ids
 */
काष्ठा idt_89hpes_cfg अणु
	अक्षर *name;
	अचिन्हित अक्षर port_cnt;
	अचिन्हित अक्षर ports[];
पूर्ण;

/*
 * Memory winकरोw configuration काष्ठाure
 * @type:	Type of the memory winकरोw (direct address translation or lookup
 *		table)
 *
 * @bar:	PCIe BAR the memory winकरोw referenced to
 * @idx:	Index of the memory winकरोw within the BAR
 *
 * @addr_align:	Alignment of translated address
 * @size_align:	Alignment of memory winकरोw size
 * @size_max:	Maximum size of memory winकरोw
 */
काष्ठा idt_mw_cfg अणु
	क्रमागत idt_mw_type type;

	अचिन्हित अक्षर bar;
	अचिन्हित अक्षर idx;

	u64 addr_align;
	u64 size_align;
	u64 size_max;
पूर्ण;

/*
 * Description काष्ठाure of peer IDT NT-functions:
 * @port:		NT-function port
 * @part:		NT-function partition
 *
 * @mw_cnt:		Number of memory winकरोws supported by NT-function
 * @mws:		Array of memory winकरोws descriptors
 */
काष्ठा idt_ntb_peer अणु
	अचिन्हित अक्षर port;
	अचिन्हित अक्षर part;

	अचिन्हित अक्षर mw_cnt;
	काष्ठा idt_mw_cfg *mws;
पूर्ण;

/*
 * Description काष्ठाure of local IDT NT-function:
 * @ntb:		Linux NTB-device description काष्ठाure
 * @swcfg:		Poपूर्णांकer to the काष्ठाure of local IDT PCIe-चयन
 *			specअगरic cofnfigurations
 *
 * @port:		Local NT-function port
 * @part:		Local NT-function partition
 *
 * @peer_cnt:		Number of peers with activated NTB-function
 * @peers:		Array of peers descripting काष्ठाures
 * @port_idx_map:	Map of port number -> peer index
 * @part_idx_map:	Map of partition number -> peer index
 *
 * @mtbl_lock:		Mapping table access lock
 *
 * @mw_cnt:		Number of memory winकरोws supported by NT-function
 * @mws:		Array of memory winकरोws descriptors
 * @lut_lock:		Lookup table access lock
 *
 * @msg_locks:		Message रेजिस्टरs mapping table lockers
 *
 * @cfgspc:		Virtual address of the memory mapped configuration
 *			space of the NT-function
 * @db_mask_lock:	Doorbell mask रेजिस्टर lock
 * @msg_mask_lock:	Message mask रेजिस्टर lock
 * @gasa_lock:		GASA रेजिस्टरs access lock
 *
 * @hwmon_mtx:		Temperature sensor पूर्णांकerface update mutex
 *
 * @dbgfs_info:		DebugFS info node
 */
काष्ठा idt_ntb_dev अणु
	काष्ठा ntb_dev ntb;
	काष्ठा idt_89hpes_cfg *swcfg;

	अचिन्हित अक्षर port;
	अचिन्हित अक्षर part;

	अचिन्हित अक्षर peer_cnt;
	काष्ठा idt_ntb_peer peers[IDT_MAX_NR_PEERS];
	अक्षर port_idx_map[IDT_MAX_NR_PORTS];
	अक्षर part_idx_map[IDT_MAX_NR_PARTS];

	spinlock_t mtbl_lock;

	अचिन्हित अक्षर mw_cnt;
	काष्ठा idt_mw_cfg *mws;
	spinlock_t lut_lock;

	spinlock_t msg_locks[IDT_MSG_CNT];

	व्योम __iomem *cfgspc;
	spinlock_t db_mask_lock;
	spinlock_t msg_mask_lock;
	spinlock_t gasa_lock;

	काष्ठा mutex hwmon_mtx;

	काष्ठा dentry *dbgfs_info;
पूर्ण;
#घोषणा to_ndev_ntb(__ntb) container_of(__ntb, काष्ठा idt_ntb_dev, ntb)

/*
 * Descriptor of the IDT PCIe-चयन BAR resources
 * @setup:	BAR setup रेजिस्टर
 * @limit:	BAR limit रेजिस्टर
 * @ltbase:	Lower translated base address
 * @utbase:	Upper translated base address
 */
काष्ठा idt_ntb_bar अणु
	अचिन्हित पूर्णांक setup;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक ltbase;
	अचिन्हित पूर्णांक utbase;
पूर्ण;

/*
 * Descriptor of the IDT PCIe-चयन message resources
 * @in:		Inbound message रेजिस्टर
 * @out:	Outbound message रेजिस्टर
 * @src:	Source of inbound message रेजिस्टर
 */
काष्ठा idt_ntb_msg अणु
	अचिन्हित पूर्णांक in;
	अचिन्हित पूर्णांक out;
	अचिन्हित पूर्णांक src;
पूर्ण;

/*
 * Descriptor of the IDT PCIe-चयन NT-function specअगरic parameters in the
 * PCI Configuration Space
 * @bars:	BARs related रेजिस्टरs
 * @msgs:	Messaging related रेजिस्टरs
 */
काष्ठा idt_ntb_regs अणु
	काष्ठा idt_ntb_bar bars[IDT_BAR_CNT];
	काष्ठा idt_ntb_msg msgs[IDT_MSG_CNT];
पूर्ण;

/*
 * Descriptor of the IDT PCIe-चयन port specअगरic parameters in the
 * Global Configuration Space
 * @pcicmdsts:	 PCI command/status रेजिस्टर
 * @pcielctlsts: PCIe link control/status
 *
 * @ctl:	Port control रेजिस्टर
 * @sts:	Port status रेजिस्टर
 *
 * @bars:	BARs related रेजिस्टरs
 */
काष्ठा idt_ntb_port अणु
	अचिन्हित पूर्णांक pcicmdsts;
	अचिन्हित पूर्णांक pcielctlsts;
	अचिन्हित पूर्णांक ntctl;

	अचिन्हित पूर्णांक ctl;
	अचिन्हित पूर्णांक sts;

	काष्ठा idt_ntb_bar bars[IDT_BAR_CNT];
पूर्ण;

/*
 * Descriptor of the IDT PCIe-चयन partition specअगरic parameters.
 * @ctl:	Partition control रेजिस्टर in the Global Address Space
 * @sts:	Partition status रेजिस्टर in the Global Address Space
 * @msgctl:	Messages control रेजिस्टरs
 */
काष्ठा idt_ntb_part अणु
	अचिन्हित पूर्णांक ctl;
	अचिन्हित पूर्णांक sts;
	अचिन्हित पूर्णांक msgctl[IDT_MSG_CNT];
पूर्ण;

#पूर्ण_अगर /* NTB_HW_IDT_H */
