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

#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sizes.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/ntb.h>

#समावेश "ntb_hw_idt.h"

#घोषणा NTB_NAME	"ntb_hw_idt"
#घोषणा NTB_DESC	"IDT PCI-E Non-Transparent Bridge Driver"
#घोषणा NTB_VER		"2.0"
#घोषणा NTB_IRQNAME	"ntb_irq_idt"

MODULE_DESCRIPTION(NTB_DESC);
MODULE_VERSION(NTB_VER);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("T-platforms");

/*
 * NT Endpoपूर्णांक रेजिस्टरs table simplअगरying a loop access to the functionally
 * related रेजिस्टरs
 */
अटल स्थिर काष्ठा idt_ntb_regs ntdata_tbl = अणु
	अणु अणुIDT_NT_BARSETUP0,	IDT_NT_BARLIMIT0,
	   IDT_NT_BARLTBASE0,	IDT_NT_BARUTBASE0पूर्ण,
	  अणुIDT_NT_BARSETUP1,	IDT_NT_BARLIMIT1,
	   IDT_NT_BARLTBASE1,	IDT_NT_BARUTBASE1पूर्ण,
	  अणुIDT_NT_BARSETUP2,	IDT_NT_BARLIMIT2,
	   IDT_NT_BARLTBASE2,	IDT_NT_BARUTBASE2पूर्ण,
	  अणुIDT_NT_BARSETUP3,	IDT_NT_BARLIMIT3,
	   IDT_NT_BARLTBASE3,	IDT_NT_BARUTBASE3पूर्ण,
	  अणुIDT_NT_BARSETUP4,	IDT_NT_BARLIMIT4,
	   IDT_NT_BARLTBASE4,	IDT_NT_BARUTBASE4पूर्ण,
	  अणुIDT_NT_BARSETUP5,	IDT_NT_BARLIMIT5,
	   IDT_NT_BARLTBASE5,	IDT_NT_BARUTBASE5पूर्ण पूर्ण,
	अणु अणुIDT_NT_INMSG0,	IDT_NT_OUTMSG0,	IDT_NT_INMSGSRC0पूर्ण,
	  अणुIDT_NT_INMSG1,	IDT_NT_OUTMSG1,	IDT_NT_INMSGSRC1पूर्ण,
	  अणुIDT_NT_INMSG2,	IDT_NT_OUTMSG2,	IDT_NT_INMSGSRC2पूर्ण,
	  अणुIDT_NT_INMSG3,	IDT_NT_OUTMSG3,	IDT_NT_INMSGSRC3पूर्ण पूर्ण
पूर्ण;

/*
 * NT Endpoपूर्णांक ports data table with the corresponding pcie command, link
 * status, control and BAR-related रेजिस्टरs
 */
अटल स्थिर काष्ठा idt_ntb_port portdata_tbl[IDT_MAX_NR_PORTS] = अणु
/*0*/	अणु IDT_SW_NTP0_PCIECMDSTS,	IDT_SW_NTP0_PCIELCTLSTS,
	  IDT_SW_NTP0_NTCTL,
	  IDT_SW_SWPORT0CTL,		IDT_SW_SWPORT0STS,
	  अणु अणुIDT_SW_NTP0_BARSETUP0,	IDT_SW_NTP0_BARLIMIT0,
	     IDT_SW_NTP0_BARLTBASE0,	IDT_SW_NTP0_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP0_BARSETUP1,	IDT_SW_NTP0_BARLIMIT1,
	     IDT_SW_NTP0_BARLTBASE1,	IDT_SW_NTP0_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP0_BARSETUP2,	IDT_SW_NTP0_BARLIMIT2,
	     IDT_SW_NTP0_BARLTBASE2,	IDT_SW_NTP0_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP0_BARSETUP3,	IDT_SW_NTP0_BARLIMIT3,
	     IDT_SW_NTP0_BARLTBASE3,	IDT_SW_NTP0_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP0_BARSETUP4,	IDT_SW_NTP0_BARLIMIT4,
	     IDT_SW_NTP0_BARLTBASE4,	IDT_SW_NTP0_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP0_BARSETUP5,	IDT_SW_NTP0_BARLIMIT5,
	     IDT_SW_NTP0_BARLTBASE5,	IDT_SW_NTP0_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*1*/	अणु0पूर्ण,
/*2*/	अणु IDT_SW_NTP2_PCIECMDSTS,	IDT_SW_NTP2_PCIELCTLSTS,
	  IDT_SW_NTP2_NTCTL,
	  IDT_SW_SWPORT2CTL,		IDT_SW_SWPORT2STS,
	  अणु अणुIDT_SW_NTP2_BARSETUP0,	IDT_SW_NTP2_BARLIMIT0,
	     IDT_SW_NTP2_BARLTBASE0,	IDT_SW_NTP2_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP2_BARSETUP1,	IDT_SW_NTP2_BARLIMIT1,
	     IDT_SW_NTP2_BARLTBASE1,	IDT_SW_NTP2_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP2_BARSETUP2,	IDT_SW_NTP2_BARLIMIT2,
	     IDT_SW_NTP2_BARLTBASE2,	IDT_SW_NTP2_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP2_BARSETUP3,	IDT_SW_NTP2_BARLIMIT3,
	     IDT_SW_NTP2_BARLTBASE3,	IDT_SW_NTP2_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP2_BARSETUP4,	IDT_SW_NTP2_BARLIMIT4,
	     IDT_SW_NTP2_BARLTBASE4,	IDT_SW_NTP2_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP2_BARSETUP5,	IDT_SW_NTP2_BARLIMIT5,
	     IDT_SW_NTP2_BARLTBASE5,	IDT_SW_NTP2_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*3*/	अणु0पूर्ण,
/*4*/	अणु IDT_SW_NTP4_PCIECMDSTS,	IDT_SW_NTP4_PCIELCTLSTS,
	  IDT_SW_NTP4_NTCTL,
	  IDT_SW_SWPORT4CTL,		IDT_SW_SWPORT4STS,
	  अणु अणुIDT_SW_NTP4_BARSETUP0,	IDT_SW_NTP4_BARLIMIT0,
	     IDT_SW_NTP4_BARLTBASE0,	IDT_SW_NTP4_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP4_BARSETUP1,	IDT_SW_NTP4_BARLIMIT1,
	     IDT_SW_NTP4_BARLTBASE1,	IDT_SW_NTP4_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP4_BARSETUP2,	IDT_SW_NTP4_BARLIMIT2,
	     IDT_SW_NTP4_BARLTBASE2,	IDT_SW_NTP4_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP4_BARSETUP3,	IDT_SW_NTP4_BARLIMIT3,
	     IDT_SW_NTP4_BARLTBASE3,	IDT_SW_NTP4_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP4_BARSETUP4,	IDT_SW_NTP4_BARLIMIT4,
	     IDT_SW_NTP4_BARLTBASE4,	IDT_SW_NTP4_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP4_BARSETUP5,	IDT_SW_NTP4_BARLIMIT5,
	     IDT_SW_NTP4_BARLTBASE5,	IDT_SW_NTP4_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*5*/	अणु0पूर्ण,
/*6*/	अणु IDT_SW_NTP6_PCIECMDSTS,	IDT_SW_NTP6_PCIELCTLSTS,
	  IDT_SW_NTP6_NTCTL,
	  IDT_SW_SWPORT6CTL,		IDT_SW_SWPORT6STS,
	  अणु अणुIDT_SW_NTP6_BARSETUP0,	IDT_SW_NTP6_BARLIMIT0,
	     IDT_SW_NTP6_BARLTBASE0,	IDT_SW_NTP6_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP6_BARSETUP1,	IDT_SW_NTP6_BARLIMIT1,
	     IDT_SW_NTP6_BARLTBASE1,	IDT_SW_NTP6_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP6_BARSETUP2,	IDT_SW_NTP6_BARLIMIT2,
	     IDT_SW_NTP6_BARLTBASE2,	IDT_SW_NTP6_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP6_BARSETUP3,	IDT_SW_NTP6_BARLIMIT3,
	     IDT_SW_NTP6_BARLTBASE3,	IDT_SW_NTP6_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP6_BARSETUP4,	IDT_SW_NTP6_BARLIMIT4,
	     IDT_SW_NTP6_BARLTBASE4,	IDT_SW_NTP6_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP6_BARSETUP5,	IDT_SW_NTP6_BARLIMIT5,
	     IDT_SW_NTP6_BARLTBASE5,	IDT_SW_NTP6_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*7*/	अणु0पूर्ण,
/*8*/	अणु IDT_SW_NTP8_PCIECMDSTS,	IDT_SW_NTP8_PCIELCTLSTS,
	  IDT_SW_NTP8_NTCTL,
	  IDT_SW_SWPORT8CTL,		IDT_SW_SWPORT8STS,
	  अणु अणुIDT_SW_NTP8_BARSETUP0,	IDT_SW_NTP8_BARLIMIT0,
	     IDT_SW_NTP8_BARLTBASE0,	IDT_SW_NTP8_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP8_BARSETUP1,	IDT_SW_NTP8_BARLIMIT1,
	     IDT_SW_NTP8_BARLTBASE1,	IDT_SW_NTP8_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP8_BARSETUP2,	IDT_SW_NTP8_BARLIMIT2,
	     IDT_SW_NTP8_BARLTBASE2,	IDT_SW_NTP8_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP8_BARSETUP3,	IDT_SW_NTP8_BARLIMIT3,
	     IDT_SW_NTP8_BARLTBASE3,	IDT_SW_NTP8_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP8_BARSETUP4,	IDT_SW_NTP8_BARLIMIT4,
	     IDT_SW_NTP8_BARLTBASE4,	IDT_SW_NTP8_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP8_BARSETUP5,	IDT_SW_NTP8_BARLIMIT5,
	     IDT_SW_NTP8_BARLTBASE5,	IDT_SW_NTP8_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*9*/	अणु0पूर्ण,
/*10*/	अणु0पूर्ण,
/*11*/	अणु0पूर्ण,
/*12*/	अणु IDT_SW_NTP12_PCIECMDSTS,	IDT_SW_NTP12_PCIELCTLSTS,
	  IDT_SW_NTP12_NTCTL,
	  IDT_SW_SWPORT12CTL,		IDT_SW_SWPORT12STS,
	  अणु अणुIDT_SW_NTP12_BARSETUP0,	IDT_SW_NTP12_BARLIMIT0,
	     IDT_SW_NTP12_BARLTBASE0,	IDT_SW_NTP12_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP12_BARSETUP1,	IDT_SW_NTP12_BARLIMIT1,
	     IDT_SW_NTP12_BARLTBASE1,	IDT_SW_NTP12_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP12_BARSETUP2,	IDT_SW_NTP12_BARLIMIT2,
	     IDT_SW_NTP12_BARLTBASE2,	IDT_SW_NTP12_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP12_BARSETUP3,	IDT_SW_NTP12_BARLIMIT3,
	     IDT_SW_NTP12_BARLTBASE3,	IDT_SW_NTP12_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP12_BARSETUP4,	IDT_SW_NTP12_BARLIMIT4,
	     IDT_SW_NTP12_BARLTBASE4,	IDT_SW_NTP12_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP12_BARSETUP5,	IDT_SW_NTP12_BARLIMIT5,
	     IDT_SW_NTP12_BARLTBASE5,	IDT_SW_NTP12_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*13*/	अणु0पूर्ण,
/*14*/	अणु0पूर्ण,
/*15*/	अणु0पूर्ण,
/*16*/	अणु IDT_SW_NTP16_PCIECMDSTS,	IDT_SW_NTP16_PCIELCTLSTS,
	  IDT_SW_NTP16_NTCTL,
	  IDT_SW_SWPORT16CTL,		IDT_SW_SWPORT16STS,
	  अणु अणुIDT_SW_NTP16_BARSETUP0,	IDT_SW_NTP16_BARLIMIT0,
	     IDT_SW_NTP16_BARLTBASE0,	IDT_SW_NTP16_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP16_BARSETUP1,	IDT_SW_NTP16_BARLIMIT1,
	     IDT_SW_NTP16_BARLTBASE1,	IDT_SW_NTP16_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP16_BARSETUP2,	IDT_SW_NTP16_BARLIMIT2,
	     IDT_SW_NTP16_BARLTBASE2,	IDT_SW_NTP16_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP16_BARSETUP3,	IDT_SW_NTP16_BARLIMIT3,
	     IDT_SW_NTP16_BARLTBASE3,	IDT_SW_NTP16_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP16_BARSETUP4,	IDT_SW_NTP16_BARLIMIT4,
	     IDT_SW_NTP16_BARLTBASE4,	IDT_SW_NTP16_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP16_BARSETUP5,	IDT_SW_NTP16_BARLIMIT5,
	     IDT_SW_NTP16_BARLTBASE5,	IDT_SW_NTP16_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*17*/	अणु0पूर्ण,
/*18*/	अणु0पूर्ण,
/*19*/	अणु0पूर्ण,
/*20*/	अणु IDT_SW_NTP20_PCIECMDSTS,	IDT_SW_NTP20_PCIELCTLSTS,
	  IDT_SW_NTP20_NTCTL,
	  IDT_SW_SWPORT20CTL,		IDT_SW_SWPORT20STS,
	  अणु अणुIDT_SW_NTP20_BARSETUP0,	IDT_SW_NTP20_BARLIMIT0,
	     IDT_SW_NTP20_BARLTBASE0,	IDT_SW_NTP20_BARUTBASE0पूर्ण,
	    अणुIDT_SW_NTP20_BARSETUP1,	IDT_SW_NTP20_BARLIMIT1,
	     IDT_SW_NTP20_BARLTBASE1,	IDT_SW_NTP20_BARUTBASE1पूर्ण,
	    अणुIDT_SW_NTP20_BARSETUP2,	IDT_SW_NTP20_BARLIMIT2,
	     IDT_SW_NTP20_BARLTBASE2,	IDT_SW_NTP20_BARUTBASE2पूर्ण,
	    अणुIDT_SW_NTP20_BARSETUP3,	IDT_SW_NTP20_BARLIMIT3,
	     IDT_SW_NTP20_BARLTBASE3,	IDT_SW_NTP20_BARUTBASE3पूर्ण,
	    अणुIDT_SW_NTP20_BARSETUP4,	IDT_SW_NTP20_BARLIMIT4,
	     IDT_SW_NTP20_BARLTBASE4,	IDT_SW_NTP20_BARUTBASE4पूर्ण,
	    अणुIDT_SW_NTP20_BARSETUP5,	IDT_SW_NTP20_BARLIMIT5,
	     IDT_SW_NTP20_BARLTBASE5,	IDT_SW_NTP20_BARUTBASE5पूर्ण पूर्ण पूर्ण,
