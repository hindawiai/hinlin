<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * core.h - DesignWare HS OTG Controller common declarations
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __DWC2_CORE_H__
#घोषणा __DWC2_CORE_H__

#समावेश <linux/acpi.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/phy.h>
#समावेश "hw.h"

/*
 * Suggested defines क्रम tracers:
 * - no_prपूर्णांकk:    Disable tracing
 * - pr_info:      Prपूर्णांक this info to the console
 * - trace_prपूर्णांकk: Prपूर्णांक this info to trace buffer (good क्रम verbose logging)
 */

#घोषणा DWC2_TRACE_SCHEDULER		no_prपूर्णांकk
#घोषणा DWC2_TRACE_SCHEDULER_VB		no_prपूर्णांकk

/* Detailed scheduler tracing, but won't overwhelm console */
#घोषणा dwc2_sch_dbg(hsotg, fmt, ...)					\
	DWC2_TRACE_SCHEDULER(pr_fmt("%s: SCH: " fmt),			\
			     dev_name(hsotg->dev), ##__VA_ARGS__)

/* Verbose scheduler tracing */
#घोषणा dwc2_sch_vdbg(hsotg, fmt, ...)					\
	DWC2_TRACE_SCHEDULER_VB(pr_fmt("%s: SCH: " fmt),		\
				dev_name(hsotg->dev), ##__VA_ARGS__)

/* Maximum number of Endpoपूर्णांकs/HostChannels */
#घोषणा MAX_EPS_CHANNELS	16

/* dwc2-hsotg declarations */
अटल स्थिर अक्षर * स्थिर dwc2_hsotg_supply_names[] = अणु
	"vusb_d",               /* digital USB supply, 1.2V */
	"vusb_a",               /* analog USB supply, 1.1V */
पूर्ण;

#घोषणा DWC2_NUM_SUPPLIES ARRAY_SIZE(dwc2_hsotg_supply_names)

/*
 * EP0_MPS_LIMIT
 *
 * Unक्रमtunately there seems to be a limit of the amount of data that can
 * be transferred by IN transactions on EP0. This is either 127 bytes or 3
 * packets (which practically means 1 packet and 63 bytes of data) when the
 * MPS is set to 64.
 *
 * This means अगर we are wanting to move >127 bytes of data, we need to
 * split the transactions up, but just करोing one packet at a समय करोes
 * not work (this may be an implicit DATA0 PID on first packet of the
 * transaction) and करोing 2 packets is outside the controller's limits.
 *
 * If we try to lower the MPS size क्रम EP0, then no transfers work properly
 * क्रम EP0, and the प्रणाली will fail basic क्रमागतeration. As no cause क्रम this
 * has currently been found, we cannot support any large IN transfers क्रम
 * EP0.
 */
#घोषणा EP0_MPS_LIMIT   64

काष्ठा dwc2_hsotg;
काष्ठा dwc2_hsotg_req;

/**
 * काष्ठा dwc2_hsotg_ep - driver endpoपूर्णांक definition.
 * @ep: The gadget layer representation of the endpoपूर्णांक.
 * @name: The driver generated name क्रम the endpoपूर्णांक.
 * @queue: Queue of requests क्रम this endpoपूर्णांक.
 * @parent: Reference back to the parent device काष्ठाure.
 * @req: The current request that the endpoपूर्णांक is processing. This is
 *       used to indicate an request has been loaded onto the endpoपूर्णांक
 *       and has yet to be completed (maybe due to data move, or simply
 *       aरुकोing an ack from the core all the data has been completed).
 * @debugfs: File entry क्रम debugfs file क्रम this endpoपूर्णांक.
 * @dir_in: Set to true अगर this endpoपूर्णांक is of the IN direction, which
 *          means that it is sending data to the Host.
 * @map_dir: Set to the value of dir_in when the DMA buffer is mapped.
 * @index: The index क्रम the endpoपूर्णांक रेजिस्टरs.
 * @mc: Multi Count - number of transactions per microframe
 * @पूर्णांकerval: Interval क्रम periodic endpoपूर्णांकs, in frames or microframes.
 * @name: The name array passed to the USB core.
 * @halted: Set अगर the endpoपूर्णांक has been halted.
 * @periodic: Set अगर this is a periodic ep, such as Interrupt
 * @isochronous: Set अगर this is a isochronous ep
 * @send_zlp: Set अगर we need to send a zero-length packet.
 * @desc_list_dma: The DMA address of descriptor chain currently in use.
 * @desc_list: Poपूर्णांकer to descriptor DMA chain head currently in use.
 * @desc_count: Count of entries within the DMA descriptor chain of EP.
 * @next_desc: index of next मुक्त descriptor in the ISOC chain under SW control.
 * @compl_desc: index of next descriptor to be completed by xFerComplete
 * @total_data: The total number of data bytes करोne.
 * @fअगरo_size: The size of the FIFO (क्रम periodic IN endpoपूर्णांकs)
 * @fअगरo_index: For Dedicated FIFO operation, only FIFO0 can be used क्रम EP0.
 * @fअगरo_load: The amount of data loaded पूर्णांकo the FIFO (periodic IN)
 * @last_load: The offset of data क्रम the last start of request.
 * @size_loaded: The last loaded size क्रम DxEPTSIZE क्रम periodic IN
 * @target_frame: Targeted frame num to setup next ISOC transfer
 * @frame_overrun: Indicates SOF number overrun in DSTS
 *
 * This is the driver's state क्रम each रेजिस्टरed endpoपूर्णांक, allowing it
 * to keep track of transactions that need करोing. Each endpoपूर्णांक has a
 * lock to protect the state, to try and aव्योम using an overall lock
 * क्रम the host controller as much as possible.
 *
 * For periodic IN endpoपूर्णांकs, we have fअगरo_size and fअगरo_load to try
 * and keep track of the amount of data in the periodic FIFO क्रम each
 * of these as we करोn't have a status रेजिस्टर that tells us how much
 * is in each of them. (note, this may actually be useless inक्रमmation
 * as in shared-fअगरo mode periodic in acts like a single-frame packet
 * buffer than a fअगरo)
 */
काष्ठा dwc2_hsotg_ep अणु
	काष्ठा usb_ep           ep;
	काष्ठा list_head        queue;
	काष्ठा dwc2_hsotg       *parent;
	काष्ठा dwc2_hsotg_req    *req;
	काष्ठा dentry           *debugfs;

	अचिन्हित दीर्घ           total_data;
	अचिन्हित पूर्णांक            size_loaded;
	अचिन्हित पूर्णांक            last_load;
	अचिन्हित पूर्णांक            fअगरo_load;
	अचिन्हित लघु          fअगरo_size;
	अचिन्हित लघु		fअगरo_index;

	अचिन्हित अक्षर           dir_in;
	अचिन्हित अक्षर           map_dir;
	अचिन्हित अक्षर           index;
	अचिन्हित अक्षर           mc;
	u16                     पूर्णांकerval;

	अचिन्हित पूर्णांक            halted:1;
	अचिन्हित पूर्णांक            periodic:1;
	अचिन्हित पूर्णांक            isochronous:1;
	अचिन्हित पूर्णांक            send_zlp:1;
	अचिन्हित पूर्णांक            target_frame;
#घोषणा TARGET_FRAME_INITIAL   0xFFFFFFFF
	bool			frame_overrun;

	dma_addr_t		desc_list_dma;
	काष्ठा dwc2_dma_desc	*desc_list;
	u8			desc_count;

	अचिन्हित पूर्णांक		next_desc;
	अचिन्हित पूर्णांक		compl_desc;

	अक्षर                    name[10];
पूर्ण;

/**
 * काष्ठा dwc2_hsotg_req - data transfer request
 * @req: The USB gadget request
 * @queue: The list of requests क्रम the endpoपूर्णांक this is queued क्रम.
 * @saved_req_buf: variable to save req.buf when bounce buffers are used.
 */
काष्ठा dwc2_hsotg_req अणु
	काष्ठा usb_request      req;
	काष्ठा list_head        queue;
	व्योम *saved_req_buf;
पूर्ण;

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
#घोषणा call_gadget(_hs, _entry) \
करो अणु \
	अगर ((_hs)->gadget.speed != USB_SPEED_UNKNOWN && \
		(_hs)->driver && (_hs)->driver->_entry) अणु \
		spin_unlock(&_hs->lock); \
		(_hs)->driver->_entry(&(_hs)->gadget); \
		spin_lock(&_hs->lock); \
	पूर्ण \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा call_gadget(_hs, _entry)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा dwc2_hsotg;
काष्ठा dwc2_host_chan;

/* Device States */
क्रमागत dwc2_lx_state अणु
	DWC2_L0,	/* On state */
	DWC2_L1,	/* LPM sleep state */
	DWC2_L2,	/* USB suspend state */
	DWC2_L3,	/* Off state */
पूर्ण;

/* Gadget ep0 states */
क्रमागत dwc2_ep0_state अणु
	DWC2_EP0_SETUP,
	DWC2_EP0_DATA_IN,
	DWC2_EP0_DATA_OUT,
	DWC2_EP0_STATUS_IN,
	DWC2_EP0_STATUS_OUT,
पूर्ण;

/**
 * काष्ठा dwc2_core_params - Parameters क्रम configuring the core
 *
 * @otg_cap:            Specअगरies the OTG capabilities.
 *                       0 - HNP and SRP capable
 *                       1 - SRP Only capable
 *                       2 - No HNP/SRP capable (always available)
 *                      Defaults to best available option (0, 1, then 2)
 * @host_dma:           Specअगरies whether to use slave or DMA mode क्रम accessing
 *                      the data FIFOs. The driver will स्वतःmatically detect the
 *                      value क्रम this parameter अगर none is specअगरied.
 *                       0 - Slave (always available)
 *                       1 - DMA (शेष, अगर available)
 * @dma_desc_enable:    When DMA mode is enabled, specअगरies whether to use
 *                      address DMA mode or descriptor DMA mode क्रम accessing
 *                      the data FIFOs. The driver will स्वतःmatically detect the
 *                      value क्रम this अगर none is specअगरied.
 *                       0 - Address DMA
 *                       1 - Descriptor DMA (शेष, अगर available)
 * @dma_desc_fs_enable: When DMA mode is enabled, specअगरies whether to use
 *                      address DMA mode or descriptor DMA mode क्रम accessing
 *                      the data FIFOs in Full Speed mode only. The driver
 *                      will स्वतःmatically detect the value क्रम this अगर none is
 *                      specअगरied.
 *                       0 - Address DMA
 *                       1 - Descriptor DMA in FS (शेष, अगर available)
 * @speed:              Specअगरies the maximum speed of operation in host and
 *                      device mode. The actual speed depends on the speed of
 *                      the attached device and the value of phy_type.
 *                       0 - High Speed
 *                           (शेष when phy_type is UTMI+ or ULPI)
 *                       1 - Full Speed
 *                           (शेष when phy_type is Full Speed)
 * @enable_dynamic_fअगरo: 0 - Use coreConsultant-specअगरied FIFO size parameters
 *                       1 - Allow dynamic FIFO sizing (शेष, अगर available)
 * @en_multiple_tx_fअगरo: Specअगरies whether dedicated per-endpoपूर्णांक transmit FIFOs
 *                      are enabled क्रम non-periodic IN endpoपूर्णांकs in device
 *                      mode.
 * @host_rx_fअगरo_size:  Number of 4-byte words in the Rx FIFO in host mode when
 *                      dynamic FIFO sizing is enabled
 *                       16 to 32768
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @host_nperio_tx_fअगरo_size: Number of 4-byte words in the non-periodic Tx FIFO
 *                      in host mode when dynamic FIFO sizing is enabled
 *                       16 to 32768
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @host_perio_tx_fअगरo_size: Number of 4-byte words in the periodic Tx FIFO in
 *                      host mode when dynamic FIFO sizing is enabled
 *                       16 to 32768
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @max_transfer_size:  The maximum transfer size supported, in bytes
 *                       2047 to 65,535
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @max_packet_count:   The maximum number of packets in a transfer
 *                       15 to 511
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @host_channels:      The number of host channel रेजिस्टरs to use
 *                       1 to 16
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @phy_type:           Specअगरies the type of PHY पूर्णांकerface to use. By शेष,
 *                      the driver will स्वतःmatically detect the phy_type.
 *                       0 - Full Speed Phy
 *                       1 - UTMI+ Phy
 *                       2 - ULPI Phy
 *                      Defaults to best available option (2, 1, then 0)
 * @phy_uपंचांगi_width:     Specअगरies the UTMI+ Data Width (in bits). This parameter
 *                      is applicable क्रम a phy_type of UTMI+ or ULPI. (For a
 *                      ULPI phy_type, this parameter indicates the data width
 *                      between the MAC and the ULPI Wrapper.) Also, this
 *                      parameter is applicable only अगर the OTG_HSPHY_WIDTH cC
 *                      parameter was set to "8 and 16 bits", meaning that the
 *                      core has been configured to work at either data path
 *                      width.
 *                       8 or 16 (शेष 16 अगर available)
 * @phy_ulpi_ddr:       Specअगरies whether the ULPI operates at द्विगुन or single
 *                      data rate. This parameter is only applicable अगर phy_type
 *                      is ULPI.
 *                       0 - single data rate ULPI पूर्णांकerface with 8 bit wide
 *                           data bus (शेष)
 *                       1 - द्विगुन data rate ULPI पूर्णांकerface with 4 bit wide
 *                           data bus
 * @phy_ulpi_ext_vbus:  For a ULPI phy, specअगरies whether to use the पूर्णांकernal or
 *                      बाह्यal supply to drive the VBus
 *                       0 - Internal supply (शेष)
 *                       1 - External supply
 * @i2c_enable:         Specअगरies whether to use the I2Cपूर्णांकerface क्रम a full
 *                      speed PHY. This parameter is only applicable अगर phy_type
 *                      is FS.
 *                       0 - No (शेष)
 *                       1 - Yes
 * @ipg_isoc_en:        Indicates the IPG supports is enabled or disabled.
 *                       0 - Disable (शेष)
 *                       1 - Enable
 * @acg_enable:		For enabling Active Clock Gating in the controller
 *                       0 - No
 *                       1 - Yes
 * @ulpi_fs_ls:         Make ULPI phy operate in FS/LS mode only
 *                       0 - No (शेष)
 *                       1 - Yes
 * @host_support_fs_ls_low_घातer: Specअगरies whether low घातer mode is supported
 *                      when attached to a Full Speed or Low Speed device in
 *                      host mode.
 *                       0 - Don't support low घातer mode (शेष)
 *                       1 - Support low घातer mode
 * @host_ls_low_घातer_phy_clk: Specअगरies the PHY घड़ी rate in low घातer mode
 *                      when connected to a Low Speed device in host
 *                      mode. This parameter is applicable only अगर
 *                      host_support_fs_ls_low_घातer is enabled.
 *                       0 - 48 MHz
 *                           (शेष when phy_type is UTMI+ or ULPI)
 *                       1 - 6 MHz
 *                           (शेष when phy_type is Full Speed)
 * @oc_disable:		Flag to disable overcurrent condition.
 *			0 - Allow overcurrent condition to get detected
 *			1 - Disable overcurrent condtion to get detected
 * @ts_dline:           Enable Term Select Dline pulsing
 *                       0 - No (शेष)
 *                       1 - Yes
 * @reload_ctl:         Allow dynamic reloading of HFIR रेजिस्टर during runसमय
 *                       0 - No (शेष क्रम core < 2.92a)
 *                       1 - Yes (शेष क्रम core >= 2.92a)
 * @ahbcfg:             This field allows the शेष value of the GAHBCFG
 *                      रेजिस्टर to be overridden
 *                       -1         - GAHBCFG value will be set to 0x06
 *                                    (INCR, शेष)
 *                       all others - GAHBCFG value will be overridden with
 *                                    this value
 *                      Not all bits can be controlled like this, the
 *                      bits defined by GAHBCFG_CTRL_MASK are controlled
 *                      by the driver and are ignored in this
 *                      configuration value.
 * @uframe_sched:       True to enable the microframe scheduler
 * @बाह्यal_id_pin_ctl: Specअगरies whether ID pin is handled बाह्यally.
 *                      Disable CONIDSTSCHNG controller पूर्णांकerrupt in such
 *                      हाल.
 *                      0 - No (शेष)
 *                      1 - Yes
 * @घातer_करोwn:         Specअगरies whether the controller support घातer_करोwn.
 *			If घातer_करोwn is enabled, the controller will enter
 *			घातer_करोwn in both peripheral and host mode when
 *			needed.
 *			0 - No (शेष)
 *			1 - Partial घातer करोwn
 *			2 - Hibernation
 * @lpm:		Enable LPM support.
 *			0 - No
 *			1 - Yes
 * @lpm_घड़ी_gating:		Enable core PHY घड़ी gating.
 *			0 - No
 *			1 - Yes
 * @besl:		Enable LPM Errata support.
 *			0 - No
 *			1 - Yes
 * @hird_threshold_en:	HIRD or HIRD Threshold enable.
 *			0 - No
 *			1 - Yes
 * @hird_threshold:	Value of BESL or HIRD Threshold.
 * @ref_clk_per:        Indicates in terms of pico seconds the period
 *                      of ref_clk.
 *			62500 - 16MHz
 *                      58823 - 17MHz
 *                      52083 - 19.2MHz
 *			50000 - 20MHz
 *			41666 - 24MHz
 *			33333 - 30MHz (शेष)
 *			25000 - 40MHz
 * @sof_cnt_wkup_alert: Indicates in term of number of SOF's after which
 *                      the controller should generate an पूर्णांकerrupt अगर the
 *                      device had been in L1 state until that period.
 *                      This is used by SW to initiate Remote WakeUp in the
 *                      controller so as to sync to the uF number from the host.
 * @activate_sपंचांग_fs_transceiver: Activate पूर्णांकernal transceiver using GGPIO
 *			रेजिस्टर.
 *			0 - Deactivate the transceiver (शेष)
 *			1 - Activate the transceiver
 * @activate_sपंचांग_id_vb_detection: Activate बाह्यal ID pin and Vbus level
 *			detection using GGPIO रेजिस्टर.
 *			0 - Deactivate the बाह्यal level detection (शेष)
 *			1 - Activate the बाह्यal level detection
 * @g_dma:              Enables gadget dma usage (शेष: स्वतःdetect).
 * @g_dma_desc:         Enables gadget descriptor DMA (शेष: स्वतःdetect).
 * @g_rx_fअगरo_size:	The periodic rx fअगरo size क्रम the device, in
 *			DWORDS from 16-32768 (शेष: 2048 अगर
 *			possible, otherwise स्वतःdetect).
 * @g_np_tx_fअगरo_size:	The non-periodic tx fअगरo size क्रम the device in
 *			DWORDS from 16-32768 (शेष: 1024 अगर
 *			possible, otherwise स्वतःdetect).
 * @g_tx_fअगरo_size:	An array of TX fअगरo sizes in dedicated fअगरo
 *			mode. Each value corresponds to one EP
 *			starting from EP1 (max 15 values). Sizes are
 *			in DWORDS with possible values from
 *			16-32768 (शेष: 256, 256, 256, 256, 768,
 *			768, 768, 768, 0, 0, 0, 0, 0, 0, 0).
 * @change_speed_quirk: Change speed configuration to DWC2_SPEED_PARAM_FULL
 *                      जबतक full&low speed device connect. And change speed
 *                      back to DWC2_SPEED_PARAM_HIGH जबतक device is gone.
 *			0 - No (शेष)
 *			1 - Yes
 * @service_पूर्णांकerval:   Enable service पूर्णांकerval based scheduling.
 *                      0 - No
 *                      1 - Yes
 *
 * The following parameters may be specअगरied when starting the module. These
 * parameters define how the DWC_otg controller should be configured. A
 * value of -1 (or any other out of range value) क्रम any parameter means
 * to पढ़ो the value from hardware (अगर possible) or use the builtin
 * शेष described above.
 */
काष्ठा dwc2_core_params अणु
	u8 otg_cap;
#घोषणा DWC2_CAP_PARAM_HNP_SRP_CAPABLE		0
#घोषणा DWC2_CAP_PARAM_SRP_ONLY_CAPABLE		1
#घोषणा DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE	2

	u8 phy_type;
#घोषणा DWC2_PHY_TYPE_PARAM_FS		0
#घोषणा DWC2_PHY_TYPE_PARAM_UTMI	1
#घोषणा DWC2_PHY_TYPE_PARAM_ULPI	2

	u8 speed;
#घोषणा DWC2_SPEED_PARAM_HIGH	0
#घोषणा DWC2_SPEED_PARAM_FULL	1
#घोषणा DWC2_SPEED_PARAM_LOW	2

	u8 phy_uपंचांगi_width;
	bool phy_ulpi_ddr;
	bool phy_ulpi_ext_vbus;
	bool enable_dynamic_fअगरo;
	bool en_multiple_tx_fअगरo;
	bool i2c_enable;
	bool acg_enable;
	bool ulpi_fs_ls;
	bool ts_dline;
	bool reload_ctl;
	bool uframe_sched;
	bool बाह्यal_id_pin_ctl;

	पूर्णांक घातer_करोwn;
#घोषणा DWC2_POWER_DOWN_PARAM_NONE		0
#घोषणा DWC2_POWER_DOWN_PARAM_PARTIAL		1
#घोषणा DWC2_POWER_DOWN_PARAM_HIBERNATION	2

	bool lpm;
	bool lpm_घड़ी_gating;
	bool besl;
	bool hird_threshold_en;
	bool service_पूर्णांकerval;
	u8 hird_threshold;
	bool activate_sपंचांग_fs_transceiver;
	bool activate_sपंचांग_id_vb_detection;
	bool ipg_isoc_en;
	u16 max_packet_count;
	u32 max_transfer_size;
	u32 ahbcfg;

	/* GREFCLK parameters */
	u32 ref_clk_per;
	u16 sof_cnt_wkup_alert;

	/* Host parameters */
	bool host_dma;
	bool dma_desc_enable;
	bool dma_desc_fs_enable;
	bool host_support_fs_ls_low_घातer;
	bool host_ls_low_घातer_phy_clk;
	bool oc_disable;

	u8 host_channels;
	u16 host_rx_fअगरo_size;
	u16 host_nperio_tx_fअगरo_size;
	u16 host_perio_tx_fअगरo_size;

	/* Gadget parameters */
	bool g_dma;
	bool g_dma_desc;
	u32 g_rx_fअगरo_size;
	u32 g_np_tx_fअगरo_size;
	u32 g_tx_fअगरo_size[MAX_EPS_CHANNELS];

	bool change_speed_quirk;
पूर्ण;

/**
 * काष्ठा dwc2_hw_params - Autodetected parameters.
 *
 * These parameters are the various parameters पढ़ो from hardware
 * रेजिस्टरs during initialization. They typically contain the best
 * supported or maximum value that can be configured in the
 * corresponding dwc2_core_params value.
 *
 * The values that are not in dwc2_core_params are करोcumented below.
 *
 * @op_mode:             Mode of Operation
 *                       0 - HNP- and SRP-Capable OTG (Host & Device)
 *                       1 - SRP-Capable OTG (Host & Device)
 *                       2 - Non-HNP and Non-SRP Capable OTG (Host & Device)
 *                       3 - SRP-Capable Device
 *                       4 - Non-OTG Device
 *                       5 - SRP-Capable Host
 *                       6 - Non-OTG Host
 * @arch:                Architecture
 *                       0 - Slave only
 *                       1 - External DMA
 *                       2 - Internal DMA
 * @ipg_isoc_en:        This feature indicates that the controller supports
 *                      the worst-हाल scenario of Rx followed by Rx
 *                      Interpacket Gap (IPG) (32 bitTimes) as per the uपंचांगi
 *                      specअगरication क्रम any token following ISOC OUT token.
 *                       0 - Don't support
 *                       1 - Support
 * @घातer_optimized:    Are घातer optimizations enabled?
 * @num_dev_ep:         Number of device endpoपूर्णांकs available
 * @num_dev_in_eps:     Number of device IN endpoपूर्णांकs available
 * @num_dev_perio_in_ep: Number of device periodic IN endpoपूर्णांकs
 *                       available
 * @dev_token_q_depth:  Device Mode IN Token Sequence Learning Queue
 *                      Depth
 *                       0 to 30
 * @host_perio_tx_q_depth:
 *                      Host Mode Periodic Request Queue Depth
 *                       2, 4 or 8
 * @nperio_tx_q_depth:
 *                      Non-Periodic Request Queue Depth
 *                       2, 4 or 8
 * @hs_phy_type:         High-speed PHY पूर्णांकerface type
 *                       0 - High-speed पूर्णांकerface not supported
 *                       1 - UTMI+
 *                       2 - ULPI
 *                       3 - UTMI+ and ULPI
 * @fs_phy_type:         Full-speed PHY पूर्णांकerface type
 *                       0 - Full speed पूर्णांकerface not supported
 *                       1 - Dedicated full speed पूर्णांकerface
 *                       2 - FS pins shared with UTMI+ pins
 *                       3 - FS pins shared with ULPI pins
 * @total_fअगरo_size:    Total पूर्णांकernal RAM क्रम FIFOs (bytes)
 * @hibernation:	Is hibernation enabled?
 * @uपंचांगi_phy_data_width: UTMI+ PHY data width
 *                       0 - 8 bits
 *                       1 - 16 bits
 *                       2 - 8 or 16 bits
 * @snpsid:             Value from SNPSID रेजिस्टर
 * @dev_ep_dirs:        Direction of device endpoपूर्णांकs (GHWCFG1)
 * @g_tx_fअगरo_size:	Power-on values of TxFIFO sizes
 * @dma_desc_enable:    When DMA mode is enabled, specअगरies whether to use
 *                      address DMA mode or descriptor DMA mode क्रम accessing
 *                      the data FIFOs. The driver will स्वतःmatically detect the
 *                      value क्रम this अगर none is specअगरied.
 *                       0 - Address DMA
 *                       1 - Descriptor DMA (शेष, अगर available)
 * @enable_dynamic_fअगरo: 0 - Use coreConsultant-specअगरied FIFO size parameters
 *                       1 - Allow dynamic FIFO sizing (शेष, अगर available)
 * @en_multiple_tx_fअगरo: Specअगरies whether dedicated per-endpoपूर्णांक transmit FIFOs
 *                      are enabled क्रम non-periodic IN endpoपूर्णांकs in device
 *                      mode.
 * @host_nperio_tx_fअगरo_size: Number of 4-byte words in the non-periodic Tx FIFO
 *                      in host mode when dynamic FIFO sizing is enabled
 *                       16 to 32768
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @host_perio_tx_fअगरo_size: Number of 4-byte words in the periodic Tx FIFO in
 *                      host mode when dynamic FIFO sizing is enabled
 *                       16 to 32768
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @max_transfer_size:  The maximum transfer size supported, in bytes
 *                       2047 to 65,535
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @max_packet_count:   The maximum number of packets in a transfer
 *                       15 to 511
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @host_channels:      The number of host channel रेजिस्टरs to use
 *                       1 to 16
 *                      Actual maximum value is स्वतःdetected and also
 *                      the शेष.
 * @dev_nperio_tx_fअगरo_size: Number of 4-byte words in the non-periodic Tx FIFO
 *			     in device mode when dynamic FIFO sizing is enabled
 *			     16 to 32768
 *			     Actual maximum value is स्वतःdetected and also
 *			     the शेष.
 * @i2c_enable:         Specअगरies whether to use the I2Cपूर्णांकerface क्रम a full
 *                      speed PHY. This parameter is only applicable अगर phy_type
 *                      is FS.
 *                       0 - No (शेष)
 *                       1 - Yes
 * @acg_enable:		For enabling Active Clock Gating in the controller
 *                       0 - Disable
 *                       1 - Enable
 * @lpm_mode:		For enabling Link Power Management in the controller
 *                       0 - Disable
 *                       1 - Enable
 * @rx_fअगरo_size:	Number of 4-byte words in the  Rx FIFO when dynamic
 *			FIFO sizing is enabled 16 to 32768
 *			Actual maximum value is स्वतःdetected and also
 *			the शेष.
 * @service_पूर्णांकerval_mode: For enabling service पूर्णांकerval based scheduling in the
 *                         controller.
 *                           0 - Disable
 *                           1 - Enable
 */
काष्ठा dwc2_hw_params अणु
	अचिन्हित op_mode:3;
	अचिन्हित arch:2;
	अचिन्हित dma_desc_enable:1;
	अचिन्हित enable_dynamic_fअगरo:1;
	अचिन्हित en_multiple_tx_fअगरo:1;
	अचिन्हित rx_fअगरo_size:16;
	अचिन्हित host_nperio_tx_fअगरo_size:16;
	अचिन्हित dev_nperio_tx_fअगरo_size:16;
	अचिन्हित host_perio_tx_fअगरo_size:16;
	अचिन्हित nperio_tx_q_depth:3;
	अचिन्हित host_perio_tx_q_depth:3;
	अचिन्हित dev_token_q_depth:5;
	अचिन्हित max_transfer_size:26;
	अचिन्हित max_packet_count:11;
	अचिन्हित host_channels:5;
	अचिन्हित hs_phy_type:2;
	अचिन्हित fs_phy_type:2;
	अचिन्हित i2c_enable:1;
	अचिन्हित acg_enable:1;
	अचिन्हित num_dev_ep:4;
	अचिन्हित num_dev_in_eps : 4;
	अचिन्हित num_dev_perio_in_ep:4;
	अचिन्हित total_fअगरo_size:16;
	अचिन्हित घातer_optimized:1;
	अचिन्हित hibernation:1;
	अचिन्हित uपंचांगi_phy_data_width:2;
	अचिन्हित lpm_mode:1;
	अचिन्हित ipg_isoc_en:1;
	अचिन्हित service_पूर्णांकerval_mode:1;
	u32 snpsid;
	u32 dev_ep_dirs;
	u32 g_tx_fअगरo_size[MAX_EPS_CHANNELS];
पूर्ण;

/* Size of control and EP0 buffers */
#घोषणा DWC2_CTRL_BUFF_SIZE 8

/**
 * काष्ठा dwc2_gregs_backup - Holds global रेजिस्टरs state beक्रमe
 * entering partial घातer करोwn
 * @gotgctl:		Backup of GOTGCTL रेजिस्टर
 * @gपूर्णांकmsk:		Backup of GINTMSK रेजिस्टर
 * @gahbcfg:		Backup of GAHBCFG रेजिस्टर
 * @gusbcfg:		Backup of GUSBCFG रेजिस्टर
 * @grxfsiz:		Backup of GRXFSIZ रेजिस्टर
 * @gnptxfsiz:		Backup of GNPTXFSIZ रेजिस्टर
 * @gi2cctl:		Backup of GI2CCTL रेजिस्टर
 * @glpmcfg:		Backup of GLPMCFG रेजिस्टर
 * @gdfअगरocfg:		Backup of GDFIFOCFG रेजिस्टर
 * @pcgcctl:		Backup of PCGCCTL रेजिस्टर
 * @pcgcctl1:		Backup of PCGCCTL1 रेजिस्टर
 * @dtxfsiz:		Backup of DTXFSIZ रेजिस्टरs क्रम each endpoपूर्णांक
 * @gpwrdn:		Backup of GPWRDN रेजिस्टर
 * @valid:		True अगर रेजिस्टरs values backuped.
 */
काष्ठा dwc2_gregs_backup अणु
	u32 gotgctl;
	u32 gपूर्णांकmsk;
	u32 gahbcfg;
	u32 gusbcfg;
	u32 grxfsiz;
	u32 gnptxfsiz;
	u32 gi2cctl;
	u32 glpmcfg;
	u32 pcgcctl;
	u32 pcgcctl1;
	u32 gdfअगरocfg;
	u32 gpwrdn;
	bool valid;
पूर्ण;

/**
 * काष्ठा dwc2_dregs_backup - Holds device रेजिस्टरs state beक्रमe
 * entering partial घातer करोwn
 * @dcfg:		Backup of DCFG रेजिस्टर
 * @dctl:		Backup of DCTL रेजिस्टर
 * @daपूर्णांकmsk:		Backup of DAINTMSK रेजिस्टर
 * @diepmsk:		Backup of DIEPMSK रेजिस्टर
 * @करोepmsk:		Backup of DOEPMSK रेजिस्टर
 * @diepctl:		Backup of DIEPCTL रेजिस्टर
 * @dieptsiz:		Backup of DIEPTSIZ रेजिस्टर
 * @diepdma:		Backup of DIEPDMA रेजिस्टर
 * @करोepctl:		Backup of DOEPCTL रेजिस्टर
 * @करोeptsiz:		Backup of DOEPTSIZ रेजिस्टर
 * @करोepdma:		Backup of DOEPDMA रेजिस्टर
 * @dtxfsiz:		Backup of DTXFSIZ रेजिस्टरs क्रम each endpoपूर्णांक
 * @valid:      True अगर रेजिस्टरs values backuped.
 */
काष्ठा dwc2_dregs_backup अणु
	u32 dcfg;
	u32 dctl;
	u32 daपूर्णांकmsk;
	u32 diepmsk;
	u32 करोepmsk;
	u32 diepctl[MAX_EPS_CHANNELS];
	u32 dieptsiz[MAX_EPS_CHANNELS];
	u32 diepdma[MAX_EPS_CHANNELS];
	u32 करोepctl[MAX_EPS_CHANNELS];
	u32 करोeptsiz[MAX_EPS_CHANNELS];
	u32 करोepdma[MAX_EPS_CHANNELS];
	u32 dtxfsiz[MAX_EPS_CHANNELS];
	bool valid;
पूर्ण;

/**
 * काष्ठा dwc2_hregs_backup - Holds host रेजिस्टरs state beक्रमe
 * entering partial घातer करोwn
 * @hcfg:		Backup of HCFG रेजिस्टर
 * @haपूर्णांकmsk:		Backup of HAINTMSK रेजिस्टर
 * @hcपूर्णांकmsk:		Backup of HCINTMSK रेजिस्टर
 * @hprt0:		Backup of HPTR0 रेजिस्टर
 * @hfir:		Backup of HFIR रेजिस्टर
 * @hptxfsiz:		Backup of HPTXFSIZ रेजिस्टर
 * @valid:      True अगर रेजिस्टरs values backuped.
 */
काष्ठा dwc2_hregs_backup अणु
	u32 hcfg;
	u32 haपूर्णांकmsk;
	u32 hcपूर्णांकmsk[MAX_EPS_CHANNELS];
	u32 hprt0;
	u32 hfir;
	u32 hptxfsiz;
	bool valid;
पूर्ण;

/*
 * Constants related to high speed periodic scheduling
 *
 * We have a periodic schedule that is DWC2_HS_SCHEDULE_UFRAMES दीर्घ.  From a
 * reservation poपूर्णांक of view it's assumed that the schedule goes right back to
 * the beginning after the end of the schedule.
 *
 * What करोes that mean क्रम scheduling things with a दीर्घ पूर्णांकerval?  It means
 * we'll reserve समय क्रम them in every possible microframe that they could
 * ever be scheduled in.  ...but we'll still only actually schedule them as
 * often as they were requested.
 *
 * We keep our schedule in a "bitmap" काष्ठाure.  This simplअगरies having
 * to keep track of and merge पूर्णांकervals: we just let the biपंचांगap code करो most
 * of the heavy lअगरting.  In a way scheduling is much like memory allocation.
 *
 * We schedule 100us per uframe or 80% of 125us (the maximum amount you're
 * supposed to schedule क्रम periodic transfers).  That's according to spec.
 *
 * Note that though we only schedule 80% of each microframe, the biपंचांगap that we
 * keep the schedule in is tightly packed (AKA it करोesn't have 100us worth of
 * space क्रम each uFrame).
 *
 * Requirements:
 * - DWC2_HS_SCHEDULE_UFRAMES must even भागide 0x4000 (HFNUM_MAX_FRNUM + 1)
 * - DWC2_HS_SCHEDULE_UFRAMES must be 8 बार DWC2_LS_SCHEDULE_FRAMES (probably
 *   could be any multiple of 8 बार DWC2_LS_SCHEDULE_FRAMES, but there might
 *   be bugs).  The 8 comes from the USB spec: number of microframes per frame.
 */
#घोषणा DWC2_US_PER_UFRAME		125
#घोषणा DWC2_HS_PERIODIC_US_PER_UFRAME	100

#घोषणा DWC2_HS_SCHEDULE_UFRAMES	8
#घोषणा DWC2_HS_SCHEDULE_US		(DWC2_HS_SCHEDULE_UFRAMES * \
					 DWC2_HS_PERIODIC_US_PER_UFRAME)

/*
 * Constants related to low speed scheduling
 *
 * For high speed we schedule every 1us.  For low speed that's a bit overसमाप्त,
 * so we make up a unit called a "slice" that's worth 25us.  There are 40
 * slices in a full frame and we can schedule 36 of those (90%) क्रम periodic
 * transfers.
 *
 * Our low speed schedule can be as लघु as 1 frame or could be दीर्घer.  When
 * we only schedule 1 frame it means that we'll need to reserve a समय every
 * frame even क्रम things that only transfer very rarely, so something that runs
 * every 2048 frames will get समय reserved in every frame.  Our low speed
 * schedule can be दीर्घer and we'll be able to handle more overlap, but that
 * will come at increased memory cost and increased समय to schedule.
 *
 * Note: one other advantage of a लघु low speed schedule is that अगर we mess
 * up and miss scheduling we can jump in and use any of the slots that we
 * happened to reserve.
 *
 * With 25 us per slice and 1 frame in the schedule, we only need 4 bytes क्रम
 * the schedule.  There will be one schedule per TT.
 *
 * Requirements:
 * - DWC2_US_PER_SLICE must evenly भागide DWC2_LS_PERIODIC_US_PER_FRAME.
 */
#घोषणा DWC2_US_PER_SLICE	25
#घोषणा DWC2_SLICES_PER_UFRAME	(DWC2_US_PER_UFRAME / DWC2_US_PER_SLICE)

#घोषणा DWC2_ROUND_US_TO_SLICE(us) \
				(DIV_ROUND_UP((us), DWC2_US_PER_SLICE) * \
				 DWC2_US_PER_SLICE)

#घोषणा DWC2_LS_PERIODIC_US_PER_FRAME \
				900
#घोषणा DWC2_LS_PERIODIC_SLICES_PER_FRAME \
				(DWC2_LS_PERIODIC_US_PER_FRAME / \
				 DWC2_US_PER_SLICE)

#घोषणा DWC2_LS_SCHEDULE_FRAMES	1
#घोषणा DWC2_LS_SCHEDULE_SLICES	(DWC2_LS_SCHEDULE_FRAMES * \
				 DWC2_LS_PERIODIC_SLICES_PER_FRAME)

