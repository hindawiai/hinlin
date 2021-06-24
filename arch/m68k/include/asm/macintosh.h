<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACINTOSH_H
#घोषणा __ASM_MACINTOSH_H

#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/bootinfo-mac.h>


/*
 *	Apple Macपूर्णांकoshisms
 */

बाह्य व्योम mac_reset(व्योम);
बाह्य व्योम mac_घातeroff(व्योम);
बाह्य व्योम mac_init_IRQ(व्योम);

बाह्य व्योम mac_irq_enable(काष्ठा irq_data *data);
बाह्य व्योम mac_irq_disable(काष्ठा irq_data *data);

बाह्य अचिन्हित अक्षर mac_pram_पढ़ो_byte(पूर्णांक);
बाह्य व्योम mac_pram_ग_लिखो_byte(अचिन्हित अक्षर, पूर्णांक);
बाह्य sमाप_प्रकार mac_pram_get_size(व्योम);

/*
 *	Macपूर्णांकosh Table
 */

काष्ठा mac_model
अणु
	लघु ident;
	अक्षर *name;
	अक्षर adb_type;
	अक्षर via_type;
	अक्षर scsi_type;
	अक्षर ide_type;
	अक्षर scc_type;
	अक्षर ether_type;
	अक्षर expansion_type;
	अक्षर floppy_type;
पूर्ण;

#घोषणा MAC_ADB_NONE		0
#घोषणा MAC_ADB_II		1
#घोषणा MAC_ADB_EGRET		2
#घोषणा MAC_ADB_CUDA		3
#घोषणा MAC_ADB_PB1		4
#घोषणा MAC_ADB_PB2		5
#घोषणा MAC_ADB_IOP		6

#घोषणा MAC_VIA_II		1
#घोषणा MAC_VIA_IICI		2
#घोषणा MAC_VIA_QUADRA		3

#घोषणा MAC_SCSI_NONE		0
#घोषणा MAC_SCSI_OLD		1
#घोषणा MAC_SCSI_QUADRA		2
#घोषणा MAC_SCSI_QUADRA2	3
#घोषणा MAC_SCSI_QUADRA3	4
#घोषणा MAC_SCSI_IIFX		5
#घोषणा MAC_SCSI_DUO		6
#घोषणा MAC_SCSI_LC		7

#घोषणा MAC_IDE_NONE		0
#घोषणा MAC_IDE_QUADRA		1
#घोषणा MAC_IDE_PB		2
#घोषणा MAC_IDE_BABOON		3

#घोषणा MAC_SCC_II		1
#घोषणा MAC_SCC_IOP		2
#घोषणा MAC_SCC_QUADRA		3
#घोषणा MAC_SCC_PSC		4

#घोषणा MAC_ETHER_NONE		0
#घोषणा MAC_ETHER_SONIC		1
#घोषणा MAC_ETHER_MACE		2

#घोषणा MAC_EXP_NONE		0
#घोषणा MAC_EXP_PDS		1 /* Accepts only a PDS card */
#घोषणा MAC_EXP_NUBUS		2 /* Accepts only NuBus card(s) */
#घोषणा MAC_EXP_PDS_NUBUS	3 /* Accepts PDS card and/or NuBus card(s) */
#घोषणा MAC_EXP_PDS_COMM	4 /* Accepts PDS card or Comm Slot card */

#घोषणा MAC_FLOPPY_UNSUPPORTED	0
#घोषणा MAC_FLOPPY_SWIM_IOP	1
#घोषणा MAC_FLOPPY_OLD		2
#घोषणा MAC_FLOPPY_QUADRA	3
#घोषणा MAC_FLOPPY_LC		4

बाह्य काष्ठा mac_model *macपूर्णांकosh_config;


    /*
     * Internal representation of the Mac hardware, filled in from bootinfo
     */

काष्ठा mac_booter_data
अणु
	अचिन्हित दीर्घ videoaddr;
	अचिन्हित दीर्घ videorow;
	अचिन्हित दीर्घ videodepth;
	अचिन्हित दीर्घ dimensions;
	अचिन्हित दीर्घ bootसमय;
	अचिन्हित दीर्घ gmtbias;
	अचिन्हित दीर्घ videological;
	अचिन्हित दीर्घ sccbase;
	अचिन्हित दीर्घ id;
	अचिन्हित दीर्घ memsize;
	अचिन्हित दीर्घ cpuid;
	अचिन्हित दीर्घ rombase;
पूर्ण;

बाह्य काष्ठा mac_booter_data mac_bi_data;

#पूर्ण_अगर