/*21*/	अणु0पूर्ण,
/*22*/	अणु0पूर्ण,
/*23*/	अणु0पूर्ण
पूर्ण;

/*
 * IDT PCIe-चयन partitions table with the corresponding control, status
 * and messages control रेजिस्टरs
 */
अटल स्थिर काष्ठा idt_ntb_part partdata_tbl[IDT_MAX_NR_PARTS] = अणु
/*0*/	अणु IDT_SW_SWPART0CTL,	IDT_SW_SWPART0STS,
	  अणुIDT_SW_SWP0MSGCTL0,	IDT_SW_SWP0MSGCTL1,
	   IDT_SW_SWP0MSGCTL2,	IDT_SW_SWP0MSGCTL3पूर्ण पूर्ण,
/*1*/	अणु IDT_SW_SWPART1CTL,	IDT_SW_SWPART1STS,
	  अणुIDT_SW_SWP1MSGCTL0,	IDT_SW_SWP1MSGCTL1,
	   IDT_SW_SWP1MSGCTL2,	IDT_SW_SWP1MSGCTL3पूर्ण पूर्ण,
/*2*/	अणु IDT_SW_SWPART2CTL,	IDT_SW_SWPART2STS,
	  अणुIDT_SW_SWP2MSGCTL0,	IDT_SW_SWP2MSGCTL1,
	   IDT_SW_SWP2MSGCTL2,	IDT_SW_SWP2MSGCTL3पूर्ण पूर्ण,
/*3*/	अणु IDT_SW_SWPART3CTL,	IDT_SW_SWPART3STS,
	  अणुIDT_SW_SWP3MSGCTL0,	IDT_SW_SWP3MSGCTL1,
	   IDT_SW_SWP3MSGCTL2,	IDT_SW_SWP3MSGCTL3पूर्ण पूर्ण,
/*4*/	अणु IDT_SW_SWPART4CTL,	IDT_SW_SWPART4STS,
	  अणुIDT_SW_SWP4MSGCTL0,	IDT_SW_SWP4MSGCTL1,
	   IDT_SW_SWP4MSGCTL2,	IDT_SW_SWP4MSGCTL3पूर्ण पूर्ण,
/*5*/	अणु IDT_SW_SWPART5CTL,	IDT_SW_SWPART5STS,
	  अणुIDT_SW_SWP5MSGCTL0,	IDT_SW_SWP5MSGCTL1,
	   IDT_SW_SWP5MSGCTL2,	IDT_SW_SWP5MSGCTL3पूर्ण पूर्ण,
/*6*/	अणु IDT_SW_SWPART6CTL,	IDT_SW_SWPART6STS,
	  अणुIDT_SW_SWP6MSGCTL0,	IDT_SW_SWP6MSGCTL1,
	   IDT_SW_SWP6MSGCTL2,	IDT_SW_SWP6MSGCTL3पूर्ण पूर्ण,
/*7*/	अणु IDT_SW_SWPART7CTL,	IDT_SW_SWPART7STS,
	  अणुIDT_SW_SWP7MSGCTL0,	IDT_SW_SWP7MSGCTL1,
	   IDT_SW_SWP7MSGCTL2,	IDT_SW_SWP7MSGCTL3पूर्ण पूर्ण
पूर्ण;

/*
 * DebugFS directory to place the driver debug file
 */
अटल काष्ठा dentry *dbgfs_topdir;

/*=============================================================================
 *                1. IDT PCIe-चयन रेजिस्टरs IO-functions
 *
 *    Beside ordinary configuration space रेजिस्टरs IDT PCIe-चयन expose
 * global configuration रेजिस्टरs, which are used to determine state of other
 * device ports as well as being notअगरied of some चयन-related events.
 * Additionally all the configuration space रेजिस्टरs of all the IDT
 * PCIe-चयन functions are mapped to the Global Address space, so each
 * function can determine a configuration of any other PCI-function.
 *    Functions declared in this chapter are created to encapsulate access
 * to configuration and global रेजिस्टरs, so the driver code just need to
 * provide IDT NTB hardware descriptor and a रेजिस्टर address.
 *=============================================================================
 */

/*
 * idt_nt_ग_लिखो() - PCI configuration space रेजिस्टरs ग_लिखो method
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to ग_लिखो data to
 * @data:	Value to ग_लिखो to the रेजिस्टर
 *
 * IDT PCIe-चयन रेजिस्टरs are all Little endian.
 */
अटल व्योम idt_nt_ग_लिखो(काष्ठा idt_ntb_dev *ndev,
			 स्थिर अचिन्हित पूर्णांक reg, स्थिर u32 data)
अणु
	/*
	 * It's obvious bug to request a रेजिस्टर exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	अगर (WARN_ON(reg > IDT_REG_PCI_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		वापस;

	/* Just ग_लिखो the value to the specअगरied रेजिस्टर */
	ioग_लिखो32(data, ndev->cfgspc + (सूचक_भेद_प्रकार)reg);
पूर्ण

/*
 * idt_nt_पढ़ो() - PCI configuration space रेजिस्टरs पढ़ो method
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to ग_लिखो data to
 *
 * IDT PCIe-चयन Global configuration रेजिस्टरs are all Little endian.
 *
 * Return: रेजिस्टर value
 */
अटल u32 idt_nt_पढ़ो(काष्ठा idt_ntb_dev *ndev, स्थिर अचिन्हित पूर्णांक reg)
अणु
	/*
	 * It's obvious bug to request a रेजिस्टर exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	अगर (WARN_ON(reg > IDT_REG_PCI_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		वापस ~0;

	/* Just पढ़ो the value from the specअगरied रेजिस्टर */
	वापस ioपढ़ो32(ndev->cfgspc + (सूचक_भेद_प्रकार)reg);
पूर्ण

/*
 * idt_sw_ग_लिखो() - Global रेजिस्टरs ग_लिखो method
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to ग_लिखो data to
 * @data:	Value to ग_लिखो to the रेजिस्टर
 *
 * IDT PCIe-चयन Global configuration रेजिस्टरs are all Little endian.
 */
अटल व्योम idt_sw_ग_लिखो(काष्ठा idt_ntb_dev *ndev,
			 स्थिर अचिन्हित पूर्णांक reg, स्थिर u32 data)
अणु
	अचिन्हित दीर्घ irqflags;

	/*
	 * It's obvious bug to request a रेजिस्टर exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	अगर (WARN_ON(reg > IDT_REG_SW_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		वापस;

	/* Lock GASA रेजिस्टरs operations */
	spin_lock_irqsave(&ndev->gasa_lock, irqflags);
	/* Set the global रेजिस्टर address */
	ioग_लिखो32((u32)reg, ndev->cfgspc + (सूचक_भेद_प्रकार)IDT_NT_GASAADDR);
	/* Put the new value of the रेजिस्टर */
	ioग_लिखो32(data, ndev->cfgspc + (सूचक_भेद_प्रकार)IDT_NT_GASADATA);
	/* Unlock GASA रेजिस्टरs operations */
	spin_unlock_irqrestore(&ndev->gasa_lock, irqflags);
पूर्ण

/*
 * idt_sw_पढ़ो() - Global रेजिस्टरs पढ़ो method
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to ग_लिखो data to
 *
 * IDT PCIe-चयन Global configuration रेजिस्टरs are all Little endian.
 *
 * Return: रेजिस्टर value
 */
अटल u32 idt_sw_पढ़ो(काष्ठा idt_ntb_dev *ndev, स्थिर अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 data;

	/*
	 * It's obvious bug to request a रेजिस्टर exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	अगर (WARN_ON(reg > IDT_REG_SW_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		वापस ~0;

	/* Lock GASA रेजिस्टरs operations */
	spin_lock_irqsave(&ndev->gasa_lock, irqflags);
	/* Set the global रेजिस्टर address */
	ioग_लिखो32((u32)reg, ndev->cfgspc + (सूचक_भेद_प्रकार)IDT_NT_GASAADDR);
	/* Get the data of the रेजिस्टर (पढ़ो ops acts as MMIO barrier) */
	data = ioपढ़ो32(ndev->cfgspc + (सूचक_भेद_प्रकार)IDT_NT_GASADATA);
	/* Unlock GASA रेजिस्टरs operations */
	spin_unlock_irqrestore(&ndev->gasa_lock, irqflags);

	वापस data;
पूर्ण

/*
 * idt_reg_set_bits() - set bits of a passed रेजिस्टर
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to change bits of
 * @reg_lock:	Register access spin lock
 * @valid_mask:	Mask of valid bits
 * @set_bits:	Biपंचांगask to set
 *
 * Helper method to check whether a passed bitfield is valid and set
 * corresponding bits of a रेजिस्टर.
 *
 * WARNING! Make sure the passed रेजिस्टर isn't accessed over plane
 * idt_nt_ग_लिखो() method (पढ़ो method is ok to be used concurrently).
 *
 * Return: zero on success, negative error on invalid biपंचांगask.
 */
अटल अंतरभूत पूर्णांक idt_reg_set_bits(काष्ठा idt_ntb_dev *ndev, अचिन्हित पूर्णांक reg,
				   spinlock_t *reg_lock,
				   u64 valid_mask, u64 set_bits)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 data;

	अगर (set_bits & ~(u64)valid_mask)
		वापस -EINVAL;

	/* Lock access to the रेजिस्टर unless the change is written back */
	spin_lock_irqsave(reg_lock, irqflags);
	data = idt_nt_पढ़ो(ndev, reg) | (u32)set_bits;
	idt_nt_ग_लिखो(ndev, reg, data);
	/* Unlock the रेजिस्टर */
	spin_unlock_irqrestore(reg_lock, irqflags);

	वापस 0;
पूर्ण

/*
 * idt_reg_clear_bits() - clear bits of a passed रेजिस्टर
 * @ndev:	IDT NTB hardware driver descriptor
 * @reg:	Register to change bits of
 * @reg_lock:	Register access spin lock
 * @set_bits:	Biपंचांगask to clear
 *
 * Helper method to check whether a passed bitfield is valid and clear
 * corresponding bits of a रेजिस्टर.
 *
 * NOTE! Invalid bits are always considered cleared so it's not an error
 * to clear them over.
 *
 * WARNING! Make sure the passed रेजिस्टर isn't accessed over plane
 * idt_nt_ग_लिखो() method (पढ़ो method is ok to use concurrently).
 */
अटल अंतरभूत व्योम idt_reg_clear_bits(काष्ठा idt_ntb_dev *ndev,
				     अचिन्हित पूर्णांक reg, spinlock_t *reg_lock,
				     u64 clear_bits)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 data;

	/* Lock access to the रेजिस्टर unless the change is written back */
	spin_lock_irqsave(reg_lock, irqflags);
	data = idt_nt_पढ़ो(ndev, reg) & ~(u32)clear_bits;
	idt_nt_ग_लिखो(ndev, reg, data);
	/* Unlock the रेजिस्टर */
	spin_unlock_irqrestore(reg_lock, irqflags);
पूर्ण

/*===========================================================================
 *                           2. Ports operations
 *
 *    IDT PCIe-चयनes can have from 3 up to 8 ports with possible
 * NT-functions enabled. So all the possible ports need to be scanned looking
 * क्रम NTB activated. NTB API will have क्रमागतerated only the ports with NTB.
 *===========================================================================
 */

/*
 * idt_scan_ports() - scan IDT PCIe-चयन ports collecting info in the tables
 * @ndev:	Poपूर्णांकer to the PCI device descriptor
 *
 * Return: zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_scan_ports(काष्ठा idt_ntb_dev *ndev)
अणु
	अचिन्हित अक्षर pidx, port, part;
	u32 data, portsts, partsts;

	/* Retrieve the local port number */
	data = idt_nt_पढ़ो(ndev, IDT_NT_PCIELCAP);
	ndev->port = GET_FIELD(PCIELCAP_PORTNUM, data);

	/* Retrieve the local partition number */
	portsts = idt_sw_पढ़ो(ndev, portdata_tbl[ndev->port].sts);
	ndev->part = GET_FIELD(SWPORTxSTS_SWPART, portsts);

	/* Initialize port/partition -> index tables with invalid values */
	स_रखो(ndev->port_idx_map, -EINVAL, माप(ndev->port_idx_map));
	स_रखो(ndev->part_idx_map, -EINVAL, माप(ndev->part_idx_map));

	/*
	 * Walk over all the possible ports checking whether any of them has
	 * NT-function activated
	 */
	ndev->peer_cnt = 0;
	क्रम (pidx = 0; pidx < ndev->swcfg->port_cnt; pidx++) अणु
		port = ndev->swcfg->ports[pidx];
		/* Skip local port */
		अगर (port == ndev->port)
			जारी;

		/* Read the port status रेजिस्टर to get it partition */
		portsts = idt_sw_पढ़ो(ndev, portdata_tbl[port].sts);
		part = GET_FIELD(SWPORTxSTS_SWPART, portsts);

		/* Retrieve the partition status */
		partsts = idt_sw_पढ़ो(ndev, partdata_tbl[part].sts);
		/* Check अगर partition state is active and port has NTB */
		अगर (IS_FLD_SET(SWPARTxSTS_STATE, partsts, ACT) &&
		    (IS_FLD_SET(SWPORTxSTS_MODE, portsts, NT) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, USNT) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, USNTDMA) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, NTDMA))) अणु
			/* Save the port and partition numbers */
			ndev->peers[ndev->peer_cnt].port = port;
			ndev->peers[ndev->peer_cnt].part = part;
			/* Fill in the port/partition -> index tables */
			ndev->port_idx_map[port] = ndev->peer_cnt;
			ndev->part_idx_map[part] = ndev->peer_cnt;
			ndev->peer_cnt++;
		पूर्ण
	पूर्ण

	dev_dbg(&ndev->ntb.pdev->dev, "Local port: %hhu, num of peers: %hhu\n",
		ndev->port, ndev->peer_cnt);

	/* It's useless to have this driver loaded अगर there is no any peer */
	अगर (ndev->peer_cnt == 0) अणु
		dev_warn(&ndev->ntb.pdev->dev, "No active peer found\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_ntb_port_number() - get the local port number
 * @ntb:	NTB device context.
 *
 * Return: the local port number
 */
अटल पूर्णांक idt_ntb_port_number(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस ndev->port;
पूर्ण

/*
 * idt_ntb_peer_port_count() - get the number of peer ports
 * @ntb:	NTB device context.
 *
 * Return the count of detected peer NT-functions.
 *
 * Return: number of peer ports
 */
अटल पूर्णांक idt_ntb_peer_port_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस ndev->peer_cnt;
पूर्ण

/*
 * idt_ntb_peer_port_number() - get peer port by given index
 * @ntb:	NTB device context.
 * @pidx:	Peer port index.
 *
 * Return: peer port or negative error
 */
अटल पूर्णांक idt_ntb_peer_port_number(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	/* Return the detected NT-function port number */
	वापस ndev->peers[pidx].port;
पूर्ण

/*
 * idt_ntb_peer_port_idx() - get peer port index by given port number
 * @ntb:	NTB device context.
 * @port:	Peer port number.
 *
 * Internal port -> index table is pre-initialized with -EINVAL values,
 * so we just need to वापस it value
 *
 * Return: peer NT-function port index or negative error
 */
अटल पूर्णांक idt_ntb_peer_port_idx(काष्ठा ntb_dev *ntb, पूर्णांक port)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (port < 0 || IDT_MAX_NR_PORTS <= port)
		वापस -EINVAL;

	वापस ndev->port_idx_map[port];
पूर्ण

/*===========================================================================
 *                         3. Link status operations
 *    There is no any पढ़ोy-to-use method to have peer ports notअगरied अगर NTB
 * link is set up or got करोwn. Instead global संकेत can be used instead.
 * In हाल अगर any one of ports changes local NTB link state, it sends
 * global संकेत and clears corresponding global state bit. Then all the ports
 * receive a notअगरication of that, so to make client driver being aware of
 * possible NTB link change.
 *    Additionally each of active NT-functions is subscribed to PCIe-link
 * state changes of peer ports.
 *===========================================================================
 */

अटल व्योम idt_ntb_local_link_disable(काष्ठा idt_ntb_dev *ndev);

/*
 * idt_init_link() - Initialize NTB link state notअगरication subप्रणाली
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Function perक्रमms the basic initialization of some global रेजिस्टरs
 * needed to enable IRQ-based notअगरications of PCIe Link Up/Down and
 * Global Signal events.
 * NOTE Since it's not possible to determine when all the NTB peer drivers are
 * unloaded as well as have those रेजिस्टरs accessed concurrently, we must
 * preinitialize them with the same value and leave it uncleared on local
 * driver unload.
 */
अटल व्योम idt_init_link(काष्ठा idt_ntb_dev *ndev)
अणु
	u32 part_mask, port_mask, se_mask;
	अचिन्हित अक्षर pidx;

	/* Initialize spin locker of Mapping Table access रेजिस्टरs */
	spin_lock_init(&ndev->mtbl_lock);

	/* Walk over all detected peers collecting port and partition masks */
	port_mask = ~BIT(ndev->port);
	part_mask = ~BIT(ndev->part);
	क्रम (pidx = 0; pidx < ndev->peer_cnt; pidx++) अणु
		port_mask &= ~BIT(ndev->peers[pidx].port);
		part_mask &= ~BIT(ndev->peers[pidx].part);
	पूर्ण

	/* Clean the Link Up/Down and GLobal Signal status रेजिस्टरs */
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKUPSTS, (u32)-1);
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKDNSTS, (u32)-1);
	idt_sw_ग_लिखो(ndev, IDT_SW_SEGSIGSTS, (u32)-1);

	/* Unmask NT-activated partitions to receive Global Switch events */
	idt_sw_ग_लिखो(ndev, IDT_SW_SEPMSK, part_mask);

	/* Enable PCIe Link Up events of NT-activated ports */
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKUPMSK, port_mask);

	/* Enable PCIe Link Down events of NT-activated ports */
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKDNMSK, port_mask);

	/* Unmask NT-activated partitions to receive Global Signal events */
	idt_sw_ग_लिखो(ndev, IDT_SW_SEGSIGMSK, part_mask);

	/* Unmask Link Up/Down and Global Switch Events */
	se_mask = ~(IDT_SEMSK_LINKUP | IDT_SEMSK_LINKDN | IDT_SEMSK_GSIGNAL);
	idt_sw_ग_लिखो(ndev, IDT_SW_SEMSK, se_mask);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB link status events initialized");