/**
 * काष्ठा dwc2_hsotg - Holds the state of the driver, including the non-periodic
 * and periodic schedules
 *
 * These are common क्रम both host and peripheral modes:
 *
 * @dev:                The काष्ठा device poपूर्णांकer
 * @regs:		Poपूर्णांकer to controller regs
 * @hw_params:          Parameters that were स्वतःdetected from the
 *                      hardware रेजिस्टरs
 * @params:	Parameters that define how the core should be configured
 * @op_state:           The operational State, during transitions (a_host=>
 *                      a_peripheral and b_device=>b_host) this may not match
 *                      the core, but allows the software to determine
 *                      transitions
 * @dr_mode:            Requested mode of operation, one of following:
 *                      - USB_DR_MODE_PERIPHERAL
 *                      - USB_DR_MODE_HOST
 *                      - USB_DR_MODE_OTG
 * @role_sw:		usb_role_चयन handle
 * @hcd_enabled:	Host mode sub-driver initialization indicator.
 * @gadget_enabled:	Peripheral mode sub-driver initialization indicator.
 * @ll_hw_enabled:	Status of low-level hardware resources.
 * @hibernated:		True अगर core is hibernated
 * @in_ppd:		True अगर core is partial घातer करोwn mode.
 * @bus_suspended:	True अगर bus is suspended
 * @reset_phy_on_wake:	Quirk saying that we should निश्चित PHY reset on a
 *			remote wakeup.
 * @phy_off_क्रम_suspend: Status of whether we turned the PHY off at suspend.
 * @need_phy_क्रम_wake:	Quirk saying that we should keep the PHY on at
 *			suspend अगर we need USB to wake us up.
 * @frame_number:       Frame number पढ़ो from the core. For both device
 *			and host modes. The value ranges are from 0
 *			to HFNUM_MAX_FRNUM.
 * @phy:                The otg phy transceiver काष्ठाure क्रम phy control.
 * @uphy:               The otg phy transceiver काष्ठाure क्रम old USB phy
 *                      control.
 * @plat:               The platक्रमm specअगरic configuration data. This can be
 *                      हटाओd once all SoCs support usb transceiver.
 * @supplies:           Definition of USB घातer supplies
 * @vbus_supply:        Regulator supplying vbus.
 * @usb33d:		Optional 3.3v regulator used on some sपंचांग32 devices to
 *			supply ID and VBUS detection hardware.
 * @lock:		Spinlock that protects all the driver data काष्ठाures
 * @priv:		Stores a poपूर्णांकer to the काष्ठा usb_hcd
 * @queuing_high_bandwidth: True अगर multiple packets of a high-bandwidth
 *                      transfer are in process of being queued
 * @srp_success:        Stores status of SRP request in the हाल of a FS PHY
 *                      with an I2C पूर्णांकerface
 * @wq_otg:             Workqueue object used क्रम handling of some पूर्णांकerrupts
 * @wf_otg:             Work object क्रम handling Connector ID Status Change
 *                      पूर्णांकerrupt
 * @wkp_समयr:          Timer object क्रम handling Wakeup Detected पूर्णांकerrupt
 * @lx_state:           Lx state of connected device
 * @gr_backup: Backup of global रेजिस्टरs during suspend
 * @dr_backup: Backup of device रेजिस्टरs during suspend
 * @hr_backup: Backup of host रेजिस्टरs during suspend
 * @needs_byte_swap:		Specअगरies whether the opposite endianness.
 *
 * These are क्रम host mode:
 *
 * @flags:              Flags क्रम handling root port state changes
 * @flags.d32:          Contain all root port flags
 * @flags.b:            Separate root port flags from each other
 * @flags.b.port_connect_status_change: True अगर root port connect status
 *                      changed
 * @flags.b.port_connect_status: True अगर device connected to root port
 * @flags.b.port_reset_change: True अगर root port reset status changed
 * @flags.b.port_enable_change: True अगर root port enable status changed
 * @flags.b.port_suspend_change: True अगर root port suspend status changed
 * @flags.b.port_over_current_change: True अगर root port over current state
 *                       changed.
 * @flags.b.port_l1_change: True अगर root port l1 status changed
 * @flags.b.reserved:   Reserved bits of root port रेजिस्टर
 * @non_periodic_sched_inactive: Inactive QHs in the non-periodic schedule.
 *                      Transfers associated with these QHs are not currently
 *                      asचिन्हित to a host channel.
 * @non_periodic_sched_active: Active QHs in the non-periodic schedule.
 *                      Transfers associated with these QHs are currently
 *                      asचिन्हित to a host channel.
 * @non_periodic_qh_ptr: Poपूर्णांकer to next QH to process in the active
 *                      non-periodic schedule
 * @non_periodic_sched_रुकोing: Waiting QHs in the non-periodic schedule.
 *                      Transfers associated with these QHs are not currently
 *                      asचिन्हित to a host channel.
 * @periodic_sched_inactive: Inactive QHs in the periodic schedule. This is a
 *                      list of QHs क्रम periodic transfers that are _not_
 *                      scheduled क्रम the next frame. Each QH in the list has an
 *                      पूर्णांकerval counter that determines when it needs to be
 *                      scheduled क्रम execution. This scheduling mechanism
 *                      allows only a simple calculation क्रम periodic bandwidth
 *                      used (i.e. must assume that all periodic transfers may
 *                      need to execute in the same frame). However, it greatly
 *                      simplअगरies scheduling and should be sufficient क्रम the
 *                      vast majority of OTG hosts, which need to connect to a
 *                      small number of peripherals at one समय. Items move from
 *                      this list to periodic_sched_पढ़ोy when the QH पूर्णांकerval
 *                      counter is 0 at SOF.
 * @periodic_sched_पढ़ोy:  List of periodic QHs that are पढ़ोy क्रम execution in
 *                      the next frame, but have not yet been asचिन्हित to host
 *                      channels. Items move from this list to
 *                      periodic_sched_asचिन्हित as host channels become
 *                      available during the current frame.
 * @periodic_sched_asचिन्हित: List of periodic QHs to be executed in the next
 *                      frame that are asचिन्हित to host channels. Items move
 *                      from this list to periodic_sched_queued as the
 *                      transactions क्रम the QH are queued to the DWC_otg
 *                      controller.
 * @periodic_sched_queued: List of periodic QHs that have been queued क्रम
 *                      execution. Items move from this list to either
 *                      periodic_sched_inactive or periodic_sched_पढ़ोy when the
 *                      channel associated with the transfer is released. If the
 *                      पूर्णांकerval क्रम the QH is 1, the item moves to
 *                      periodic_sched_पढ़ोy because it must be rescheduled क्रम
 *                      the next frame. Otherwise, the item moves to
 *                      periodic_sched_inactive.
 * @split_order:        List keeping track of channels करोing splits, in order.
 * @periodic_usecs:     Total bandwidth claimed so far क्रम periodic transfers.
 *                      This value is in microseconds per (micro)frame. The
 *                      assumption is that all periodic transfers may occur in
 *                      the same (micro)frame.
 * @hs_periodic_biपंचांगap: Biपंचांगap used by the microframe scheduler any समय the
 *                      host is in high speed mode; low speed schedules are
 *                      stored अन्यथाwhere since we need one per TT.
 * @periodic_qh_count:  Count of periodic QHs, अगर using several eps. Used क्रम
 *                      SOF enable/disable.
 * @मुक्त_hc_list:       Free host channels in the controller. This is a list of
 *                      काष्ठा dwc2_host_chan items.
 * @periodic_channels:  Number of host channels asचिन्हित to periodic transfers.
 *                      Currently assuming that there is a dedicated host
 *                      channel क्रम each periodic transaction and at least one
 *                      host channel is available क्रम non-periodic transactions.
 * @non_periodic_channels: Number of host channels asचिन्हित to non-periodic
 *                      transfers
 * @available_host_channels: Number of host channels available क्रम the
 *			     microframe scheduler to use
 * @hc_ptr_array:       Array of poपूर्णांकers to the host channel descriptors.
 *                      Allows accessing a host channel descriptor given the
 *                      host channel number. This is useful in पूर्णांकerrupt
 *                      handlers.
 * @status_buf:         Buffer used क्रम data received during the status phase of
 *                      a control transfer.
 * @status_buf_dma:     DMA address क्रम status_buf
 * @start_work:         Delayed work क्रम handling host A-cable connection
 * @reset_work:         Delayed work क्रम handling a port reset
 * @phy_reset_work:     Work काष्ठाure क्रम करोing a PHY reset
 * @otg_port:           OTG port number
 * @frame_list:         Frame list
 * @frame_list_dma:     Frame list DMA address
 * @frame_list_sz:      Frame list size
 * @desc_gen_cache:     Kmem cache क्रम generic descriptors
 * @desc_hsisoc_cache:  Kmem cache क्रम hs isochronous descriptors
 * @unaligned_cache:    Kmem cache क्रम DMA mode to handle non-aligned buf
 *
 * These are क्रम peripheral mode:
 *
 * @driver:             USB gadget driver
 * @dedicated_fअगरos:    Set अगर the hardware has dedicated IN-EP fअगरos.
 * @num_of_eps:         Number of available EPs (excluding EP0)
 * @debug_root:         Root directrory क्रम debugfs.
 * @ep0_reply:          Request used क्रम ep0 reply.
 * @ep0_buff:           Buffer क्रम EP0 reply data, अगर needed.
 * @ctrl_buff:          Buffer क्रम EP0 control requests.
 * @ctrl_req:           Request क्रम EP0 control packets.
 * @ep0_state:          EP0 control transfers state
 * @delayed_status:		true when gadget driver asks क्रम delayed status
 * @test_mode:          USB test mode requested by the host
 * @remote_wakeup_allowed: True अगर device is allowed to wake-up host by
 *                      remote-wakeup संकेतling
 * @setup_desc_dma:	EP0 setup stage desc chain DMA address
 * @setup_desc:		EP0 setup stage desc chain poपूर्णांकer
 * @ctrl_in_desc_dma:	EP0 IN data phase desc chain DMA address
 * @ctrl_in_desc:	EP0 IN data phase desc chain poपूर्णांकer
 * @ctrl_out_desc_dma:	EP0 OUT data phase desc chain DMA address
 * @ctrl_out_desc:	EP0 OUT data phase desc chain poपूर्णांकer
 * @irq:		Interrupt request line number
 * @clk:		Poपूर्णांकer to otg घड़ी
 * @reset:		Poपूर्णांकer to dwc2 reset controller
 * @reset_ecc:          Poपूर्णांकer to dwc2 optional reset controller in Stratix10.
 * @regset:		A poपूर्णांकer to a काष्ठा debugfs_regset32, which contains
 *			a poपूर्णांकer to an array of रेजिस्टर definitions, the
 *			array size and the base address where the रेजिस्टर bank
 *			is to be found.
 * @last_frame_num:	Number of last frame. Range from 0 to  32768
 * @frame_num_array:    Used only  अगर CONFIG_USB_DWC2_TRACK_MISSED_SOFS is
 *			defined, क्रम missed SOFs tracking. Array holds that
 *			frame numbers, which not equal to last_frame_num +1
 * @last_frame_num_array:   Used only  अगर CONFIG_USB_DWC2_TRACK_MISSED_SOFS is
 *			    defined, क्रम missed SOFs tracking.
 *			    If current_frame_number != last_frame_num+1
 *			    then last_frame_num added to this array
 * @frame_num_idx:	Actual size of frame_num_array and last_frame_num_array
 * @dumped_frame_num_array:	1 - अगर missed SOFs frame numbers dumbed
 *				0 - अगर missed SOFs frame numbers not dumbed
 * @fअगरo_mem:			Total पूर्णांकernal RAM क्रम FIFOs (bytes)
 * @fअगरo_map:		Each bit पूर्णांकend क्रम concrete fअगरo. If that bit is set,
 *			then that fअगरo is used
 * @gadget:		Represents a usb gadget device
 * @connected:		Used in slave mode. True अगर device connected with host
 * @eps_in:		The IN endpoपूर्णांकs being supplied to the gadget framework
 * @eps_out:		The OUT endpoपूर्णांकs being supplied to the gadget framework
 * @new_connection:	Used in host mode. True अगर there are new connected
 *			device
 * @enabled:		Indicates the enabling state of controller
 *
 */
