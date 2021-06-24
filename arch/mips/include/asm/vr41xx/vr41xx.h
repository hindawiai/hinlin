<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/यंत्र-mips/vr41xx/vr41xx.h
 *
 * Include file क्रम NEC VR4100 series.
 *
 * Copyright (C) 1999 Michael Klar
 * Copyright (C) 2001, 2002 Paul Mundt
 * Copyright (C) 2002 MontaVista Software, Inc.
 * Copyright (C) 2002 TimeSys Corp.
 * Copyright (C) 2003-2008 Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __NEC_VR41XX_H
#घोषणा __NEC_VR41XX_H

#समावेश <linux/पूर्णांकerrupt.h>

/*
 * CPU Revision
 */
/* VR4122 0x00000c70-0x00000c72 */
#घोषणा PRID_VR4122_REV1_0	0x00000c70
#घोषणा PRID_VR4122_REV2_0	0x00000c70
#घोषणा PRID_VR4122_REV2_1	0x00000c70
#घोषणा PRID_VR4122_REV3_0	0x00000c71
#घोषणा PRID_VR4122_REV3_1	0x00000c72

/* VR4181A 0x00000c73-0x00000c7f */
#घोषणा PRID_VR4181A_REV1_0	0x00000c73
#घोषणा PRID_VR4181A_REV1_1	0x00000c74

/* VR4131 0x00000c80-0x00000c83 */
#घोषणा PRID_VR4131_REV1_2	0x00000c80
#घोषणा PRID_VR4131_REV2_0	0x00000c81
#घोषणा PRID_VR4131_REV2_1	0x00000c82
#घोषणा PRID_VR4131_REV2_2	0x00000c83

/* VR4133 0x00000c84- */
#घोषणा PRID_VR4133		0x00000c84

/*
 * Bus Control Uपूर्णांक
 */
बाह्य अचिन्हित दीर्घ vr41xx_calculate_घड़ी_frequency(व्योम);
बाह्य अचिन्हित दीर्घ vr41xx_get_vtघड़ी_frequency(व्योम);
बाह्य अचिन्हित दीर्घ vr41xx_get_tघड़ी_frequency(व्योम);

/*
 * Clock Mask Unit
 */
प्रकार क्रमागत अणु
	PIU_CLOCK,
	SIU_CLOCK,
	AIU_CLOCK,
	KIU_CLOCK,
	FIR_CLOCK,
	DSIU_CLOCK,
	CSI_CLOCK,
	PCIU_CLOCK,
	HSP_CLOCK,
	PCI_CLOCK,
	CEU_CLOCK,
	ETHER0_CLOCK,
	ETHER1_CLOCK
पूर्ण vr41xx_घड़ी_प्रकार;

बाह्य व्योम vr41xx_supply_घड़ी(vr41xx_घड़ी_प्रकार घड़ी);
बाह्य व्योम vr41xx_mask_घड़ी(vr41xx_घड़ी_प्रकार घड़ी);

/*
 * Interrupt Control Unit
 */
बाह्य पूर्णांक vr41xx_set_पूर्णांकassign(अचिन्हित पूर्णांक irq, अचिन्हित अक्षर पूर्णांकassign);
बाह्य पूर्णांक cascade_irq(अचिन्हित पूर्णांक irq, पूर्णांक (*get_irq)(अचिन्हित पूर्णांक));

#घोषणा PIUINT_COMMAND		0x0040
#घोषणा PIUINT_DATA		0x0020
#घोषणा PIUINT_PAGE1		0x0010
#घोषणा PIUINT_PAGE0		0x0008
#घोषणा PIUINT_DATALOST		0x0004
#घोषणा PIUINT_STATUSCHANGE	0x0001

बाह्य व्योम vr41xx_enable_piuपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_piuपूर्णांक(uपूर्णांक16_t mask);

#घोषणा AIUINT_INPUT_DMAEND	0x0800
#घोषणा AIUINT_INPUT_DMAHALT	0x0400
#घोषणा AIUINT_INPUT_DATALOST	0x0200
#घोषणा AIUINT_INPUT_DATA	0x0100
#घोषणा AIUINT_OUTPUT_DMAEND	0x0008
#घोषणा AIUINT_OUTPUT_DMAHALT	0x0004
#घोषणा AIUINT_OUTPUT_NODATA	0x0002

बाह्य व्योम vr41xx_enable_aiuपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_aiuपूर्णांक(uपूर्णांक16_t mask);

#घोषणा KIUINT_DATALOST		0x0004
#घोषणा KIUINT_DATAREADY	0x0002
#घोषणा KIUINT_SCAN		0x0001

बाह्य व्योम vr41xx_enable_kiuपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_kiuपूर्णांक(uपूर्णांक16_t mask);

#घोषणा DSIUINT_CTS		0x0800
#घोषणा DSIUINT_RXERR		0x0400
#घोषणा DSIUINT_RX		0x0200
#घोषणा DSIUINT_TX		0x0100
#घोषणा DSIUINT_ALL		0x0f00

बाह्य व्योम vr41xx_enable_dsiuपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_dsiuपूर्णांक(uपूर्णांक16_t mask);

#घोषणा FIRINT_UNIT		0x0010
#घोषणा FIRINT_RX_DMAEND	0x0008
#घोषणा FIRINT_RX_DMAHALT	0x0004
#घोषणा FIRINT_TX_DMAEND	0x0002
#घोषणा FIRINT_TX_DMAHALT	0x0001

बाह्य व्योम vr41xx_enable_firपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_firपूर्णांक(uपूर्णांक16_t mask);

बाह्य व्योम vr41xx_enable_pciपूर्णांक(व्योम);
बाह्य व्योम vr41xx_disable_pciपूर्णांक(व्योम);

बाह्य व्योम vr41xx_enable_scuपूर्णांक(व्योम);
बाह्य व्योम vr41xx_disable_scuपूर्णांक(व्योम);

#घोषणा CSIINT_TX_DMAEND	0x0040
#घोषणा CSIINT_TX_DMAHALT	0x0020
#घोषणा CSIINT_TX_DATA		0x0010
#घोषणा CSIINT_TX_FIFOEMPTY	0x0008
#घोषणा CSIINT_RX_DMAEND	0x0004
#घोषणा CSIINT_RX_DMAHALT	0x0002
#घोषणा CSIINT_RX_FIFOEMPTY	0x0001

बाह्य व्योम vr41xx_enable_csiपूर्णांक(uपूर्णांक16_t mask);
बाह्य व्योम vr41xx_disable_csiपूर्णांक(uपूर्णांक16_t mask);

बाह्य व्योम vr41xx_enable_bcuपूर्णांक(व्योम);
बाह्य व्योम vr41xx_disable_bcuपूर्णांक(व्योम);

#अगर_घोषित CONFIG_SERIAL_VR41XX_CONSOLE
बाह्य व्योम vr41xx_siu_setup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम vr41xx_siu_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NEC_VR41XX_H */