पूर्ण

/*
 * idt_deinit_link() - deinitialize link subप्रणाली
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Just disable the link back.
 */
अटल व्योम idt_deinit_link(काष्ठा idt_ntb_dev *ndev)
अणु
	/* Disable the link */
	idt_ntb_local_link_disable(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB link status events deinitialized");
पूर्ण

/*
 * idt_se_isr() - चयन events ISR
 * @ndev:	IDT NTB hardware driver descriptor
 * @ntपूर्णांक_sts:	NT-function पूर्णांकerrupt status
 *
 * This driver करोesn't support IDT PCIe-चयन dynamic reconfigurations,
 * Failover capability, etc, so चयन events are utilized to notअगरy of
 * PCIe and NTB link events.
 * The method is called from PCIe ISR bottom-half routine.
 */
अटल व्योम idt_se_isr(काष्ठा idt_ntb_dev *ndev, u32 ntपूर्णांक_sts)
अणु
	u32 sests;

	/* Read Switch Events status */
	sests = idt_sw_पढ़ो(ndev, IDT_SW_SESTS);

	/* Clean the Link Up/Down and Global Signal status रेजिस्टरs */
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKUPSTS, (u32)-1);
	idt_sw_ग_लिखो(ndev, IDT_SW_SELINKDNSTS, (u32)-1);
	idt_sw_ग_लिखो(ndev, IDT_SW_SEGSIGSTS, (u32)-1);

	/* Clean the corresponding पूर्णांकerrupt bit */
	idt_nt_ग_लिखो(ndev, IDT_NT_NTINTSTS, IDT_NTINTSTS_SEVENT);

	dev_dbg(&ndev->ntb.pdev->dev, "SE IRQ detected %#08x (SESTS %#08x)",
			  ntपूर्णांक_sts, sests);

	/* Notअगरy the client driver of possible link state change */
	ntb_link_event(&ndev->ntb);
पूर्ण

/*
 * idt_ntb_local_link_enable() - enable the local NTB link.
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * In order to enable the NTB link we need:
 * - enable Completion TLPs translation
 * - initialize mapping table to enable the Request ID translation
 * - notअगरy peers of NTB link state change
 */
अटल व्योम idt_ntb_local_link_enable(काष्ठा idt_ntb_dev *ndev)
अणु
	u32 reqid, mtbldata = 0;
	अचिन्हित दीर्घ irqflags;

	/* Enable the ID protection and Completion TLPs translation */
	idt_nt_ग_लिखो(ndev, IDT_NT_NTCTL, IDT_NTCTL_CPEN);

	/* Retrieve the current Requester ID (Bus:Device:Function) */
	reqid = idt_nt_पढ़ो(ndev, IDT_NT_REQIDCAP);

	/*
	 * Set the corresponding NT Mapping table entry of port partition index
	 * with the data to perक्रमm the Request ID translation
	 */
	mtbldata = SET_FIELD(NTMTBLDATA_REQID, 0, reqid) |
		   SET_FIELD(NTMTBLDATA_PART, 0, ndev->part) |
		   IDT_NTMTBLDATA_VALID;
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLADDR, ndev->part);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLDATA, mtbldata);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	/* Notअगरy the peers by setting and clearing the global संकेत bit */
	idt_nt_ग_लिखो(ndev, IDT_NT_NTGSIGNAL, IDT_NTGSIGNAL_SET);
	idt_sw_ग_लिखो(ndev, IDT_SW_SEGSIGSTS, (u32)1 << ndev->part);
पूर्ण

/*
 * idt_ntb_local_link_disable() - disable the local NTB link.
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * In order to enable the NTB link we need:
 * - disable Completion TLPs translation
 * - clear corresponding mapping table entry
 * - notअगरy peers of NTB link state change
 */
अटल व्योम idt_ntb_local_link_disable(काष्ठा idt_ntb_dev *ndev)
अणु
	अचिन्हित दीर्घ irqflags;

	/* Disable Completion TLPs translation */
	idt_nt_ग_लिखो(ndev, IDT_NT_NTCTL, 0);

	/* Clear the corresponding NT Mapping table entry */
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLADDR, ndev->part);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLDATA, 0);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	/* Notअगरy the peers by setting and clearing the global संकेत bit */
	idt_nt_ग_लिखो(ndev, IDT_NT_NTGSIGNAL, IDT_NTGSIGNAL_SET);
	idt_sw_ग_लिखो(ndev, IDT_SW_SEGSIGSTS, (u32)1 << ndev->part);
पूर्ण

/*
 * idt_ntb_local_link_is_up() - test wethter local NTB link is up
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Local link is up under the following conditions:
 * - Bus mastering is enabled
 * - NTCTL has Completion TLPs translation enabled
 * - Mapping table permits Request TLPs translation
 * NOTE: We करोn't need to check PCIe link state since it's obviously
 * up जबतक we are able to communicate with IDT PCIe-चयन
 *
 * Return: true अगर link is up, otherwise false
 */
अटल bool idt_ntb_local_link_is_up(काष्ठा idt_ntb_dev *ndev)
अणु
	अचिन्हित दीर्घ irqflags;
	u32 data;

	/* Read the local Bus Master Enable status */
	data = idt_nt_पढ़ो(ndev, IDT_NT_PCICMDSTS);
	अगर (!(data & IDT_PCICMDSTS_BME))
		वापस false;

	/* Read the local Completion TLPs translation enable status */
	data = idt_nt_पढ़ो(ndev, IDT_NT_NTCTL);
	अगर (!(data & IDT_NTCTL_CPEN))
		वापस false;

	/* Read Mapping table entry corresponding to the local partition */
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLADDR, ndev->part);
	data = idt_nt_पढ़ो(ndev, IDT_NT_NTMTBLDATA);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	वापस !!(data & IDT_NTMTBLDATA_VALID);
पूर्ण

/*
 * idt_ntb_peer_link_is_up() - test whether peer NTB link is up
 * @ndev:	IDT NTB hardware driver descriptor
 * @pidx:	Peer port index
 *
 * Peer link is up under the following conditions:
 * - PCIe link is up
 * - Bus mastering is enabled
 * - NTCTL has Completion TLPs translation enabled
 * - Mapping table permits Request TLPs translation
 *
 * Return: true अगर link is up, otherwise false
 */
अटल bool idt_ntb_peer_link_is_up(काष्ठा idt_ntb_dev *ndev, पूर्णांक pidx)
अणु
	अचिन्हित दीर्घ irqflags;
	अचिन्हित अक्षर port;
	u32 data;

	/* Retrieve the device port number */
	port = ndev->peers[pidx].port;

	/* Check whether PCIe link is up */
	data = idt_sw_पढ़ो(ndev, portdata_tbl[port].sts);
	अगर (!(data & IDT_SWPORTxSTS_LINKUP))
		वापस false;

	/* Check whether bus mastering is enabled on the peer port */
	data = idt_sw_पढ़ो(ndev, portdata_tbl[port].pcicmdsts);
	अगर (!(data & IDT_PCICMDSTS_BME))
		वापस false;

	/* Check अगर Completion TLPs translation is enabled on the peer port */
	data = idt_sw_पढ़ो(ndev, portdata_tbl[port].ntctl);
	अगर (!(data & IDT_NTCTL_CPEN))
		वापस false;

	/* Read Mapping table entry corresponding to the peer partition */
	spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
	idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLADDR, ndev->peers[pidx].part);
	data = idt_nt_पढ़ो(ndev, IDT_NT_NTMTBLDATA);
	spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

	वापस !!(data & IDT_NTMTBLDATA_VALID);
पूर्ण

/*
 * idt_ntb_link_is_up() - get the current ntb link state (NTB API callback)
 * @ntb:	NTB device context.
 * @speed:	OUT - The link speed expressed as PCIe generation number.
 * @width:	OUT - The link width expressed as the number of PCIe lanes.
 *
 * Get the bitfield of NTB link states क्रम all peer ports
 *
 * Return: bitfield of indexed ports link state: bit is set/cleared अगर the
 *         link is up/करोwn respectively.
 */
अटल u64 idt_ntb_link_is_up(काष्ठा ntb_dev *ntb,
			      क्रमागत ntb_speed *speed, क्रमागत ntb_width *width)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	अचिन्हित अक्षर pidx;
	u64 status;
	u32 data;

	/* Retrieve the local link speed and width */
	अगर (speed != शून्य || width != शून्य) अणु
		data = idt_nt_पढ़ो(ndev, IDT_NT_PCIELCTLSTS);
		अगर (speed != शून्य)
			*speed = GET_FIELD(PCIELCTLSTS_CLS, data);
		अगर (width != शून्य)
			*width = GET_FIELD(PCIELCTLSTS_NLW, data);
	पूर्ण

	/* If local NTB link isn't up then all the links are considered करोwn */
	अगर (!idt_ntb_local_link_is_up(ndev))
		वापस 0;

	/* Collect all the peer ports link states पूर्णांकo the bitfield */
	status = 0;
	क्रम (pidx = 0; pidx < ndev->peer_cnt; pidx++) अणु
		अगर (idt_ntb_peer_link_is_up(ndev, pidx))
			status |= ((u64)1 << pidx);
	पूर्ण

	वापस status;
पूर्ण

/*
 * idt_ntb_link_enable() - enable local port ntb link (NTB API callback)
 * @ntb:	NTB device context.
 * @max_speed:	The maximum link speed expressed as PCIe generation number.
 * @max_width:	The maximum link width expressed as the number of PCIe lanes.
 *
 * Enable just local NTB link. PCIe link parameters are ignored.
 *
 * Return: always zero.
 */
अटल पूर्णांक idt_ntb_link_enable(काष्ठा ntb_dev *ntb, क्रमागत ntb_speed speed,
			       क्रमागत ntb_width width)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	/* Just enable the local NTB link */
	idt_ntb_local_link_enable(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "Local NTB link enabled");

	वापस 0;
पूर्ण

/*
 * idt_ntb_link_disable() - disable local port ntb link (NTB API callback)
 * @ntb:	NTB device context.
 *
 * Disable just local NTB link.
 *
 * Return: always zero.
 */
अटल पूर्णांक idt_ntb_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	/* Just disable the local NTB link */
	idt_ntb_local_link_disable(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "Local NTB link disabled");

	वापस 0;
पूर्ण