काष्ठा dwc2_hsotg अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	/** Params detected from hardware */
	काष्ठा dwc2_hw_params hw_params;
	/** Params to actually use */
	काष्ठा dwc2_core_params params;
	क्रमागत usb_otg_state op_state;
	क्रमागत usb_dr_mode dr_mode;
	काष्ठा usb_role_चयन *role_sw;
	अचिन्हित पूर्णांक hcd_enabled:1;
	अचिन्हित पूर्णांक gadget_enabled:1;
	अचिन्हित पूर्णांक ll_hw_enabled:1;
	अचिन्हित पूर्णांक hibernated:1;
	अचिन्हित पूर्णांक in_ppd:1;
	bool bus_suspended;
	अचिन्हित पूर्णांक reset_phy_on_wake:1;
	अचिन्हित पूर्णांक need_phy_क्रम_wake:1;
	अचिन्हित पूर्णांक phy_off_क्रम_suspend:1;
	u16 frame_number;

	काष्ठा phy *phy;
	काष्ठा usb_phy *uphy;
	काष्ठा dwc2_hsotg_plat *plat;
	काष्ठा regulator_bulk_data supplies[DWC2_NUM_SUPPLIES];
	काष्ठा regulator *vbus_supply;
	काष्ठा regulator *usb33d;

	spinlock_t lock;
	व्योम *priv;
	पूर्णांक     irq;
	काष्ठा clk *clk;
	काष्ठा reset_control *reset;
	काष्ठा reset_control *reset_ecc;

	अचिन्हित पूर्णांक queuing_high_bandwidth:1;
	अचिन्हित पूर्णांक srp_success:1;

	काष्ठा workqueue_काष्ठा *wq_otg;
	काष्ठा work_काष्ठा wf_otg;
	काष्ठा समयr_list wkp_समयr;
	क्रमागत dwc2_lx_state lx_state;
	काष्ठा dwc2_gregs_backup gr_backup;
	काष्ठा dwc2_dregs_backup dr_backup;
	काष्ठा dwc2_hregs_backup hr_backup;

	काष्ठा dentry *debug_root;
	काष्ठा debugfs_regset32 *regset;
	bool needs_byte_swap;

	/* DWC OTG HW Release versions */
