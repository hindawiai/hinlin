<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_H_
#घोषणा _IPA_H_

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm_wakeup.h>

#समावेश "ipa_version.h"
#समावेश "gsi.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_qmi.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_interrupt.h"

काष्ठा clk;
काष्ठा icc_path;
काष्ठा net_device;
काष्ठा platक्रमm_device;

काष्ठा ipa_घड़ी;
काष्ठा ipa_smp2p;
काष्ठा ipa_पूर्णांकerrupt;

/**
 * क्रमागत ipa_flag - IPA state flags
 * @IPA_FLAG_RESUMED:	Whether resume from suspend has been संकेतed
 * @IPA_FLAG_COUNT:	Number of defined IPA flags
 */
क्रमागत ipa_flag अणु
	IPA_FLAG_RESUMED,
	IPA_FLAG_COUNT,		/* Last; not a flag */
पूर्ण;

/**
 * काष्ठा ipa - IPA inक्रमmation
 * @gsi:		Embedded GSI काष्ठाure
 * @flags:		Boolean state flags
 * @version:		IPA hardware version
 * @pdev:		Platक्रमm device
 * @completion:		Used to संकेत pipeline clear transfer complete
 * @nb:			Notअगरier block used क्रम remoteproc SSR
 * @notअगरier:		Remoteproc SSR notअगरier
 * @smp2p:		SMP2P inक्रमmation
 * @घड़ी:		IPA घड़ीing inक्रमmation
 * @table_addr:		DMA address of filter/route table content
 * @table_virt:		Virtual address of filter/route table content
 * @पूर्णांकerrupt:		IPA Interrupt inक्रमmation
 * @uc_loaded:		true after microcontroller has reported it's पढ़ोy
 * @reg_addr:		DMA address used क्रम IPA रेजिस्टर access
 * @reg_virt:		Virtual address used क्रम IPA रेजिस्टर access
 * @mem_addr:		DMA address of IPA-local memory space
 * @mem_virt:		Virtual address of IPA-local memory space
 * @mem_offset:		Offset from @mem_virt used क्रम access to IPA memory
 * @mem_size:		Total size (bytes) of memory at @mem_virt
 * @mem_count:		Number of entries in the mem array
 * @mem:		Array of IPA-local memory region descriptors
 * @imem_iova:		I/O भव address of IPA region in IMEM
 * @imem_size:		Size of IMEM region
 * @smem_iova:		I/O भव address of IPA region in SMEM
 * @smem_size:		Size of SMEM region
 * @zero_addr:		DMA address of pपुनः_स्मृतिated zero-filled memory
 * @zero_virt:		Virtual address of pपुनः_स्मृतिated zero-filled memory
 * @zero_size:		Size (bytes) of pपुनः_स्मृतिated zero-filled memory
 * @available:		Bit mask indicating endpoपूर्णांकs hardware supports
 * @filter_map:		Bit mask indicating endpoपूर्णांकs that support filtering
 * @initialized:	Bit mask indicating endpoपूर्णांकs initialized
 * @set_up:		Bit mask indicating endpoपूर्णांकs set up
 * @enabled:		Bit mask indicating endpoपूर्णांकs enabled
 * @endpoपूर्णांक:		Array of endpoपूर्णांक inक्रमmation
 * @channel_map:	Mapping of GSI channel to IPA endpoपूर्णांक
 * @name_map:		Mapping of IPA endpoपूर्णांक name to IPA endpoपूर्णांक
 * @setup_complete:	Flag indicating whether setup stage has completed
 * @modem_state:	State of modem (stopped, running)
 * @modem_netdev:	Network device काष्ठाure used क्रम modem
 * @qmi:		QMI inक्रमmation
 */
काष्ठा ipa अणु
	काष्ठा gsi gsi;
	DECLARE_BITMAP(flags, IPA_FLAG_COUNT);
	क्रमागत ipa_version version;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा completion completion;
	काष्ठा notअगरier_block nb;
	व्योम *notअगरier;
	काष्ठा ipa_smp2p *smp2p;
	काष्ठा ipa_घड़ी *घड़ी;

	dma_addr_t table_addr;
	__le64 *table_virt;

	काष्ठा ipa_पूर्णांकerrupt *पूर्णांकerrupt;
	bool uc_loaded;

	dma_addr_t reg_addr;
	व्योम __iomem *reg_virt;

	dma_addr_t mem_addr;
	व्योम *mem_virt;
	u32 mem_offset;
	u32 mem_size;
	u32 mem_count;
	स्थिर काष्ठा ipa_mem *mem;

	अचिन्हित दीर्घ imem_iova;
	माप_प्रकार imem_size;

	अचिन्हित दीर्घ smem_iova;
	माप_प्रकार smem_size;

	dma_addr_t zero_addr;
	व्योम *zero_virt;
	माप_प्रकार zero_size;

	/* Bit masks indicating endpoपूर्णांक state */
	u32 available;		/* supported by hardware */
	u32 filter_map;
	u32 initialized;
	u32 set_up;
	u32 enabled;

	काष्ठा ipa_endpoपूर्णांक endpoपूर्णांक[IPA_ENDPOपूर्णांक_उच्च];
	काष्ठा ipa_endpoपूर्णांक *channel_map[GSI_CHANNEL_COUNT_MAX];
	काष्ठा ipa_endpoपूर्णांक *name_map[IPA_ENDPOINT_COUNT];

	bool setup_complete;

	atomic_t modem_state;		/* क्रमागत ipa_modem_state */
	काष्ठा net_device *modem_netdev;
	काष्ठा ipa_qmi qmi;
पूर्ण;

/**
 * ipa_setup() - Perक्रमm IPA setup
 * @ipa:		IPA poपूर्णांकer
 *
 * IPA initialization is broken पूर्णांकo stages:  init; config; and setup.
 * (These have inverses निकास, deconfig, and tearकरोwn.)
 *
 * Activities perक्रमmed at the init stage can be करोne without requiring
 * any access to IPA hardware.  Activities perक्रमmed at the config stage
 * require the IPA घड़ी to be running, because they involve access
 * to IPA रेजिस्टरs.  The setup stage is perक्रमmed only after the GSI
 * hardware is पढ़ोy (more on this below).  The setup stage allows
 * the AP to perक्रमm more complex initialization by issuing "immediate
 * commands" using a special पूर्णांकerface to the IPA.
 *
 * This function, @ipa_setup(), starts the setup stage.
 *
 * In order क्रम the GSI hardware to be functional it needs firmware to be
 * loaded (in addition to some other low-level initialization).  This early
 * GSI initialization can be करोne either by Trust Zone on the AP or by the
 * modem.
 *
 * If it's करोne by Trust Zone, the AP loads the GSI firmware and supplies
 * it to Trust Zone to verअगरy and install.  When this completes, अगर
 * verअगरication was successful, the GSI layer is पढ़ोy and ipa_setup()
 * implements the setup phase of initialization.
 *
 * If the modem perक्रमms early GSI initialization, the AP needs to know
 * when this has occurred.  An SMP2P पूर्णांकerrupt is used क्रम this purpose,
 * and receipt of that पूर्णांकerrupt triggers the call to ipa_setup().
 */
पूर्णांक ipa_setup(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_H_ */