/*=============================================================================
 *                         4. Memory Winकरोw operations
 *
 *    IDT PCIe-चयनes have two types of memory winकरोws: MWs with direct
 * address translation and MWs with LUT based translation. The first type of
 * MWs is simple map of corresponding BAR address space to a memory space
 * of specअगरied target port. So it implemets just ont-to-one mapping. Lookup
 * table in its turn can map one BAR address space to up to 24 dअगरferent
 * memory spaces of dअगरferent ports.
 *    NT-functions BARs can be turned on to implement either direct or lookup
 * table based address translations, so:
 * BAR0 - NT configuration रेजिस्टरs space/direct address translation
 * BAR1 - direct address translation/upper address of BAR0x64
 * BAR2 - direct address translation/Lookup table with either 12 or 24 entries
 * BAR3 - direct address translation/upper address of BAR2x64
 * BAR4 - direct address translation/Lookup table with either 12 or 24 entries
 * BAR5 - direct address translation/upper address of BAR4x64
 *    Additionally BAR2 and BAR4 can't have 24-entries LUT enabled at the same
 * समय. Since the BARs setup can be rather complicated this driver implements
 * a scanning algorithm to have all the possible memory winकरोws configuration
 * covered.
 *
 * NOTE 1 BAR setup must be करोne beक्रमe Linux kernel क्रमागतerated NT-function
 * of any port, so this driver would have memory winकरोws configurations fixed.
 * In this way all initializations must be perक्रमmed either by platक्रमm BIOS
 * or using EEPROM connected to IDT PCIe-चयन master SMBus.
 *
 * NOTE 2 This driver expects BAR0 mapping NT-function configuration space.
 * Easy calculation can give us an upper boundary of 29 possible memory winकरोws
 * per each NT-function अगर all the BARs are of 32bit type.
 *=============================================================================
 */

/*
 * idt_get_mw_count() - get memory winकरोw count
 * @mw_type:	Memory winकरोw type
 *
 * Return: number of memory winकरोws with respect to the BAR type
 */
अटल अंतरभूत अचिन्हित अक्षर idt_get_mw_count(क्रमागत idt_mw_type mw_type)
अणु
	चयन (mw_type) अणु
	हाल IDT_MW_सूची:
		वापस 1;
	हाल IDT_MW_LUT12:
		वापस 12;
	हाल IDT_MW_LUT24:
		वापस 24;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_get_mw_name() - get memory winकरोw name
 * @mw_type:	Memory winकरोw type
 *
 * Return: poपूर्णांकer to a string with name
 */
अटल अंतरभूत अक्षर *idt_get_mw_name(क्रमागत idt_mw_type mw_type)
अणु
	चयन (mw_type) अणु
	हाल IDT_MW_सूची:
		वापस "DIR  ";
	हाल IDT_MW_LUT12:
		वापस "LUT12";
	हाल IDT_MW_LUT24:
		वापस "LUT24";
	शेष:
		अवरोध;
	पूर्ण

	वापस "unknown";
पूर्ण

/*
 * idt_scan_mws() - scan memory winकरोws of the port
 * @ndev:	IDT NTB hardware driver descriptor
 * @port:	Port to get number of memory winकरोws क्रम
 * @mw_cnt:	Out - number of memory winकरोws
 *
 * It walks over BAR setup रेजिस्टरs of the specअगरied port and determines
 * the memory winकरोws parameters अगर any activated.
 *
 * Return: array of memory winकरोws
 */
अटल काष्ठा idt_mw_cfg *idt_scan_mws(काष्ठा idt_ntb_dev *ndev, पूर्णांक port,
				       अचिन्हित अक्षर *mw_cnt)
अणु
	काष्ठा idt_mw_cfg mws[IDT_MAX_NR_MWS], *ret_mws;
	स्थिर काष्ठा idt_ntb_bar *bars;
	क्रमागत idt_mw_type mw_type;
	अचिन्हित अक्षर widx, bidx, en_cnt;
	bool bar_64bit = false;
	पूर्णांक aprt_size;
	u32 data;

	/* Retrieve the array of the BARs रेजिस्टरs */
	bars = portdata_tbl[port].bars;

	/* Scan all the BARs beदीर्घing to the port */
	*mw_cnt = 0;
	क्रम (bidx = 0; bidx < IDT_BAR_CNT; bidx += 1 + bar_64bit) अणु
		/* Read BARSETUP रेजिस्टर value */
		data = idt_sw_पढ़ो(ndev, bars[bidx].setup);

		/* Skip disabled BARs */
		अगर (!(data & IDT_BARSETUP_EN)) अणु
			bar_64bit = false;
			जारी;
		पूर्ण

		/* Skip next BARSETUP अगर current one has 64bit addressing */
		bar_64bit = IS_FLD_SET(BARSETUP_TYPE, data, 64);

		/* Skip configuration space mapping BARs */
		अगर (data & IDT_BARSETUP_MODE_CFG)
			जारी;

		/* Retrieve MW type/entries count and aperture size */
		mw_type = GET_FIELD(BARSETUP_ATRAN, data);
		en_cnt = idt_get_mw_count(mw_type);
		aprt_size = (u64)1 << GET_FIELD(BARSETUP_SIZE, data);

		/* Save configurations of all available memory winकरोws */
		क्रम (widx = 0; widx < en_cnt; widx++, (*mw_cnt)++) अणु
			/*
			 * IDT can expose a limited number of MWs, so it's bug
			 * to have more than the driver expects
			 */
			अगर (*mw_cnt >= IDT_MAX_NR_MWS)
				वापस ERR_PTR(-EINVAL);

			/* Save basic MW info */
			mws[*mw_cnt].type = mw_type;
			mws[*mw_cnt].bar = bidx;
			mws[*mw_cnt].idx = widx;
			/* It's always DWORD aligned */
			mws[*mw_cnt].addr_align = IDT_TRANS_ALIGN;
			/* सूची and LUT approachs dअगरferently configure MWs */
			अगर (mw_type == IDT_MW_सूची)
				mws[*mw_cnt].size_max = aprt_size;
			अन्यथा अगर (mw_type == IDT_MW_LUT12)
				mws[*mw_cnt].size_max = aprt_size / 16;
			अन्यथा
				mws[*mw_cnt].size_max = aprt_size / 32;
			mws[*mw_cnt].size_align = (mw_type == IDT_MW_सूची) ?
				IDT_सूची_SIZE_ALIGN : mws[*mw_cnt].size_max;
		पूर्ण
	पूर्ण

	/* Allocate memory क्रम memory winकरोw descriptors */
	ret_mws = devm_kसुस्मृति(&ndev->ntb.pdev->dev, *mw_cnt, माप(*ret_mws),
			       GFP_KERNEL);
	अगर (!ret_mws)
		वापस ERR_PTR(-ENOMEM);

	/* Copy the info of detected memory winकरोws */
	स_नकल(ret_mws, mws, (*mw_cnt)*माप(*ret_mws));

	वापस ret_mws;
पूर्ण

/*
 * idt_init_mws() - initialize memory winकरोws subप्रणाली
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Scan BAR setup रेजिस्टरs of local and peer ports to determine the
 * outbound and inbound memory winकरोws parameters
 *
 * Return: zero on success, otherwise a negative error number
 */
अटल पूर्णांक idt_init_mws(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा idt_ntb_peer *peer;
	अचिन्हित अक्षर pidx;

	/* Scan memory winकरोws of the local port */
	ndev->mws = idt_scan_mws(ndev, ndev->port, &ndev->mw_cnt);
	अगर (IS_ERR(ndev->mws)) अणु
		dev_err(&ndev->ntb.pdev->dev,
			"Failed to scan mws of local port %hhu", ndev->port);
		वापस PTR_ERR(ndev->mws);
	पूर्ण

	/* Scan memory winकरोws of the peer ports */
	क्रम (pidx = 0; pidx < ndev->peer_cnt; pidx++) अणु
		peer = &ndev->peers[pidx];
		peer->mws = idt_scan_mws(ndev, peer->port, &peer->mw_cnt);
		अगर (IS_ERR(peer->mws)) अणु
			dev_err(&ndev->ntb.pdev->dev,
				"Failed to scan mws of port %hhu", peer->port);
			वापस PTR_ERR(peer->mws);
		पूर्ण
	पूर्ण

	/* Initialize spin locker of the LUT रेजिस्टरs */
	spin_lock_init(&ndev->lut_lock);

	dev_dbg(&ndev->ntb.pdev->dev, "Outbound and inbound MWs initialized");

	वापस 0;
पूर्ण

/*
 * idt_ntb_mw_count() - number of inbound memory winकरोws (NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 *
 * The value is वापसed क्रम the specअगरied peer, so generally speaking it can
 * be dअगरferent क्रम dअगरferent port depending on the IDT PCIe-चयन
 * initialization.
 *
 * Return: the number of memory winकरोws.
 */
अटल पूर्णांक idt_ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	वापस ndev->peers[pidx].mw_cnt;
पूर्ण

/*
 * idt_ntb_mw_get_align() - inbound memory winकरोw parameters (NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 * @addr_align:	OUT - the base alignment क्रम translating the memory winकरोw
 * @size_align:	OUT - the size alignment क्रम translating the memory winकरोw
 * @size_max:	OUT - the maximum size of the memory winकरोw
 *
 * The peer memory winकरोw parameters have alपढ़ोy been determined, so just
 * वापस the corresponding values, which mustn't change within session.
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				resource_माप_प्रकार *addr_align,
				resource_माप_प्रकार *size_align,
				resource_माप_प्रकार *size_max)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	काष्ठा idt_ntb_peer *peer;

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	peer = &ndev->peers[pidx];

	अगर (widx < 0 || peer->mw_cnt <= widx)
		वापस -EINVAL;

	अगर (addr_align != शून्य)
		*addr_align = peer->mws[widx].addr_align;

	अगर (size_align != शून्य)
		*size_align = peer->mws[widx].size_align;

	अगर (size_max != शून्य)
		*size_max = peer->mws[widx].size_max;

	वापस 0;
पूर्ण

/*
 * idt_ntb_peer_mw_count() - number of outbound memory winकरोws
 *			     (NTB API callback)
 * @ntb:	NTB device context.
 *
 * Outbound memory winकरोws parameters have been determined based on the
 * BAR setup रेजिस्टरs value, which are mostly स्थिरants within one session.
 *
 * Return: the number of memory winकरोws.
 */
अटल पूर्णांक idt_ntb_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस ndev->mw_cnt;
पूर्ण

/*
 * idt_ntb_peer_mw_get_addr() - get map address of an outbound memory winकरोw
 *				(NTB API callback)
 * @ntb:	NTB device context.
 * @widx:	Memory winकरोw index (within ntb_peer_mw_count() वापस value).
 * @base:	OUT - the base address of mapping region.
 * @size:	OUT - the size of mapping region.
 *
 * Return just parameters of BAR resources mapping. Size reflects just the size
 * of the resource
 *
 * Return: Zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक widx,
				    phys_addr_t *base, resource_माप_प्रकार *size)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (widx < 0 || ndev->mw_cnt <= widx)
		वापस -EINVAL;

	/* Mapping address is just properly shअगरted BAR resource start */
	अगर (base != शून्य)
		*base = pci_resource_start(ntb->pdev, ndev->mws[widx].bar) +
			ndev->mws[widx].idx * ndev->mws[widx].size_max;

	/* Mapping size has alपढ़ोy been calculated at MWs scanning */
	अगर (size != शून्य)
		*size = ndev->mws[widx].size_max;

	वापस 0;
पूर्ण

/*
 * idt_ntb_peer_mw_set_trans() - set a translation address of a memory winकरोw
 *				 (NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device the translation address received from.
 * @widx:	Memory winकरोw index.
 * @addr:	The dma address of the shared memory to access.
 * @size:	The size of the shared memory to access.
 *
 * The Direct address translation and LUT base translation is initialized a
 * bit dअगरferenet. Although the parameters restriction are now determined by
 * the same code.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल पूर्णांक idt_ntb_peer_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				     u64 addr, resource_माप_प्रकार size)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	काष्ठा idt_mw_cfg *mw_cfg;
	u32 data = 0, lutoff = 0;

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	अगर (widx < 0 || ndev->mw_cnt <= widx)
		वापस -EINVAL;

	/*
	 * Retrieve the memory winकरोw config to make sure the passed arguments
	 * fit it restrictions
	 */
	mw_cfg = &ndev->mws[widx];
	अगर (!IS_ALIGNED(addr, mw_cfg->addr_align))
		वापस -EINVAL;
	अगर (!IS_ALIGNED(size, mw_cfg->size_align) || size > mw_cfg->size_max)
		वापस -EINVAL;

	/* सूची and LUT based translations are initialized dअगरferently */
	अगर (mw_cfg->type == IDT_MW_सूची) अणु
		स्थिर काष्ठा idt_ntb_bar *bar = &ntdata_tbl.bars[mw_cfg->bar];
		u64 limit;
		/* Set destination partition of translation */
		data = idt_nt_पढ़ो(ndev, bar->setup);
		data = SET_FIELD(BARSETUP_TPART, data, ndev->peers[pidx].part);
		idt_nt_ग_लिखो(ndev, bar->setup, data);
		/* Set translation base address */
		idt_nt_ग_लिखो(ndev, bar->ltbase, (u32)addr);
		idt_nt_ग_लिखो(ndev, bar->utbase, (u32)(addr >> 32));
		/* Set the custom BAR aperture limit */
		limit = pci_bus_address(ntb->pdev, mw_cfg->bar) + size;
		idt_nt_ग_लिखो(ndev, bar->limit, (u32)limit);
		अगर (IS_FLD_SET(BARSETUP_TYPE, data, 64))
			idt_nt_ग_लिखो(ndev, (bar + 1)->limit, (limit >> 32));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ irqflags;
		/* Initialize corresponding LUT entry */
		lutoff = SET_FIELD(LUTOFFSET_INDEX, 0, mw_cfg->idx) |
			 SET_FIELD(LUTOFFSET_BAR, 0, mw_cfg->bar);
		data = SET_FIELD(LUTUDATA_PART, 0, ndev->peers[pidx].part) |
			IDT_LUTUDATA_VALID;
		spin_lock_irqsave(&ndev->lut_lock, irqflags);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTOFFSET, lutoff);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTLDATA, (u32)addr);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTMDATA, (u32)(addr >> 32));
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTUDATA, data);
		spin_unlock_irqrestore(&ndev->lut_lock, irqflags);
		/* Limit address isn't specअगरied since size is fixed क्रम LUT */
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_ntb_peer_mw_clear_trans() - clear the outbound MW translation address
 *				   (NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device.
 * @widx:	Memory winकरोw index.
 *
 * It effectively disables the translation over the specअगरied outbound MW.
 *
 * Return: Zero on success, otherwise an error number.
 */
अटल पूर्णांक idt_ntb_peer_mw_clear_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
					पूर्णांक widx)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	काष्ठा idt_mw_cfg *mw_cfg;

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	अगर (widx < 0 || ndev->mw_cnt <= widx)
		वापस -EINVAL;

	mw_cfg = &ndev->mws[widx];

	/* सूची and LUT based translations are initialized dअगरferently */
	अगर (mw_cfg->type == IDT_MW_सूची) अणु
		स्थिर काष्ठा idt_ntb_bar *bar = &ntdata_tbl.bars[mw_cfg->bar];
		u32 data;
		/* Read BARSETUP to check BAR type */
		data = idt_nt_पढ़ो(ndev, bar->setup);
		/* Disable translation by specअगरying zero BAR limit */
		idt_nt_ग_लिखो(ndev, bar->limit, 0);
		अगर (IS_FLD_SET(BARSETUP_TYPE, data, 64))
			idt_nt_ग_लिखो(ndev, (bar + 1)->limit, 0);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ irqflags;
		u32 lutoff;
		/* Clear the corresponding LUT entry up */
		lutoff = SET_FIELD(LUTOFFSET_INDEX, 0, mw_cfg->idx) |
			 SET_FIELD(LUTOFFSET_BAR, 0, mw_cfg->bar);
		spin_lock_irqsave(&ndev->lut_lock, irqflags);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTOFFSET, lutoff);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTLDATA, 0);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTMDATA, 0);
		idt_nt_ग_लिखो(ndev, IDT_NT_LUTUDATA, 0);
		spin_unlock_irqrestore(&ndev->lut_lock, irqflags);
	पूर्ण

	वापस 0;