#घोषणा DWC2_CORE_REV_2_71a	0x4f54271a
#घोषणा DWC2_CORE_REV_2_72a     0x4f54272a
#घोषणा DWC2_CORE_REV_2_80a	0x4f54280a
#घोषणा DWC2_CORE_REV_2_90a	0x4f54290a
#घोषणा DWC2_CORE_REV_2_91a	0x4f54291a
#घोषणा DWC2_CORE_REV_2_92a	0x4f54292a
#घोषणा DWC2_CORE_REV_2_94a	0x4f54294a
#घोषणा DWC2_CORE_REV_3_00a	0x4f54300a
#घोषणा DWC2_CORE_REV_3_10a	0x4f54310a
#घोषणा DWC2_CORE_REV_4_00a	0x4f54400a
#घोषणा DWC2_CORE_REV_4_20a	0x4f54420a
#घोषणा DWC2_FS_IOT_REV_1_00a	0x5531100a
#घोषणा DWC2_HS_IOT_REV_1_00a	0x5532100a
#घोषणा DWC2_CORE_REV_MASK	0x0000ffff

	/* DWC OTG HW Core ID */
#घोषणा DWC2_OTG_ID		0x4f540000
#घोषणा DWC2_FS_IOT_ID		0x55310000
#घोषणा DWC2_HS_IOT_ID		0x55320000

