<शैली गुरु>
/*
 * PMC-Sierra SPC 8001 SAS/SATA based host adapters driver
 *
 * Copyright (c) 2008-2009 USI Co., Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#अगर_अघोषित _PM8001_CHIPS_H_
#घोषणा _PM8001_CHIPS_H_

अटल अंतरभूत u32 pm8001_पढ़ो_32(व्योम *virt_addr)
अणु
	वापस *((u32 *)virt_addr);
पूर्ण

अटल अंतरभूत व्योम pm8001_ग_लिखो_32(व्योम *addr, u32 offset, __le32 val)
अणु
	*((__le32 *)(addr + offset)) = val;
पूर्ण

अटल अंतरभूत u32 pm8001_cr32(काष्ठा pm8001_hba_info *pm8001_ha, u32 bar,
		u32 offset)
अणु
	वापस पढ़ोl(pm8001_ha->io_mem[bar].memvirtaddr + offset);
पूर्ण

अटल अंतरभूत व्योम pm8001_cw32(काष्ठा pm8001_hba_info *pm8001_ha, u32 bar,
		u32 addr, u32 val)
अणु
	ग_लिखोl(val, pm8001_ha->io_mem[bar].memvirtaddr + addr);
पूर्ण
अटल अंतरभूत u32 pm8001_mr32(व्योम __iomem *addr, u32 offset)
अणु
	वापस पढ़ोl(addr + offset);
पूर्ण
अटल अंतरभूत व्योम pm8001_mw32(व्योम __iomem *addr, u32 offset, u32 val)
अणु
	ग_लिखोl(val, addr + offset);
पूर्ण
अटल अंतरभूत u32 get_pci_bar_index(u32 pcibar)
अणु
		चयन (pcibar) अणु
		हाल 0x18:
		हाल 0x1C:
			वापस 1;
		हाल 0x20:
			वापस 2;
		हाल 0x24:
			वापस 3;
		शेष:
			वापस 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर  /* _PM8001_CHIPS_H_ */