पूर्ण

/*=============================================================================
 *                          5. Doorbell operations
 *
 *    Doorbell functionality of IDT PCIe-चयनes is pretty unusual. First of
 * all there is global करोorbell रेजिस्टर which state can be changed by any
 * NT-function of the IDT device in accordance with global permissions. These
 * permissions configs are not supported by NTB API, so it must be करोne by
 * either BIOS or EEPROM settings. In the same way the state of the global
 * करोorbell is reflected to the NT-functions local inbound करोorbell रेजिस्टरs.
 * It can lead to situations when client driver sets some peer करोorbell bits
 * and get them bounced back to local inbound करोorbell अगर permissions are
 * granted.
 *    Secondly there is just one IRQ vector क्रम Doorbell, Message, Temperature
 * and Switch events, so अगर client driver left any of Doorbell bits set and
 * some other event occurred, the driver will be notअगरied of Doorbell event
 * again.
 *=============================================================================
 */

/*
 * idt_db_isr() - करोorbell event ISR
 * @ndev:	IDT NTB hardware driver descriptor
 * @ntपूर्णांक_sts:	NT-function पूर्णांकerrupt status
 *
 * Doorbell event happans when DBELL bit of NTINTSTS चयनes from 0 to 1.
 * It happens only when unmasked करोorbell bits are set to ones on completely
 * zeroed करोorbell रेजिस्टर.
 * The method is called from PCIe ISR bottom-half routine.
 */
अटल व्योम idt_db_isr(काष्ठा idt_ntb_dev *ndev, u32 ntपूर्णांक_sts)
अणु
	/*
	 * Doorbell IRQ status will be cleaned only when client
	 * driver unsets all the करोorbell bits.
	 */
	dev_dbg(&ndev->ntb.pdev->dev, "DB IRQ detected %#08x", ntपूर्णांक_sts);

	/* Notअगरy the client driver of possible करोorbell state change */
	ntb_db_event(&ndev->ntb, 0);
पूर्ण

/*
 * idt_ntb_db_valid_mask() - get a mask of करोorbell bits supported by the ntb
 *			     (NTB API callback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-चयनes expose just one Doorbell रेजिस्टर of DWORD size.
 *
 * Return: A mask of करोorbell bits supported by the ntb.
 */
अटल u64 idt_ntb_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	वापस IDT_DBELL_MASK;
पूर्ण

/*
 * idt_ntb_db_पढ़ो() - पढ़ो the local करोorbell रेजिस्टर (NTB API callback)
 * @ntb:	NTB device context.
 *
 * There is just on inbound करोorbell रेजिस्टर of each NT-function, so
 * this method वापस it value.
 *
 * Return: The bits currently set in the local करोorbell रेजिस्टर.
 */
अटल u64 idt_ntb_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस idt_nt_पढ़ो(ndev, IDT_NT_INDBELLSTS);
पूर्ण

/*
 * idt_ntb_db_clear() - clear bits in the local करोorbell रेजिस्टर
 *			(NTB API callback)
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * Clear bits of inbound करोorbell रेजिस्टर by writing ones to it.
 *
 * NOTE! Invalid bits are always considered cleared so it's not an error
 * to clear them over.
 *
 * Return: always zero as success.
 */
अटल पूर्णांक idt_ntb_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_nt_ग_लिखो(ndev, IDT_NT_INDBELLSTS, (u32)db_bits);

	वापस 0;
पूर्ण

/*
 * idt_ntb_db_पढ़ो_mask() - पढ़ो the local करोorbell mask (NTB API callback)
 * @ntb:	NTB device context.
 *
 * Each inbound करोorbell bit can be masked from generating IRQ by setting
 * the corresponding bit in inbound करोorbell mask. So this method वापसs
 * the value of the रेजिस्टर.
 *
 * Return: The bits currently set in the local करोorbell mask रेजिस्टर.
 */