#अगर IS_ENABLED(CONFIG_USB_DWC2_HOST) || IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
	जोड़ dwc2_hcd_पूर्णांकernal_flags अणु
		u32 d32;
		काष्ठा अणु
			अचिन्हित port_connect_status_change:1;
			अचिन्हित port_connect_status:1;
			अचिन्हित port_reset_change:1;
			अचिन्हित port_enable_change:1;
			अचिन्हित port_suspend_change:1;
			अचिन्हित port_over_current_change:1;
			अचिन्हित port_l1_change:1;
			अचिन्हित reserved:25;
		पूर्ण b;
	पूर्ण flags;

	काष्ठा list_head non_periodic_sched_inactive;
	काष्ठा list_head non_periodic_sched_रुकोing;
	काष्ठा list_head non_periodic_sched_active;
	काष्ठा list_head *non_periodic_qh_ptr;
	काष्ठा list_head periodic_sched_inactive;
	काष्ठा list_head periodic_sched_पढ़ोy;
	काष्ठा list_head periodic_sched_asचिन्हित;
	काष्ठा list_head periodic_sched_queued;
	काष्ठा list_head split_order;
	u16 periodic_usecs;
	अचिन्हित दीर्घ hs_periodic_biपंचांगap[
		DIV_ROUND_UP(DWC2_HS_SCHEDULE_US, BITS_PER_LONG)];
	u16 periodic_qh_count;
	bool new_connection;

	u16 last_frame_num;

#अगर_घोषित CONFIG_USB_DWC2_TRACK_MISSED_SOFS
#घोषणा FRAME_NUM_ARRAY_SIZE 1000
	u16 *frame_num_array;
	u16 *last_frame_num_array;
	पूर्णांक frame_num_idx;
	पूर्णांक dumped_frame_num_array;
#पूर्ण_अगर

	काष्ठा list_head मुक्त_hc_list;
	पूर्णांक periodic_channels;
	पूर्णांक non_periodic_channels;
	पूर्णांक available_host_channels;
	काष्ठा dwc2_host_chan *hc_ptr_array[MAX_EPS_CHANNELS];
	u8 *status_buf;
	dma_addr_t status_buf_dma;
#घोषणा DWC2_HCD_STATUS_BUF_SIZE 64

	काष्ठा delayed_work start_work;
	काष्ठा delayed_work reset_work;
	काष्ठा work_काष्ठा phy_reset_work;
	u8 otg_port;
	u32 *frame_list;
	dma_addr_t frame_list_dma;
	u32 frame_list_sz;
	काष्ठा kmem_cache *desc_gen_cache;
	काष्ठा kmem_cache *desc_hsisoc_cache;
	काष्ठा kmem_cache *unaligned_cache;
#घोषणा DWC2_KMEM_UNALIGNED_BUF_SIZE 1024