अटल u64 idt_ntb_db_पढ़ो_mask(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस idt_nt_पढ़ो(ndev, IDT_NT_INDBELLMSK);
पूर्ण

/*
 * idt_ntb_db_set_mask() - set bits in the local करोorbell mask
 *			   (NTB API callback)
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell mask bits to set.
 *
 * The inbound करोorbell रेजिस्टर mask value must be पढ़ो, then OR'ed with
 * passed field and only then set back.
 *
 * Return: zero on success, negative error अगर invalid argument passed.
 */
अटल पूर्णांक idt_ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस idt_reg_set_bits(ndev, IDT_NT_INDBELLMSK, &ndev->db_mask_lock,
				IDT_DBELL_MASK, db_bits);
पूर्ण

/*
 * idt_ntb_db_clear_mask() - clear bits in the local करोorbell mask
 *			     (NTB API callback)
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to clear.
 *
 * The method just clears the set bits up in accordance with the passed
 * bitfield. IDT PCIe-चयन shall generate an पूर्णांकerrupt अगर there hasn't
 * been any unmasked bit set beक्रमe current unmasking. Otherwise IRQ won't
 * be generated since there is only one IRQ vector क्रम all करोorbells.
 *
 * Return: always zero as success
 */
अटल पूर्णांक idt_ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_reg_clear_bits(ndev, IDT_NT_INDBELLMSK, &ndev->db_mask_lock,
			   db_bits);

	वापस 0;
पूर्ण

/*
 * idt_ntb_peer_db_set() - set bits in the peer करोorbell रेजिस्टर
 *			   (NTB API callback)
 * @ntb:	NTB device context.
 * @db_bits:	Doorbell bits to set.
 *
 * IDT PCIe-चयनes exposes local outbound करोorbell रेजिस्टर to change peer
 * inbound करोorbell रेजिस्टर state.
 *
 * Return: zero on success, negative error अगर invalid argument passed.
 */
अटल पूर्णांक idt_ntb_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (db_bits & ~(u64)IDT_DBELL_MASK)
		वापस -EINVAL;

	idt_nt_ग_लिखो(ndev, IDT_NT_OUTDBELLSET, (u32)db_bits);
	वापस 0;
पूर्ण

/*=============================================================================
 *                          6. Messaging operations
 *
 *    Each NT-function of IDT PCIe-चयन has four inbound and four outbound
 * message रेजिस्टरs. Each outbound message रेजिस्टर can be connected to one or
 * even more than one peer inbound message रेजिस्टरs by setting global
 * configurations. Since NTB API permits one-on-one message रेजिस्टरs mapping
 * only, the driver acts in according with that restriction.
 *=============================================================================
 */

/*
 * idt_init_msg() - initialize messaging पूर्णांकerface
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Just initialize the message रेजिस्टरs routing tables locker.
 */
अटल व्योम idt_init_msg(काष्ठा idt_ntb_dev *ndev)
अणु
	अचिन्हित अक्षर midx;

	/* Init the messages routing table lockers */
	क्रम (midx = 0; midx < IDT_MSG_CNT; midx++)
		spin_lock_init(&ndev->msg_locks[midx]);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB Messaging initialized");
पूर्ण

/*
 * idt_msg_isr() - message event ISR
 * @ndev:	IDT NTB hardware driver descriptor
 * @ntपूर्णांक_sts:	NT-function पूर्णांकerrupt status
 *
 * Message event happens when MSG bit of NTINTSTS चयनes from 0 to 1.
 * It happens only when unmasked message status bits are set to ones on
 * completely zeroed message status रेजिस्टर.
 * The method is called from PCIe ISR bottom-half routine.
 */
अटल व्योम idt_msg_isr(काष्ठा idt_ntb_dev *ndev, u32 ntपूर्णांक_sts)
अणु
	/*
	 * Message IRQ status will be cleaned only when client
	 * driver unsets all the message status bits.
	 */
	dev_dbg(&ndev->ntb.pdev->dev, "Message IRQ detected %#08x", ntपूर्णांक_sts);

	/* Notअगरy the client driver of possible message status change */
	ntb_msg_event(&ndev->ntb);
पूर्ण

/*
 * idt_ntb_msg_count() - get the number of message रेजिस्टरs (NTB API callback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-चयनes support four message रेजिस्टरs.
 *
 * Return: the number of message रेजिस्टरs.
 */
अटल पूर्णांक idt_ntb_msg_count(काष्ठा ntb_dev *ntb)
अणु
	वापस IDT_MSG_CNT;
पूर्ण

/*
 * idt_ntb_msg_inbits() - get a bitfield of inbound message रेजिस्टरs status
 *			  (NTB API callback)
 * @ntb:	NTB device context.
 *
 * NT message status रेजिस्टर is shared between inbound and outbound message
 * रेजिस्टरs status
 *
 * Return: bitfield of inbound message रेजिस्टरs.
 */
अटल u64 idt_ntb_msg_inbits(काष्ठा ntb_dev *ntb)
अणु
	वापस (u64)IDT_INMSG_MASK;
पूर्ण

/*
 * idt_ntb_msg_outbits() - get a bitfield of outbound message रेजिस्टरs status
 *			  (NTB API callback)
 * @ntb:	NTB device context.
 *
 * NT message status रेजिस्टर is shared between inbound and outbound message
 * रेजिस्टरs status
 *
 * Return: bitfield of outbound message रेजिस्टरs.
 */
अटल u64 idt_ntb_msg_outbits(काष्ठा ntb_dev *ntb)
अणु
	वापस (u64)IDT_OUTMSG_MASK;
पूर्ण

/*
 * idt_ntb_msg_पढ़ो_sts() - पढ़ो the message रेजिस्टरs status (NTB API callback)
 * @ntb:	NTB device context.
 *
 * IDT PCIe-चयनes expose message status रेजिस्टरs to notअगरy drivers of
 * incoming data and failures in हाल अगर peer message रेजिस्टर isn't मुक्तd.
 *
 * Return: status bits of message रेजिस्टरs
 */
अटल u64 idt_ntb_msg_पढ़ो_sts(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस idt_nt_पढ़ो(ndev, IDT_NT_MSGSTS);
पूर्ण

/*
 * idt_ntb_msg_clear_sts() - clear status bits of message रेजिस्टरs
 *			     (NTB API callback)
 * @ntb:	NTB device context.
 * @sts_bits:	Status bits to clear.
 *
 * Clear bits in the status रेजिस्टर by writing ones.
 *
 * NOTE! Invalid bits are always considered cleared so it's not an error
 * to clear them over.
 *
 * Return: always zero as success.
 */
अटल पूर्णांक idt_ntb_msg_clear_sts(काष्ठा ntb_dev *ntb, u64 sts_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_nt_ग_लिखो(ndev, IDT_NT_MSGSTS, sts_bits);

	वापस 0;
पूर्ण

/*
 * idt_ntb_msg_set_mask() - set mask of message रेजिस्टर status bits
 *			    (NTB API callback)
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Mask the message status bits from raising an IRQ.
 *
 * Return: zero on success, negative error अगर invalid argument passed.
 */
अटल पूर्णांक idt_ntb_msg_set_mask(काष्ठा ntb_dev *ntb, u64 mask_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	वापस idt_reg_set_bits(ndev, IDT_NT_MSGSTSMSK, &ndev->msg_mask_lock,
				IDT_MSG_MASK, mask_bits);
पूर्ण

/*
 * idt_ntb_msg_clear_mask() - clear message रेजिस्टरs mask
 *			      (NTB API callback)
 * @ntb:	NTB device context.
 * @mask_bits:	Mask bits.
 *
 * Clear mask of message status bits IRQs.
 *
 * Return: always zero as success.
 */
अटल पूर्णांक idt_ntb_msg_clear_mask(काष्ठा ntb_dev *ntb, u64 mask_bits)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	idt_reg_clear_bits(ndev, IDT_NT_MSGSTSMSK, &ndev->msg_mask_lock,
			   mask_bits);

	वापस 0;
पूर्ण

/*
 * idt_ntb_msg_पढ़ो() - पढ़ो message रेजिस्टर with specअगरied index
 *			(NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	OUT - Port index of peer device a message retrieved from
 * @midx:	Message रेजिस्टर index
 *
 * Read data from the specअगरied message रेजिस्टर and source रेजिस्टर.
 *
 * Return: inbound message रेजिस्टर value.
 */
अटल u32 idt_ntb_msg_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक *pidx, पूर्णांक midx)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	अगर (midx < 0 || IDT_MSG_CNT <= midx)
		वापस ~(u32)0;

	/* Retrieve source port index of the message */
	अगर (pidx != शून्य) अणु
		u32 srcpart;

		srcpart = idt_nt_पढ़ो(ndev, ntdata_tbl.msgs[midx].src);
		*pidx = ndev->part_idx_map[srcpart];

		/* Sanity check partition index (क्रम initial हाल) */
		अगर (*pidx == -EINVAL)
			*pidx = 0;
	पूर्ण

	/* Retrieve data of the corresponding message रेजिस्टर */
	वापस idt_nt_पढ़ो(ndev, ntdata_tbl.msgs[midx].in);
पूर्ण

/*
 * idt_ntb_peer_msg_ग_लिखो() - ग_लिखो data to the specअगरied message रेजिस्टर
 *			      (NTB API callback)
 * @ntb:	NTB device context.
 * @pidx:	Port index of peer device a message being sent to
 * @midx:	Message रेजिस्टर index
 * @msg:	Data to send
 *
 * Just try to send data to a peer. Message status रेजिस्टर should be
 * checked by client driver.
 *
 * Return: zero on success, negative error अगर invalid argument passed.
 */
अटल पूर्णांक idt_ntb_peer_msg_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक midx,
				  u32 msg)
अणु
	काष्ठा idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	अचिन्हित दीर्घ irqflags;
	u32 swpmsgctl = 0;

	अगर (midx < 0 || IDT_MSG_CNT <= midx)
		वापस -EINVAL;

	अगर (pidx < 0 || ndev->peer_cnt <= pidx)
		वापस -EINVAL;

	/* Collect the routing inक्रमmation */
	swpmsgctl = SET_FIELD(SWPxMSGCTL_REG, 0, midx) |
		    SET_FIELD(SWPxMSGCTL_PART, 0, ndev->peers[pidx].part);

	/* Lock the messages routing table of the specअगरied रेजिस्टर */
	spin_lock_irqsave(&ndev->msg_locks[midx], irqflags);
	/* Set the route and send the data */
	idt_sw_ग_लिखो(ndev, partdata_tbl[ndev->part].msgctl[midx], swpmsgctl);
	idt_nt_ग_लिखो(ndev, ntdata_tbl.msgs[midx].out, msg);
	/* Unlock the messages routing table */
	spin_unlock_irqrestore(&ndev->msg_locks[midx], irqflags);

	/* Client driver shall check the status रेजिस्टर */
	वापस 0;
पूर्ण

/*=============================================================================
 *                      7. Temperature sensor operations
 *
 *    IDT PCIe-चयन has an embedded temperature sensor, which can be used to
 * check current chip core temperature. Since a workload environment can be
 * dअगरferent on dअगरferent platक्रमms, an offset and ADC/filter settings can be
 * specअगरied. Although the offset configuration is only exposed to the sysfs
 * hwmon पूर्णांकerface at the moment. The rest of the settings can be adjusted
 * क्रम instance by the BIOS/EEPROM firmware.
 *=============================================================================
 */

/*
 * idt_get_deg() - convert millidegree Celsius value to just degree
 * @mdegC:	IN - millidegree Celsius value
 *
 * Return: Degree corresponding to the passed millidegree value
 */
अटल अंतरभूत s8 idt_get_deg(दीर्घ mdegC)
अणु
	वापस mdegC / 1000;
पूर्ण

/*
 * idt_get_frac() - retrieve 0/0.5 fraction of the millidegree Celsius value
 * @mdegC:	IN - millidegree Celsius value
 *
 * Return: 0/0.5 degree fraction of the passed millidegree value
 */
अटल अंतरभूत u8 idt_get_deg_frac(दीर्घ mdegC)
अणु
	वापस (mdegC % 1000) >= 500 ? 5 : 0;
पूर्ण

/*
 * idt_get_temp_fmt() - convert millidegree Celsius value to 0:7:1 क्रमmat
 * @mdegC:	IN - millidegree Celsius value
 *
 * Return: 0:7:1 क्रमmat acceptable by the IDT temperature sensor
 */
अटल अंतरभूत u8 idt_temp_get_fmt(दीर्घ mdegC)
अणु
	वापस (idt_get_deg(mdegC) << 1) | (idt_get_deg_frac(mdegC) ? 1 : 0);
पूर्ण

/*
 * idt_get_temp_sval() - convert temp sample to चिन्हित millidegree Celsius
 * @data:	IN - shअगरted to LSB 8-bits temperature sample
 *
 * Return: चिन्हित millidegree Celsius
 */
अटल अंतरभूत दीर्घ idt_get_temp_sval(u32 data)
अणु
	वापस ((s8)data / 2) * 1000 + (data & 0x1 ? 500 : 0);
पूर्ण

/*
 * idt_get_temp_sval() - convert temp sample to अचिन्हित millidegree Celsius
 * @data:	IN - shअगरted to LSB 8-bits temperature sample
 *
 * Return: अचिन्हित millidegree Celsius
 */
अटल अंतरभूत दीर्घ idt_get_temp_uval(u32 data)
अणु
	वापस (data / 2) * 1000 + (data & 0x1 ? 500 : 0);
पूर्ण

/*
 * idt_पढ़ो_temp() - पढ़ो temperature from chip sensor
 * @ntb:	NTB device context.
 * @type:	IN - type of the temperature value to पढ़ो
 * @val:	OUT - पूर्णांकeger value of temperature in millidegree Celsius
 */
अटल व्योम idt_पढ़ो_temp(काष्ठा idt_ntb_dev *ndev,
			  स्थिर क्रमागत idt_temp_val type, दीर्घ *val)
अणु
	u32 data;

	/* Alter the temperature field in accordance with the passed type */
	चयन (type) अणु
	हाल IDT_TEMP_CUR:
		data = GET_FIELD(TMPSTS_TEMP,
				 idt_sw_पढ़ो(ndev, IDT_SW_TMPSTS));
		अवरोध;
	हाल IDT_TEMP_LOW:
		data = GET_FIELD(TMPSTS_LTEMP,
				 idt_sw_पढ़ो(ndev, IDT_SW_TMPSTS));
		अवरोध;
	हाल IDT_TEMP_HIGH:
		data = GET_FIELD(TMPSTS_HTEMP,
				 idt_sw_पढ़ो(ndev, IDT_SW_TMPSTS));
		अवरोध;
	हाल IDT_TEMP_OFFSET:
		/* This is the only field with चिन्हित 0:7:1 क्रमmat */
		data = GET_FIELD(TMPADJ_OFFSET,
				 idt_sw_पढ़ो(ndev, IDT_SW_TMPADJ));
		*val = idt_get_temp_sval(data);
		वापस;
	शेष:
		data = GET_FIELD(TMPSTS_TEMP,
				 idt_sw_पढ़ो(ndev, IDT_SW_TMPSTS));
		अवरोध;
	पूर्ण

	/* The rest of the fields accept अचिन्हित 0:7:1 क्रमmat */
	*val = idt_get_temp_uval(data);
पूर्ण

/*
 * idt_ग_लिखो_temp() - ग_लिखो temperature to the chip sensor रेजिस्टर
 * @ntb:	NTB device context.
 * @type:	IN - type of the temperature value to change
 * @val:	IN - पूर्णांकeger value of temperature in millidegree Celsius
 */
अटल व्योम idt_ग_लिखो_temp(काष्ठा idt_ntb_dev *ndev,
			   स्थिर क्रमागत idt_temp_val type, स्थिर दीर्घ val)
अणु
	अचिन्हित पूर्णांक reg;
	u32 data;
	u8 fmt;

	/* Retrieve the properly क्रमmatted temperature value */
	fmt = idt_temp_get_fmt(val);

	mutex_lock(&ndev->hwmon_mtx);
	चयन (type) अणु
	हाल IDT_TEMP_LOW:
		reg = IDT_SW_TMPALARM;
		data = SET_FIELD(TMPALARM_LTEMP, idt_sw_पढ़ो(ndev, reg), fmt) &
			~IDT_TMPALARM_IRQ_MASK;
		अवरोध;
	हाल IDT_TEMP_HIGH:
		reg = IDT_SW_TMPALARM;
		data = SET_FIELD(TMPALARM_HTEMP, idt_sw_पढ़ो(ndev, reg), fmt) &
			~IDT_TMPALARM_IRQ_MASK;
		अवरोध;
	हाल IDT_TEMP_OFFSET:
		reg = IDT_SW_TMPADJ;
		data = SET_FIELD(TMPADJ_OFFSET, idt_sw_पढ़ो(ndev, reg), fmt);
		अवरोध;
	शेष:
		जाओ inval_spin_unlock;
	पूर्ण

	idt_sw_ग_लिखो(ndev, reg, data);

inval_spin_unlock:
	mutex_unlock(&ndev->hwmon_mtx);
पूर्ण

/*
 * idt_sysfs_show_temp() - prपूर्णांकout corresponding temperature value
 * @dev:	Poपूर्णांकer to the NTB device काष्ठाure
 * @da:		Sensor device attribute काष्ठाure
 * @buf:	Buffer to prपूर्णांक temperature out
 *
 * Return: Number of written symbols or negative error
 */
अटल sमाप_प्रकार idt_sysfs_show_temp(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा idt_ntb_dev *ndev = dev_get_drvdata(dev);
	क्रमागत idt_temp_val type = attr->index;
	दीर्घ mdeg;

	idt_पढ़ो_temp(ndev, type, &mdeg);
	वापस प्र_लिखो(buf, "%ld\n", mdeg);
पूर्ण

/*
 * idt_sysfs_set_temp() - set corresponding temperature value
 * @dev:	Poपूर्णांकer to the NTB device काष्ठाure
 * @da:		Sensor device attribute काष्ठाure
 * @buf:	Buffer to prपूर्णांक temperature out
 * @count:	Size of the passed buffer
 *
 * Return: Number of written symbols or negative error
 */
अटल sमाप_प्रकार idt_sysfs_set_temp(काष्ठा device *dev,
				  काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा idt_ntb_dev *ndev = dev_get_drvdata(dev);
	क्रमागत idt_temp_val type = attr->index;
	दीर्घ mdeg;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &mdeg);
	अगर (ret)
		वापस ret;

	/* Clamp the passed value in accordance with the type */
	अगर (type == IDT_TEMP_OFFSET)
		mdeg = clamp_val(mdeg, IDT_TEMP_MIN_OFFSET,
				 IDT_TEMP_MAX_OFFSET);
	अन्यथा
		mdeg = clamp_val(mdeg, IDT_TEMP_MIN_MDEG, IDT_TEMP_MAX_MDEG);

	idt_ग_लिखो_temp(ndev, type, mdeg);

	वापस count;
पूर्ण

/*
 * idt_sysfs_reset_hist() - reset temperature history
 * @dev:	Poपूर्णांकer to the NTB device काष्ठाure
 * @da:		Sensor device attribute काष्ठाure
 * @buf:	Buffer to prपूर्णांक temperature out
 * @count:	Size of the passed buffer
 *
 * Return: Number of written symbols or negative error
 */
अटल sमाप_प्रकार idt_sysfs_reset_hist(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा idt_ntb_dev *ndev = dev_get_drvdata(dev);

	/* Just set the maximal value to the lowest temperature field and
	 * minimal value to the highest temperature field
	 */
	idt_ग_लिखो_temp(ndev, IDT_TEMP_LOW, IDT_TEMP_MAX_MDEG);
	idt_ग_लिखो_temp(ndev, IDT_TEMP_HIGH, IDT_TEMP_MIN_MDEG);

	वापस count;
पूर्ण

/*
 * Hwmon IDT sysfs attributes
 */
अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, idt_sysfs_show_temp, शून्य,
			  IDT_TEMP_CUR);
अटल SENSOR_DEVICE_ATTR(temp1_lowest, 0444, idt_sysfs_show_temp, शून्य,
			  IDT_TEMP_LOW);
अटल SENSOR_DEVICE_ATTR(temp1_highest, 0444, idt_sysfs_show_temp, शून्य,
			  IDT_TEMP_HIGH);
अटल SENSOR_DEVICE_ATTR(temp1_offset, 0644, idt_sysfs_show_temp,
			  idt_sysfs_set_temp, IDT_TEMP_OFFSET);
अटल DEVICE_ATTR(temp1_reset_history, 0200, शून्य, idt_sysfs_reset_hist);

/*
 * Hwmon IDT sysfs attributes group
 */
अटल काष्ठा attribute *idt_temp_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_lowest.dev_attr.attr,
	&sensor_dev_attr_temp1_highest.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&dev_attr_temp1_reset_history.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(idt_temp);

/*
 * idt_init_temp() - initialize temperature sensor पूर्णांकerface
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Simple sensor initializarion method is responsible क्रम device चयनing
 * on and resource management based hwmon पूर्णांकerface registration. Note, that
 * since the device is shared we won't disable it on हटाओ, but leave it
 * working until the प्रणाली is घातered off.
 */
अटल व्योम idt_init_temp(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा device *hwmon;

	/* Enable sensor अगर it hasn't been alपढ़ोy */
	idt_sw_ग_लिखो(ndev, IDT_SW_TMPCTL, 0x0);

	/* Initialize hwmon पूर्णांकerface fields */
	mutex_init(&ndev->hwmon_mtx);

	hwmon = devm_hwmon_device_रेजिस्टर_with_groups(&ndev->ntb.pdev->dev,
		ndev->swcfg->name, ndev, idt_temp_groups);
	अगर (IS_ERR(hwmon)) अणु
		dev_err(&ndev->ntb.pdev->dev, "Couldn't create hwmon device");
		वापस;
	पूर्ण

	dev_dbg(&ndev->ntb.pdev->dev, "Temperature HWmon interface registered");
पूर्ण

/*=============================================================================
 *                           8. ISRs related operations
 *
 *    IDT PCIe-चयन has strangely developed IRQ प्रणाली. There is just one
 * पूर्णांकerrupt vector क्रम करोorbell and message रेजिस्टरs. So the hardware driver
 * can't determine actual source of IRQ अगर, क्रम example, message event happened
 * जबतक any of unmasked करोorbell is still set. The similar situation may be अगर
 * चयन or temperature sensor events pop up. The dअगरference is that SEVENT
 * and TMPSENSOR bits of NT पूर्णांकerrupt status रेजिस्टर can be cleaned by
 * IRQ handler so a next पूर्णांकerrupt request won't have false handling of
 * corresponding events.
 *    The hardware driver has only bottom-half handler of the IRQ, since अगर any
 * of events happened the device won't उठाओ it again beक्रमe the last one is
 * handled by clearing of corresponding NTINTSTS bit.
 *=============================================================================
 */

अटल irqवापस_t idt_thपढ़ो_isr(पूर्णांक irq, व्योम *devid);

/*
 * idt_init_isr() - initialize PCIe पूर्णांकerrupt handler
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Return: zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_init_isr(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	u32 ntपूर्णांक_mask;
	पूर्णांक ret;

	/* Allocate just one पूर्णांकerrupt vector क्रम the ISR */
	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI | PCI_IRQ_LEGACY);
	अगर (ret != 1) अणु
		dev_err(&pdev->dev, "Failed to allocate IRQ vector");
		वापस ret;
	पूर्ण

	/* Retrieve the IRQ vector */
	ret = pci_irq_vector(pdev, 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get IRQ vector");
		जाओ err_मुक्त_vectors;
	पूर्ण

	/* Set the IRQ handler */
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, ret, शून्य, idt_thपढ़ो_isr,
					IRQF_ONESHOT, NTB_IRQNAME, ndev);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to set MSI IRQ handler, %d", ret);
		जाओ err_मुक्त_vectors;
	पूर्ण

	/* Unmask Message/Doorbell/SE पूर्णांकerrupts */
	ntपूर्णांक_mask = idt_nt_पढ़ो(ndev, IDT_NT_NTINTMSK) & ~IDT_NTINTMSK_ALL;
	idt_nt_ग_लिखो(ndev, IDT_NT_NTINTMSK, ntपूर्णांक_mask);

	/* From now on the पूर्णांकerrupts are enabled */
	dev_dbg(&pdev->dev, "NTB interrupts initialized");

	वापस 0;

err_मुक्त_vectors:
	pci_मुक्त_irq_vectors(pdev);

	वापस ret;
पूर्ण

/*
 * idt_deinit_ist() - deinitialize PCIe पूर्णांकerrupt handler
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Disable corresponding पूर्णांकerrupts and मुक्त allocated IRQ vectors.
 */
अटल व्योम idt_deinit_isr(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	u32 ntपूर्णांक_mask;

	/* Mask पूर्णांकerrupts back */
	ntपूर्णांक_mask = idt_nt_पढ़ो(ndev, IDT_NT_NTINTMSK) | IDT_NTINTMSK_ALL;
	idt_nt_ग_लिखो(ndev, IDT_NT_NTINTMSK, ntपूर्णांक_mask);

	/* Manually मुक्त IRQ otherwise PCI मुक्त irq vectors will fail */
	devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, 0), ndev);

	/* Free allocated IRQ vectors */
	pci_मुक्त_irq_vectors(pdev);

	dev_dbg(&pdev->dev, "NTB interrupts deinitialized");
पूर्ण

/*
 * idt_thपढ़ो_isr() - NT function पूर्णांकerrupts handler
 * @irq:	IRQ number
 * @devid:	Custom buffer
 *
 * It पढ़ोs current NT पूर्णांकerrupts state रेजिस्टर and handles all the event
 * it declares.
 * The method is bottom-half routine of actual शेष PCIe IRQ handler.
 */
अटल irqवापस_t idt_thपढ़ो_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा idt_ntb_dev *ndev = devid;
	bool handled = false;
	u32 ntपूर्णांक_sts;

	/* Read the NT पूर्णांकerrupts status रेजिस्टर */
	ntपूर्णांक_sts = idt_nt_पढ़ो(ndev, IDT_NT_NTINTSTS);

	/* Handle messaging पूर्णांकerrupts */
	अगर (ntपूर्णांक_sts & IDT_NTINTSTS_MSG) अणु
		idt_msg_isr(ndev, ntपूर्णांक_sts);
		handled = true;
	पूर्ण

	/* Handle करोorbell पूर्णांकerrupts */
	अगर (ntपूर्णांक_sts & IDT_NTINTSTS_DBELL) अणु
		idt_db_isr(ndev, ntपूर्णांक_sts);
		handled = true;
	पूर्ण

	/* Handle चयन event पूर्णांकerrupts */
	अगर (ntपूर्णांक_sts & IDT_NTINTSTS_SEVENT) अणु
		idt_se_isr(ndev, ntपूर्णांक_sts);
		handled = true;
	पूर्ण

	dev_dbg(&ndev->ntb.pdev->dev, "IDT IRQs 0x%08x handled", ntपूर्णांक_sts);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/*===========================================================================
 *                     9. NTB hardware driver initialization
 *===========================================================================
 */

/*
 * NTB API operations
 */
अटल स्थिर काष्ठा ntb_dev_ops idt_ntb_ops = अणु
	.port_number		= idt_ntb_port_number,
	.peer_port_count	= idt_ntb_peer_port_count,
	.peer_port_number	= idt_ntb_peer_port_number,
	.peer_port_idx		= idt_ntb_peer_port_idx,
	.link_is_up		= idt_ntb_link_is_up,
	.link_enable		= idt_ntb_link_enable,
	.link_disable		= idt_ntb_link_disable,
	.mw_count		= idt_ntb_mw_count,
	.mw_get_align		= idt_ntb_mw_get_align,
	.peer_mw_count		= idt_ntb_peer_mw_count,
	.peer_mw_get_addr	= idt_ntb_peer_mw_get_addr,
	.peer_mw_set_trans	= idt_ntb_peer_mw_set_trans,
	.peer_mw_clear_trans	= idt_ntb_peer_mw_clear_trans,
	.db_valid_mask		= idt_ntb_db_valid_mask,
	.db_पढ़ो		= idt_ntb_db_पढ़ो,
	.db_clear		= idt_ntb_db_clear,
	.db_पढ़ो_mask		= idt_ntb_db_पढ़ो_mask,
	.db_set_mask		= idt_ntb_db_set_mask,
	.db_clear_mask		= idt_ntb_db_clear_mask,
	.peer_db_set		= idt_ntb_peer_db_set,
	.msg_count		= idt_ntb_msg_count,
	.msg_inbits		= idt_ntb_msg_inbits,
	.msg_outbits		= idt_ntb_msg_outbits,
	.msg_पढ़ो_sts		= idt_ntb_msg_पढ़ो_sts,
	.msg_clear_sts		= idt_ntb_msg_clear_sts,
	.msg_set_mask		= idt_ntb_msg_set_mask,
	.msg_clear_mask		= idt_ntb_msg_clear_mask,
	.msg_पढ़ो		= idt_ntb_msg_पढ़ो,
	.peer_msg_ग_लिखो		= idt_ntb_peer_msg_ग_लिखो
पूर्ण;

/*
 * idt_रेजिस्टर_device() - रेजिस्टर IDT NTB device
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Return: zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_रेजिस्टर_device(काष्ठा idt_ntb_dev *ndev)
अणु
	पूर्णांक ret;

	/* Initialize the rest of NTB device काष्ठाure and रेजिस्टर it */
	ndev->ntb.ops = &idt_ntb_ops;
	ndev->ntb.topo = NTB_TOPO_SWITCH;

	ret = ntb_रेजिस्टर_device(&ndev->ntb);
	अगर (ret != 0) अणु
		dev_err(&ndev->ntb.pdev->dev, "Failed to register NTB device");
		वापस ret;
	पूर्ण

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device successfully registered");

	वापस 0;
पूर्ण

/*
 * idt_unरेजिस्टर_device() - unरेजिस्टर IDT NTB device
 * @ndev:	IDT NTB hardware driver descriptor
 */
अटल व्योम idt_unरेजिस्टर_device(काष्ठा idt_ntb_dev *ndev)
अणु
	/* Just unरेजिस्टर the NTB device */
	ntb_unरेजिस्टर_device(&ndev->ntb);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device unregistered");
पूर्ण

/*=============================================================================
 *                        10. DebugFS node initialization
 *=============================================================================
 */

अटल sमाप_प्रकार idt_dbgfs_info_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				   माप_प्रकार count, loff_t *offp);

/*
 * Driver DebugFS info file operations
 */
अटल स्थिर काष्ठा file_operations idt_dbgfs_info_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = idt_dbgfs_info_पढ़ो
पूर्ण;

/*
 * idt_dbgfs_info_पढ़ो() - DebugFS पढ़ो info node callback
 * @file:	File node descriptor.
 * @ubuf:	User-space buffer to put data to
 * @count:	Size of the buffer
 * @offp:	Offset within the buffer
 */
अटल sमाप_प्रकार idt_dbgfs_info_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				   माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा idt_ntb_dev *ndev = filp->निजी_data;
	अचिन्हित अक्षर idx, pidx, cnt;
	अचिन्हित दीर्घ irqflags, mdeg;
	sमाप_प्रकार ret = 0, off = 0;
	क्रमागत ntb_speed speed;
	क्रमागत ntb_width width;
	अक्षर *strbuf;
	माप_प्रकार size;
	u32 data;

	/* Lets limit the buffer size the way the Intel/AMD drivers करो */
	size = min_t(माप_प्रकार, count, 0x1000U);

	/* Allocate the memory क्रम the buffer */
	strbuf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (strbuf == शून्य)
		वापस -ENOMEM;

	/* Put the data पूर्णांकo the string buffer */
	off += scnम_लिखो(strbuf + off, size - off,
		"\n\t\tIDT NTB device Information:\n\n");

	/* General local device configurations */
	off += scnम_लिखो(strbuf + off, size - off,
		"Local Port %hhu, Partition %hhu\n", ndev->port, ndev->part);

	/* Peer ports inक्रमmation */
	off += scnम_लिखो(strbuf + off, size - off, "Peers:\n");
	क्रम (idx = 0; idx < ndev->peer_cnt; idx++) अणु
		off += scnम_लिखो(strbuf + off, size - off,
			"\t%hhu. Port %hhu, Partition %hhu\n",
			idx, ndev->peers[idx].port, ndev->peers[idx].part);
	पूर्ण

	/* Links status */
	data = idt_ntb_link_is_up(&ndev->ntb, &speed, &width);
	off += scnम_लिखो(strbuf + off, size - off,
		"NTB link status\t- 0x%08x, ", data);
	off += scnम_लिखो(strbuf + off, size - off, "PCIe Gen %d x%d lanes\n",
		speed, width);

	/* Mapping table entries */
	off += scnम_लिखो(strbuf + off, size - off, "NTB Mapping Table:\n");
	क्रम (idx = 0; idx < IDT_MTBL_ENTRY_CNT; idx++) अणु
		spin_lock_irqsave(&ndev->mtbl_lock, irqflags);
		idt_nt_ग_लिखो(ndev, IDT_NT_NTMTBLADDR, idx);
		data = idt_nt_पढ़ो(ndev, IDT_NT_NTMTBLDATA);
		spin_unlock_irqrestore(&ndev->mtbl_lock, irqflags);

		/* Prपूर्णांक valid entries only */
		अगर (data & IDT_NTMTBLDATA_VALID) अणु
			off += scnम_लिखो(strbuf + off, size - off,
				"\t%hhu. Partition %d, Requester ID 0x%04x\n",
				idx, GET_FIELD(NTMTBLDATA_PART, data),
				GET_FIELD(NTMTBLDATA_REQID, data));
		पूर्ण
	पूर्ण
	off += scnम_लिखो(strbuf + off, size - off, "\n");

	/* Outbound memory winकरोws inक्रमmation */
	off += scnम_लिखो(strbuf + off, size - off,
		"Outbound Memory Windows:\n");
	क्रम (idx = 0; idx < ndev->mw_cnt; idx += cnt) अणु
		data = ndev->mws[idx].type;
		cnt = idt_get_mw_count(data);

		/* Prपूर्णांक Memory Winकरोw inक्रमmation */
		अगर (data == IDT_MW_सूची)
			off += scnम_लिखो(strbuf + off, size - off,
				"\t%hhu.\t", idx);
		अन्यथा
			off += scnम_लिखो(strbuf + off, size - off,
				"\t%hhu-%hhu.\t", idx, idx + cnt - 1);

		off += scnम_लिखो(strbuf + off, size - off, "%s BAR%hhu, ",
			idt_get_mw_name(data), ndev->mws[idx].bar);

		off += scnम_लिखो(strbuf + off, size - off,
			"Address align 0x%08llx, ", ndev->mws[idx].addr_align);

		off += scnम_लिखो(strbuf + off, size - off,
			"Size align 0x%08llx, Size max %llu\n",
			ndev->mws[idx].size_align, ndev->mws[idx].size_max);
	पूर्ण

	/* Inbound memory winकरोws inक्रमmation */
	क्रम (pidx = 0; pidx < ndev->peer_cnt; pidx++) अणु
		off += scnम_लिखो(strbuf + off, size - off,
			"Inbound Memory Windows for peer %hhu (Port %hhu):\n",
			pidx, ndev->peers[pidx].port);

		/* Prपूर्णांक Memory Winकरोws inक्रमmation */
		क्रम (idx = 0; idx < ndev->peers[pidx].mw_cnt; idx += cnt) अणु
			data = ndev->peers[pidx].mws[idx].type;
			cnt = idt_get_mw_count(data);

			अगर (data == IDT_MW_सूची)
				off += scnम_लिखो(strbuf + off, size - off,
					"\t%hhu.\t", idx);
			अन्यथा
				off += scnम_लिखो(strbuf + off, size - off,
					"\t%hhu-%hhu.\t", idx, idx + cnt - 1);

			off += scnम_लिखो(strbuf + off, size - off,
				"%s BAR%hhu, ", idt_get_mw_name(data),
				ndev->peers[pidx].mws[idx].bar);

			off += scnम_लिखो(strbuf + off, size - off,
				"Address align 0x%08llx, ",
				ndev->peers[pidx].mws[idx].addr_align);

			off += scnम_लिखो(strbuf + off, size - off,
				"Size align 0x%08llx, Size max %llu\n",
				ndev->peers[pidx].mws[idx].size_align,
				ndev->peers[pidx].mws[idx].size_max);
		पूर्ण
	पूर्ण
	off += scnम_लिखो(strbuf + off, size - off, "\n");

	/* Doorbell inक्रमmation */
	data = idt_sw_पढ़ो(ndev, IDT_SW_GDBELLSTS);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Global Doorbell state\t- 0x%08x\n", data);
	data = idt_ntb_db_पढ़ो(&ndev->ntb);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Local  Doorbell state\t- 0x%08x\n", data);
	data = idt_nt_पढ़ो(ndev, IDT_NT_INDBELLMSK);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Local  Doorbell mask\t- 0x%08x\n", data);
	off += scnम_लिखो(strbuf + off, size - off, "\n");

	/* Messaging inक्रमmation */
	off += scnम_लिखो(strbuf + off, size - off,
		 "Message event valid\t- 0x%08x\n", IDT_MSG_MASK);
	data = idt_ntb_msg_पढ़ो_sts(&ndev->ntb);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Message event status\t- 0x%08x\n", data);
	data = idt_nt_पढ़ो(ndev, IDT_NT_MSGSTSMSK);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Message event mask\t- 0x%08x\n", data);
	off += scnम_लिखो(strbuf + off, size - off,
		 "Message data:\n");
	क्रम (idx = 0; idx < IDT_MSG_CNT; idx++) अणु
		पूर्णांक src;
		data = idt_ntb_msg_पढ़ो(&ndev->ntb, &src, idx);
		off += scnम_लिखो(strbuf + off, size - off,
			"\t%hhu. 0x%08x from peer %hhu (Port %hhu)\n",
			idx, data, src, ndev->peers[src].port);
	पूर्ण
	off += scnम_लिखो(strbuf + off, size - off, "\n");

	/* Current temperature */
	idt_पढ़ो_temp(ndev, IDT_TEMP_CUR, &mdeg);
	off += scnम_लिखो(strbuf + off, size - off,
		"Switch temperature\t\t- %hhd.%hhuC\n",
		idt_get_deg(mdeg), idt_get_deg_frac(mdeg));

	/* Copy the buffer to the User Space */
	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, strbuf, off);
	kमुक्त(strbuf);

	वापस ret;
पूर्ण

/*
 * idt_init_dbgfs() - initialize DebugFS node
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Return: zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_init_dbgfs(काष्ठा idt_ntb_dev *ndev)
अणु
	अक्षर devname[64];

	/* If the top directory is not created then करो nothing */
	अगर (IS_ERR_OR_शून्य(dbgfs_topdir)) अणु
		dev_info(&ndev->ntb.pdev->dev, "Top DebugFS directory absent");
		वापस PTR_ERR_OR_ZERO(dbgfs_topdir);
	पूर्ण

	/* Create the info file node */
	snम_लिखो(devname, 64, "info:%s", pci_name(ndev->ntb.pdev));
	ndev->dbgfs_info = debugfs_create_file(devname, 0400, dbgfs_topdir,
		ndev, &idt_dbgfs_info_ops);
	अगर (IS_ERR(ndev->dbgfs_info)) अणु
		dev_dbg(&ndev->ntb.pdev->dev, "Failed to create DebugFS node");
		वापस PTR_ERR(ndev->dbgfs_info);
	पूर्ण

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device DebugFS node created");

	वापस 0;
पूर्ण

/*
 * idt_deinit_dbgfs() - deinitialize DebugFS node
 * @ndev:	IDT NTB hardware driver descriptor
 *
 * Just discard the info node from DebugFS
 */