#पूर्ण_अगर /* CONFIG_USB_DWC2_HOST || CONFIG_USB_DWC2_DUAL_ROLE */

#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
	/* Gadget काष्ठाures */
	काष्ठा usb_gadget_driver *driver;
	पूर्णांक fअगरo_mem;
	अचिन्हित पूर्णांक dedicated_fअगरos:1;
	अचिन्हित अक्षर num_of_eps;
	u32 fअगरo_map;

	काष्ठा usb_request *ep0_reply;
	काष्ठा usb_request *ctrl_req;
	व्योम *ep0_buff;
	व्योम *ctrl_buff;
	क्रमागत dwc2_ep0_state ep0_state;
	अचिन्हित delayed_status : 1;
	u8 test_mode;

	dma_addr_t setup_desc_dma[2];
	काष्ठा dwc2_dma_desc *setup_desc[2];
	dma_addr_t ctrl_in_desc_dma;
	काष्ठा dwc2_dma_desc *ctrl_in_desc;
	dma_addr_t ctrl_out_desc_dma;
	काष्ठा dwc2_dma_desc *ctrl_out_desc;

	काष्ठा usb_gadget gadget;
	अचिन्हित पूर्णांक enabled:1;
	अचिन्हित पूर्णांक connected:1;
	अचिन्हित पूर्णांक remote_wakeup_allowed:1;
	काष्ठा dwc2_hsotg_ep *eps_in[MAX_EPS_CHANNELS];
	काष्ठा dwc2_hsotg_ep *eps_out[MAX_EPS_CHANNELS];
#पूर्ण_अगर /* CONFIG_USB_DWC2_PERIPHERAL || CONFIG_USB_DWC2_DUAL_ROLE */
पूर्ण;

/* Normal architectures just use पढ़ोl/ग_लिखो */
अटल अंतरभूत u32 dwc2_पढ़ोl(काष्ठा dwc2_hsotg *hsotg, u32 offset)
अणु
	u32 val;

	val = पढ़ोl(hsotg->regs + offset);
	अगर (hsotg->needs_byte_swap)
		वापस swab32(val);
	अन्यथा
		वापस val;
पूर्ण

अटल अंतरभूत व्योम dwc2_ग_लिखोl(काष्ठा dwc2_hsotg *hsotg, u32 value, u32 offset)
अणु
	अगर (hsotg->needs_byte_swap)
		ग_लिखोl(swab32(value), hsotg->regs + offset);
	अन्यथा
		ग_लिखोl(value, hsotg->regs + offset);