अटल व्योम idt_deinit_dbgfs(काष्ठा idt_ntb_dev *ndev)
अणु
	debugfs_हटाओ(ndev->dbgfs_info);

	dev_dbg(&ndev->ntb.pdev->dev, "NTB device DebugFS node discarded");
पूर्ण

/*=============================================================================
 *                     11. Basic PCIe device initialization
 *=============================================================================
 */

/*
 * idt_check_setup() - Check whether the IDT PCIe-swtich is properly
 *		       pre-initialized
 * @pdev:	Poपूर्णांकer to the PCI device descriptor
 *
 * Return: zero on success, otherwise a negative error number.
 */
अटल पूर्णांक idt_check_setup(काष्ठा pci_dev *pdev)
अणु
	u32 data;
	पूर्णांक ret;

	/* Read the BARSETUP0 */
	ret = pci_पढ़ो_config_dword(pdev, IDT_NT_BARSETUP0, &data);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev,
			"Failed to read BARSETUP0 config register");
		वापस ret;
	पूर्ण

	/* Check whether the BAR0 रेजिस्टर is enabled to be of config space */
	अगर (!(data & IDT_BARSETUP_EN) || !(data & IDT_BARSETUP_MODE_CFG)) अणु
		dev_err(&pdev->dev, "BAR0 doesn't map config space");
		वापस -EINVAL;
	पूर्ण

	/* Configuration space BAR0 must have certain size */
	अगर ((data & IDT_BARSETUP_SIZE_MASK) != IDT_BARSETUP_SIZE_CFG) अणु
		dev_err(&pdev->dev, "Invalid size of config space");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&pdev->dev, "NTB device pre-initialized correctly");

	वापस 0;
पूर्ण

/*
 * Create the IDT PCIe-चयन driver descriptor
 * @pdev:	Poपूर्णांकer to the PCI device descriptor
 * @id:		IDT PCIe-device configuration
 *
 * It just allocates a memory क्रम IDT PCIe-चयन device काष्ठाure and
 * initializes some commonly used fields.
 *
 * No need of release method, since managed device resource is used क्रम
 * memory allocation.
 *
 * Return: poपूर्णांकer to the descriptor, otherwise a negative error number.
 */
अटल काष्ठा idt_ntb_dev *idt_create_dev(काष्ठा pci_dev *pdev,
					  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा idt_ntb_dev *ndev;

	/* Allocate memory क्रम the IDT PCIe-device descriptor */
	ndev = devm_kzalloc(&pdev->dev, माप(*ndev), GFP_KERNEL);
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "Memory allocation failed for descriptor");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Save the IDT PCIe-चयन ports configuration */
	ndev->swcfg = (काष्ठा idt_89hpes_cfg *)id->driver_data;
	/* Save the PCI-device poपूर्णांकer inside the NTB device काष्ठाure */
	ndev->ntb.pdev = pdev;

	/* Initialize spin locker of Doorbell, Message and GASA रेजिस्टरs */
	spin_lock_init(&ndev->db_mask_lock);
	spin_lock_init(&ndev->msg_mask_lock);
	spin_lock_init(&ndev->gasa_lock);

	dev_info(&pdev->dev, "IDT %s discovered", ndev->swcfg->name);

	dev_dbg(&pdev->dev, "NTB device descriptor created");

	वापस ndev;
पूर्ण

/*
 * idt_init_pci() - initialize the basic PCI-related subप्रणाली
 * @ndev:	Poपूर्णांकer to the IDT PCIe-चयन driver descriptor
 *
 * Managed device resources will be मुक्तd स्वतःmatically in हाल of failure or
 * driver detachment.
 *
 * Return: zero on success, otherwise negative error number.
 */
अटल पूर्णांक idt_init_pci(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;
	पूर्णांक ret;

	/* Initialize the bit mask of PCI/NTB DMA */
	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret != 0) अणु
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (ret != 0) अणु
			dev_err(&pdev->dev, "Failed to set DMA bit mask\n");
			वापस ret;
		पूर्ण
		dev_warn(&pdev->dev, "Cannot set DMA highmem bit mask\n");
	पूर्ण
	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret != 0) अणु
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"Failed to set consistent DMA bit mask\n");
			वापस ret;
		पूर्ण
		dev_warn(&pdev->dev,
			"Cannot set consistent DMA highmem bit mask\n");
	पूर्ण

	/*
	 * Enable the device advanced error reporting. It's not critical to
	 * have AER disabled in the kernel.
	 */
	ret = pci_enable_pcie_error_reporting(pdev);
	अगर (ret != 0)
		dev_warn(&pdev->dev, "PCIe AER capability disabled\n");
	अन्यथा /* Cleanup nonfatal error status beक्रमe getting to init */
		pci_aer_clear_nonfatal_status(pdev);

	/* First enable the PCI device */
	ret = pcim_enable_device(pdev);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to enable PCIe device\n");
		जाओ err_disable_aer;
	पूर्ण

	/*
	 * Enable the bus mastering, which effectively enables MSI IRQs and
	 * Request TLPs translation
	 */
	pci_set_master(pdev);

	/* Request all BARs resources and map BAR0 only */
	ret = pcim_iomap_regions_request_all(pdev, 1, NTB_NAME);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to request resources\n");
		जाओ err_clear_master;
	पूर्ण

	/* Retrieve भव address of BAR0 - PCI configuration space */
	ndev->cfgspc = pcim_iomap_table(pdev)[0];

	/* Put the IDT driver data poपूर्णांकer to the PCI-device निजी poपूर्णांकer */
	pci_set_drvdata(pdev, ndev);

	dev_dbg(&pdev->dev, "NT-function PCIe interface initialized");

	वापस 0;

err_clear_master:
	pci_clear_master(pdev);
err_disable_aer:
	(व्योम)pci_disable_pcie_error_reporting(pdev);

	वापस ret;
पूर्ण

/*
 * idt_deinit_pci() - deinitialize the basic PCI-related subप्रणाली
 * @ndev:	Poपूर्णांकer to the IDT PCIe-चयन driver descriptor
 *
 * Managed resources will be मुक्तd on the driver detachment
 */
अटल व्योम idt_deinit_pci(काष्ठा idt_ntb_dev *ndev)
अणु
	काष्ठा pci_dev *pdev = ndev->ntb.pdev;

	/* Clean up the PCI-device निजी data poपूर्णांकer */
	pci_set_drvdata(pdev, शून्य);

	/* Clear the bus master disabling the Request TLPs translation */
	pci_clear_master(pdev);

	/* Disable the AER capability */
	(व्योम)pci_disable_pcie_error_reporting(pdev);

	dev_dbg(&pdev->dev, "NT-function PCIe interface cleared");
पूर्ण

/*===========================================================================
 *                       12. PCI bus callback functions
 *===========================================================================
 */

/*
 * idt_pci_probe() - PCI device probe callback
 * @pdev:	Poपूर्णांकer to PCI device काष्ठाure
 * @id:		PCIe device custom descriptor
 *
 * Return: zero on success, otherwise negative error number
 */
अटल पूर्णांक idt_pci_probe(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा idt_ntb_dev *ndev;
	पूर्णांक ret;

	/* Check whether IDT PCIe-चयन is properly pre-initialized */
	ret = idt_check_setup(pdev);
	अगर (ret != 0)
		वापस ret;

	/* Allocate the memory क्रम IDT NTB device data */
	ndev = idt_create_dev(pdev, id);
	अगर (IS_ERR(ndev))
		वापस PTR_ERR(ndev);

	/* Initialize the basic PCI subप्रणाली of the device */
	ret = idt_init_pci(ndev);
	अगर (ret != 0)
		वापस ret;

	/* Scan ports of the IDT PCIe-चयन */
	(व्योम)idt_scan_ports(ndev);

	/* Initialize NTB link events subप्रणाली */
	idt_init_link(ndev);

	/* Initialize MWs subप्रणाली */
	ret = idt_init_mws(ndev);
	अगर (ret != 0)
		जाओ err_deinit_link;

	/* Initialize Messaging subप्रणाली */
	idt_init_msg(ndev);

	/* Initialize hwmon पूर्णांकerface */
	idt_init_temp(ndev);

	/* Initialize IDT पूर्णांकerrupts handler */
	ret = idt_init_isr(ndev);
	अगर (ret != 0)
		जाओ err_deinit_link;

	/* Register IDT NTB devices on the NTB bus */
	ret = idt_रेजिस्टर_device(ndev);
	अगर (ret != 0)
		जाओ err_deinit_isr;

	/* Initialize DebugFS info node */
	(व्योम)idt_init_dbgfs(ndev);

	/* IDT PCIe-चयन NTB driver is finally initialized */
	dev_info(&pdev->dev, "IDT NTB device is ready");

	/* May the क्रमce be with us... */
	वापस 0;

err_deinit_isr:
	idt_deinit_isr(ndev);
err_deinit_link:
	idt_deinit_link(ndev);
	idt_deinit_pci(ndev);

	वापस ret;
पूर्ण

/*
 * idt_pci_probe() - PCI device हटाओ callback
 * @pdev:	Poपूर्णांकer to PCI device काष्ठाure
 */
अटल व्योम idt_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा idt_ntb_dev *ndev = pci_get_drvdata(pdev);

	/* Deinit the DebugFS node */
	idt_deinit_dbgfs(ndev);

	/* Unरेजिस्टर NTB device */
	idt_unरेजिस्टर_device(ndev);

	/* Stop the पूर्णांकerrupts handling */
	idt_deinit_isr(ndev);

	/* Deinitialize link event subप्रणाली */
	idt_deinit_link(ndev);

	/* Deinit basic PCI subप्रणाली */
	idt_deinit_pci(ndev);

	/* IDT PCIe-चयन NTB driver is finally initialized */
	dev_info(&pdev->dev, "IDT NTB device is removed");

	/* Sayonara... */
पूर्ण

/*
 * IDT PCIe-चयन models ports configuration काष्ठाures
 */
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes24nt6ag2_config = अणु
	.name = "89HPES24NT6AG2",
	.port_cnt = 6, .ports = अणु0, 2, 4, 6, 8, 12पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes32nt8ag2_config = अणु
	.name = "89HPES32NT8AG2",
	.port_cnt = 8, .ports = अणु0, 2, 4, 6, 8, 12, 16, 20पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes32nt8bg2_config = अणु
	.name = "89HPES32NT8BG2",
	.port_cnt = 8, .ports = अणु0, 2, 4, 6, 8, 12, 16, 20पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes12nt12g2_config = अणु
	.name = "89HPES12NT12G2",
	.port_cnt = 3, .ports = अणु0, 8, 16पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes16nt16g2_config = अणु
	.name = "89HPES16NT16G2",
	.port_cnt = 4, .ports = अणु0, 8, 12, 16पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes24nt24g2_config = अणु
	.name = "89HPES24NT24G2",
	.port_cnt = 8, .ports = अणु0, 2, 4, 6, 8, 12, 16, 20पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes32nt24ag2_config = अणु
	.name = "89HPES32NT24AG2",
	.port_cnt = 8, .ports = अणु0, 2, 4, 6, 8, 12, 16, 20पूर्ण
पूर्ण;
अटल स्थिर काष्ठा idt_89hpes_cfg idt_89hpes32nt24bg2_config = अणु
	.name = "89HPES32NT24BG2",
	.port_cnt = 8, .ports = अणु0, 2, 4, 6, 8, 12, 16, 20पूर्ण
पूर्ण;

/*
 * PCI-ids table of the supported IDT PCIe-चयन devices
 */
अटल स्थिर काष्ठा pci_device_id idt_pci_tbl[] = अणु
	अणुIDT_PCI_DEVICE_IDS(89HPES24NT6AG2,  idt_89hpes24nt6ag2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES32NT8AG2,  idt_89hpes32nt8ag2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES32NT8BG2,  idt_89hpes32nt8bg2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES12NT12G2,  idt_89hpes12nt12g2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES16NT16G2,  idt_89hpes16nt16g2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES24NT24G2,  idt_89hpes24nt24g2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES32NT24AG2, idt_89hpes32nt24ag2_config)पूर्ण,
	अणुIDT_PCI_DEVICE_IDS(89HPES32NT24BG2, idt_89hpes32nt24bg2_config)पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, idt_pci_tbl);

/*
 * IDT PCIe-चयन NT-function device driver काष्ठाure definition
 */
अटल काष्ठा pci_driver idt_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.probe		= idt_pci_probe,
	.हटाओ		= idt_pci_हटाओ,
	.id_table	= idt_pci_tbl,
पूर्ण;

अटल पूर्णांक __init idt_pci_driver_init(व्योम)
अणु
	pr_info("%s %s\n", NTB_DESC, NTB_VER);

	/* Create the top DebugFS directory अगर the FS is initialized */
	अगर (debugfs_initialized())
		dbgfs_topdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	/* Register the NTB hardware driver to handle the PCI device */
	वापस pci_रेजिस्टर_driver(&idt_pci_driver);
पूर्ण
module_init(idt_pci_driver_init);

अटल व्योम __निकास idt_pci_driver_निकास(व्योम)
अणु
	/* Unरेजिस्टर the NTB hardware driver */
	pci_unरेजिस्टर_driver(&idt_pci_driver);

	/* Discard the top DebugFS directory */
	debugfs_हटाओ_recursive(dbgfs_topdir);
पूर्ण
module_निकास(idt_pci_driver_निकास);