#अगर_घोषित DWC2_LOG_WRITES
	pr_info("info:: wrote %08x to %p\n", value, hsotg->regs + offset);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम dwc2_पढ़ोl_rep(काष्ठा dwc2_hsotg *hsotg, u32 offset,
				  व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		u32 *buf = buffer;

		करो अणु
			u32 x = dwc2_पढ़ोl(hsotg, offset);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम dwc2_ग_लिखोl_rep(काष्ठा dwc2_hsotg *hsotg, u32 offset,
				   स्थिर व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u32 *buf = buffer;

		करो अणु
			dwc2_ग_लिखोl(hsotg, *buf++, offset);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

/* Reasons क्रम halting a host channel */
क्रमागत dwc2_halt_status अणु
	DWC2_HC_XFER_NO_HALT_STATUS,
	DWC2_HC_XFER_COMPLETE,
	DWC2_HC_XFER_URB_COMPLETE,
	DWC2_HC_XFER_ACK,
	DWC2_HC_XFER_NAK,
	DWC2_HC_XFER_NYET,
	DWC2_HC_XFER_STALL,
	DWC2_HC_XFER_XACT_ERR,
	DWC2_HC_XFER_FRAME_OVERRUN,
	DWC2_HC_XFER_BABBLE_ERR,
	DWC2_HC_XFER_DATA_TOGGLE_ERR,
	DWC2_HC_XFER_AHB_ERR,
	DWC2_HC_XFER_PERIODIC_INCOMPLETE,
	DWC2_HC_XFER_URB_DEQUEUE,
पूर्ण;

/* Core version inक्रमmation */
अटल अंतरभूत bool dwc2_is_iot(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (hsotg->hw_params.snpsid & 0xfff00000) == 0x55300000;
पूर्ण

अटल अंतरभूत bool dwc2_is_fs_iot(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (hsotg->hw_params.snpsid & 0xffff0000) == 0x55310000;
पूर्ण

अटल अंतरभूत bool dwc2_is_hs_iot(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (hsotg->hw_params.snpsid & 0xffff0000) == 0x55320000;
पूर्ण

/*
 * The following functions support initialization of the core driver component
 * and the DWC_otg controller
 */
पूर्णांक dwc2_core_reset(काष्ठा dwc2_hsotg *hsotg, bool skip_रुको);
पूर्णांक dwc2_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
				 bool restore);
पूर्णांक dwc2_enter_hibernation(काष्ठा dwc2_hsotg *hsotg, पूर्णांक is_host);
पूर्णांक dwc2_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
		पूर्णांक reset, पूर्णांक is_host);
व्योम dwc2_init_fs_ls_pclk_sel(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_phy_init(काष्ठा dwc2_hsotg *hsotg, bool select_phy);

व्योम dwc2_क्रमce_mode(काष्ठा dwc2_hsotg *hsotg, bool host);
व्योम dwc2_क्रमce_dr_mode(काष्ठा dwc2_hsotg *hsotg);

bool dwc2_is_controller_alive(काष्ठा dwc2_hsotg *hsotg);

पूर्णांक dwc2_check_core_version(काष्ठा dwc2_hsotg *hsotg);

/*
 * Common core Functions.
 * The following functions support managing the DWC_otg controller in either
 * device or host mode.
 */
व्योम dwc2_पढ़ो_packet(काष्ठा dwc2_hsotg *hsotg, u8 *dest, u16 bytes);
व्योम dwc2_flush_tx_fअगरo(काष्ठा dwc2_hsotg *hsotg, स्थिर पूर्णांक num);
व्योम dwc2_flush_rx_fअगरo(काष्ठा dwc2_hsotg *hsotg);

व्योम dwc2_enable_global_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hcd);
व्योम dwc2_disable_global_पूर्णांकerrupts(काष्ठा dwc2_hsotg *hcd);

व्योम dwc2_hib_restore_common(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup,
			     पूर्णांक is_host);
पूर्णांक dwc2_backup_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_restore_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);

व्योम dwc2_enable_acg(काष्ठा dwc2_hsotg *hsotg);

/* This function should be called on every hardware पूर्णांकerrupt. */
irqवापस_t dwc2_handle_common_पूर्णांकr(पूर्णांक irq, व्योम *dev);

/* The device ID match table */
बाह्य स्थिर काष्ठा of_device_id dwc2_of_match_table[];
बाह्य स्थिर काष्ठा acpi_device_id dwc2_acpi_match[];

पूर्णांक dwc2_lowlevel_hw_enable(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_lowlevel_hw_disable(काष्ठा dwc2_hsotg *hsotg);

/* Common polling functions */
पूर्णांक dwc2_hsotg_रुको_bit_set(काष्ठा dwc2_hsotg *hs_otg, u32 reg, u32 bit,
			    u32 समयout);
पूर्णांक dwc2_hsotg_रुको_bit_clear(काष्ठा dwc2_hsotg *hs_otg, u32 reg, u32 bit,
			      u32 समयout);
/* Parameters */
पूर्णांक dwc2_get_hwparams(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_init_params(काष्ठा dwc2_hsotg *hsotg);

/*
 * The following functions check the controller's OTG operation mode
 * capability (GHWCFG2.OTG_MODE).
 *
 * These functions can be used beक्रमe the पूर्णांकernal hsotg->hw_params
 * are पढ़ो in and cached so they always पढ़ो directly from the
 * GHWCFG2 रेजिस्टर.
 */
अचिन्हित पूर्णांक dwc2_op_mode(काष्ठा dwc2_hsotg *hsotg);
bool dwc2_hw_is_otg(काष्ठा dwc2_hsotg *hsotg);
bool dwc2_hw_is_host(काष्ठा dwc2_hsotg *hsotg);
bool dwc2_hw_is_device(काष्ठा dwc2_hsotg *hsotg);

/*
 * Returns the mode of operation, host or device
 */
अटल अंतरभूत पूर्णांक dwc2_is_host_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (dwc2_पढ़ोl(hsotg, GINTSTS) & GINTSTS_CURMODE_HOST) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक dwc2_is_device_mode(काष्ठा dwc2_hsotg *hsotg)
अणु
	वापस (dwc2_पढ़ोl(hsotg, GINTSTS) & GINTSTS_CURMODE_HOST) == 0;
पूर्ण

पूर्णांक dwc2_drd_init(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_drd_suspend(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_drd_resume(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_drd_निकास(काष्ठा dwc2_hsotg *hsotg);

/*
 * Dump core रेजिस्टरs and SPRAM
 */
व्योम dwc2_dump_dev_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_dump_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_dump_global_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);

/* Gadget defines */
#अगर IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL) || \
	IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
पूर्णांक dwc2_hsotg_हटाओ(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_hsotg_suspend(काष्ठा dwc2_hsotg *dwc2);
पूर्णांक dwc2_hsotg_resume(काष्ठा dwc2_hsotg *dwc2);
पूर्णांक dwc2_gadget_init(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hsotg_core_init_disconnected(काष्ठा dwc2_hsotg *dwc2,
				       bool reset);
व्योम dwc2_hsotg_core_disconnect(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hsotg_core_connect(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hsotg_disconnect(काष्ठा dwc2_hsotg *dwc2);
पूर्णांक dwc2_hsotg_set_test_mode(काष्ठा dwc2_hsotg *hsotg, पूर्णांक tesपंचांगode);
#घोषणा dwc2_is_device_connected(hsotg) (hsotg->connected)
पूर्णांक dwc2_backup_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_restore_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg, पूर्णांक remote_wakeup);
पूर्णांक dwc2_gadget_enter_hibernation(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_gadget_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg,
				 पूर्णांक rem_wakeup, पूर्णांक reset);
पूर्णांक dwc2_gadget_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_gadget_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
					bool restore);
व्योम dwc2_gadget_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_gadget_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg,
				   पूर्णांक rem_wakeup);
पूर्णांक dwc2_hsotg_tx_fअगरo_count(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_hsotg_tx_fअगरo_total_depth(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_hsotg_tx_fअगरo_average_depth(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_gadget_init_lpm(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_gadget_program_ref_clk(काष्ठा dwc2_hsotg *hsotg);
अटल अंतरभूत व्योम dwc2_clear_fअगरo_map(काष्ठा dwc2_hsotg *hsotg)
अणु hsotg->fअगरo_map = 0; पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dwc2_hsotg_हटाओ(काष्ठा dwc2_hsotg *dwc2)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_suspend(काष्ठा dwc2_hsotg *dwc2)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_resume(काष्ठा dwc2_hsotg *dwc2)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_gadget_init(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc2_hsotg_core_init_disconnected(काष्ठा dwc2_hsotg *dwc2,
						     bool reset) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hsotg_core_disconnect(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hsotg_core_connect(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hsotg_disconnect(काष्ठा dwc2_hsotg *dwc2) अणुपूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_set_test_mode(काष्ठा dwc2_hsotg *hsotg,
					   पूर्णांक tesपंचांगode)
अणु वापस 0; पूर्ण
#घोषणा dwc2_is_device_connected(hsotg) (0)
अटल अंतरभूत पूर्णांक dwc2_backup_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_restore_device_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg,
						पूर्णांक remote_wakeup)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_gadget_enter_hibernation(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_gadget_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg,
					       पूर्णांक rem_wakeup, पूर्णांक reset)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_gadget_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_gadget_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
						      bool restore)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc2_gadget_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_gadget_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg,
						 पूर्णांक rem_wakeup) अणुपूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_tx_fअगरo_count(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_tx_fअगरo_total_depth(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hsotg_tx_fअगरo_average_depth(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc2_gadget_init_lpm(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_gadget_program_ref_clk(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_clear_fअगरo_map(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_DWC2_HOST) || IS_ENABLED(CONFIG_USB_DWC2_DUAL_ROLE)
पूर्णांक dwc2_hcd_get_frame_number(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_hcd_get_future_frame_number(काष्ठा dwc2_hsotg *hsotg, पूर्णांक us);
व्योम dwc2_hcd_connect(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_hcd_disconnect(काष्ठा dwc2_hsotg *hsotg, bool क्रमce);
व्योम dwc2_hcd_start(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_core_init(काष्ठा dwc2_hsotg *hsotg, bool initial_setup);
पूर्णांक dwc2_port_suspend(काष्ठा dwc2_hsotg *hsotg, u16 windex);
पूर्णांक dwc2_port_resume(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_backup_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_restore_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_host_enter_hibernation(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_host_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg,
			       पूर्णांक rem_wakeup, पूर्णांक reset);
पूर्णांक dwc2_host_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg);
पूर्णांक dwc2_host_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
				      पूर्णांक rem_wakeup, bool restore);
व्योम dwc2_host_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg);
व्योम dwc2_host_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg, पूर्णांक rem_wakeup);
bool dwc2_host_can_घातeroff_phy(काष्ठा dwc2_hsotg *dwc2);
अटल अंतरभूत व्योम dwc2_host_schedule_phy_reset(काष्ठा dwc2_hsotg *hsotg)
अणु schedule_work(&hsotg->phy_reset_work); पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dwc2_hcd_get_frame_number(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hcd_get_future_frame_number(काष्ठा dwc2_hsotg *hsotg,
						   पूर्णांक us)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc2_hcd_connect(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hcd_disconnect(काष्ठा dwc2_hsotg *hsotg, bool क्रमce) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hcd_start(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_hcd_हटाओ(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत पूर्णांक dwc2_core_init(काष्ठा dwc2_hsotg *hsotg, bool initial_setup)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_port_suspend(काष्ठा dwc2_hsotg *hsotg, u16 windex)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_port_resume(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_hcd_init(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_backup_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_restore_host_रेजिस्टरs(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_host_enter_hibernation(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_host_निकास_hibernation(काष्ठा dwc2_hsotg *hsotg,
					     पूर्णांक rem_wakeup, पूर्णांक reset)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_host_enter_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक dwc2_host_निकास_partial_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg,
						    पूर्णांक rem_wakeup, bool restore)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम dwc2_host_enter_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण
अटल अंतरभूत व्योम dwc2_host_निकास_घड़ी_gating(काष्ठा dwc2_hsotg *hsotg,
					       पूर्णांक rem_wakeup) अणुपूर्ण
अटल अंतरभूत bool dwc2_host_can_घातeroff_phy(काष्ठा dwc2_hsotg *dwc2)
अणु वापस false; पूर्ण
अटल अंतरभूत व्योम dwc2_host_schedule_phy_reset(काष्ठा dwc2_hsotg *hsotg) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __DWC2_CORE_H__ */
