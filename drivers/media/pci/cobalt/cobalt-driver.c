<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cobalt driver initialization and card probing
 *
 *  Derived from cx18-driver.c
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <media/i2c/adv7604.h>
#समावेश <media/i2c/adv7842.h>
#समावेश <media/i2c/adv7511.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "cobalt-driver.h"
#समावेश "cobalt-irq.h"
#समावेश "cobalt-i2c.h"
#समावेश "cobalt-v4l2.h"
#समावेश "cobalt-flash.h"
#समावेश "cobalt-alsa.h"
#समावेश "cobalt-omnitek.h"

/* add your revision and whatnot here */
अटल स्थिर काष्ठा pci_device_id cobalt_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_CISCO, PCI_DEVICE_ID_COBALT,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cobalt_pci_tbl);

अटल atomic_t cobalt_instance = ATOMIC_INIT(0);

पूर्णांक cobalt_debug;
module_param_named(debug, cobalt_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level. Default: 0\n");

पूर्णांक cobalt_ignore_err;
module_param_named(ignore_err, cobalt_ignore_err, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_err,
	"If set then ignore missing i2c adapters/receivers. Default: 0\n");

MODULE_AUTHOR("Hans Verkuil <hans.verkuil@cisco.com> & Morten Hestnes");
MODULE_DESCRIPTION("cobalt driver");
MODULE_LICENSE("GPL");

अटल u8 edid[256] = अणु
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x50, 0x21, 0x32, 0x27, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x1a, 0x01, 0x03, 0x80, 0x30, 0x1b, 0x78,
	0x0f, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26,
	0x0f, 0x50, 0x54, 0x2f, 0xcf, 0x00, 0x31, 0x59,
	0x45, 0x59, 0x61, 0x59, 0x81, 0x99, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3a,
	0x80, 0x18, 0x71, 0x38, 0x2d, 0x40, 0x58, 0x2c,
	0x45, 0x00, 0xe0, 0x0e, 0x11, 0x00, 0x00, 0x1e,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x55, 0x18,
	0x5e, 0x11, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x63,
	0x6f, 0x62, 0x61, 0x6c, 0x74, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9d,

	0x02, 0x03, 0x1f, 0xf1, 0x4a, 0x10, 0x1f, 0x04,
	0x13, 0x22, 0x21, 0x20, 0x02, 0x11, 0x01, 0x23,
	0x09, 0x07, 0x07, 0x68, 0x03, 0x0c, 0x00, 0x10,
	0x00, 0x00, 0x22, 0x0f, 0xe2, 0x00, 0xca, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46,
पूर्ण;

अटल व्योम cobalt_set_पूर्णांकerrupt(काष्ठा cobalt *cobalt, bool enable)
अणु
	अगर (enable) अणु
		अचिन्हित irqs = COBALT_SYSSTAT_VI0_INT1_MSK |
				COBALT_SYSSTAT_VI1_INT1_MSK |
				COBALT_SYSSTAT_VI2_INT1_MSK |
				COBALT_SYSSTAT_VI3_INT1_MSK |
				COBALT_SYSSTAT_VI0_INT2_MSK |
				COBALT_SYSSTAT_VI1_INT2_MSK |
				COBALT_SYSSTAT_VI2_INT2_MSK |
				COBALT_SYSSTAT_VI3_INT2_MSK |
				COBALT_SYSSTAT_VI0_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI1_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI2_LOST_DATA_MSK |
				COBALT_SYSSTAT_VI3_LOST_DATA_MSK |
				COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK;

		अगर (cobalt->have_hsma_rx)
			irqs |= COBALT_SYSSTAT_VIHSMA_INT1_MSK |
				COBALT_SYSSTAT_VIHSMA_INT2_MSK |
				COBALT_SYSSTAT_VIHSMA_LOST_DATA_MSK;

		अगर (cobalt->have_hsma_tx)
			irqs |= COBALT_SYSSTAT_VOHSMA_INT1_MSK |
				COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK |
				COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK;
		/* Clear any existing पूर्णांकerrupts */
		cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_EDGE, 0xffffffff);
		/* PIO Core पूर्णांकerrupt mask रेजिस्टर.
		   Enable ADV7604 INT1 पूर्णांकerrupts */
		cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK, irqs);
	पूर्ण अन्यथा अणु
		/* Disable all ADV7604 पूर्णांकerrupts */
		cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_STAT_MASK, 0);
	पूर्ण
पूर्ण

अटल अचिन्हित cobalt_get_sd_nr(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cobalt *cobalt = to_cobalt(sd->v4l2_dev);
	अचिन्हित i;

	क्रम (i = 0; i < COBALT_NUM_NODES; i++)
		अगर (sd == cobalt->streams[i].sd)
			वापस i;
	cobalt_err("Invalid adv7604 subdev pointer!\n");
	वापस 0;
पूर्ण

अटल व्योम cobalt_notअगरy(काष्ठा v4l2_subdev *sd,
			  अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	काष्ठा cobalt *cobalt = to_cobalt(sd->v4l2_dev);
	अचिन्हित sd_nr = cobalt_get_sd_nr(sd);
	काष्ठा cobalt_stream *s = &cobalt->streams[sd_nr];
	bool hotplug = arg ? *((पूर्णांक *)arg) : false;

	अगर (s->is_output)
		वापस;

	चयन (notअगरication) अणु
	हाल ADV76XX_HOTPLUG:
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_HPD_TO_CONNECTOR_BIT(sd_nr), hotplug);
		cobalt_dbg(1, "Set hotplug for adv %d to %d\n", sd_nr, hotplug);
		अवरोध;
	हाल V4L2_DEVICE_NOTIFY_EVENT:
		cobalt_dbg(1, "Format changed for adv %d\n", sd_nr);
		v4l2_event_queue(&s->vdev, arg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक get_payload_size(u16 code)
अणु
	चयन (code) अणु
	हाल 0: वापस 128;
	हाल 1: वापस 256;
	हाल 2: वापस 512;
	हाल 3: वापस 1024;
	हाल 4: वापस 2048;
	हाल 5: वापस 4096;
	शेष: वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *get_link_speed(u16 stat)
अणु
	चयन (stat & PCI_EXP_LNKSTA_CLS) अणु
	हाल 1:	वापस "2.5 Gbit/s";
	हाल 2:	वापस "5 Gbit/s";
	हाल 3:	वापस "10 Gbit/s";
	पूर्ण
	वापस "Unknown speed";
पूर्ण

व्योम cobalt_pcie_status_show(काष्ठा cobalt *cobalt)
अणु
	काष्ठा pci_dev *pci_dev = cobalt->pci_dev;
	काष्ठा pci_dev *pci_bus_dev = cobalt->pci_dev->bus->self;
	u32 capa;
	u16 stat, ctrl;

	अगर (!pci_is_pcie(pci_dev) || !pci_is_pcie(pci_bus_dev))
		वापस;

	/* Device */
	pcie_capability_पढ़ो_dword(pci_dev, PCI_EXP_DEVCAP, &capa);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_DEVCTL, &ctrl);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_DEVSTA, &stat);
	cobalt_info("PCIe device capability 0x%08x: Max payload %d\n",
		    capa, get_payload_size(capa & PCI_EXP_DEVCAP_PAYLOAD));
	cobalt_info("PCIe device control 0x%04x: Max payload %d. Max read request %d\n",
		    ctrl,
		    get_payload_size((ctrl & PCI_EXP_DEVCTL_PAYLOAD) >> 5),
		    get_payload_size((ctrl & PCI_EXP_DEVCTL_READRQ) >> 12));
	cobalt_info("PCIe device status 0x%04x\n", stat);

	/* Link */
	pcie_capability_पढ़ो_dword(pci_dev, PCI_EXP_LNKCAP, &capa);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_LNKCTL, &ctrl);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_LNKSTA, &stat);
	cobalt_info("PCIe link capability 0x%08x: %s per lane and %u lanes\n",
			capa, get_link_speed(capa),
			(capa & PCI_EXP_LNKCAP_MLW) >> 4);
	cobalt_info("PCIe link control 0x%04x\n", ctrl);
	cobalt_info("PCIe link status 0x%04x: %s per lane and %u lanes\n",
		    stat, get_link_speed(stat),
		    (stat & PCI_EXP_LNKSTA_NLW) >> 4);

	/* Bus */
	pcie_capability_पढ़ो_dword(pci_bus_dev, PCI_EXP_LNKCAP, &capa);
	cobalt_info("PCIe bus link capability 0x%08x: %s per lane and %u lanes\n",
			capa, get_link_speed(capa),
			(capa & PCI_EXP_LNKCAP_MLW) >> 4);

	/* Slot */
	pcie_capability_पढ़ो_dword(pci_dev, PCI_EXP_SLTCAP, &capa);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_SLTCTL, &ctrl);
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_SLTSTA, &stat);
	cobalt_info("PCIe slot capability 0x%08x\n", capa);
	cobalt_info("PCIe slot control 0x%04x\n", ctrl);
	cobalt_info("PCIe slot status 0x%04x\n", stat);
पूर्ण

अटल अचिन्हित pcie_link_get_lanes(काष्ठा cobalt *cobalt)
अणु
	काष्ठा pci_dev *pci_dev = cobalt->pci_dev;
	u16 link;

	अगर (!pci_is_pcie(pci_dev))
		वापस 0;
	pcie_capability_पढ़ो_word(pci_dev, PCI_EXP_LNKSTA, &link);
	वापस (link & PCI_EXP_LNKSTA_NLW) >> 4;
पूर्ण

अटल अचिन्हित pcie_bus_link_get_lanes(काष्ठा cobalt *cobalt)
अणु
	काष्ठा pci_dev *pci_dev = cobalt->pci_dev->bus->self;
	u32 link;

	अगर (!pci_is_pcie(pci_dev))
		वापस 0;
	pcie_capability_पढ़ो_dword(pci_dev, PCI_EXP_LNKCAP, &link);
	वापस (link & PCI_EXP_LNKCAP_MLW) >> 4;
पूर्ण

अटल व्योम msi_config_show(काष्ठा cobalt *cobalt, काष्ठा pci_dev *pci_dev)
अणु
	u16 ctrl, data;
	u32 adrs_l, adrs_h;

	pci_पढ़ो_config_word(pci_dev, 0x52, &ctrl);
	cobalt_info("MSI %s\n", ctrl & 1 ? "enable" : "disable");
	cobalt_info("MSI multiple message: Capable %u. Enable %u\n",
		    (1 << ((ctrl >> 1) & 7)), (1 << ((ctrl >> 4) & 7)));
	अगर (ctrl & 0x80)
		cobalt_info("MSI: 64-bit address capable\n");
	pci_पढ़ो_config_dword(pci_dev, 0x54, &adrs_l);
	pci_पढ़ो_config_dword(pci_dev, 0x58, &adrs_h);
	pci_पढ़ो_config_word(pci_dev, 0x5c, &data);
	अगर (ctrl & 0x80)
		cobalt_info("MSI: Address 0x%08x%08x. Data 0x%04x\n",
				adrs_h, adrs_l, data);
	अन्यथा
		cobalt_info("MSI: Address 0x%08x. Data 0x%04x\n",
				adrs_l, data);
पूर्ण

अटल व्योम cobalt_pci_iounmap(काष्ठा cobalt *cobalt, काष्ठा pci_dev *pci_dev)
अणु
	अगर (cobalt->bar0) अणु
		pci_iounmap(pci_dev, cobalt->bar0);
		cobalt->bar0 = शून्य;
	पूर्ण
	अगर (cobalt->bar1) अणु
		pci_iounmap(pci_dev, cobalt->bar1);
		cobalt->bar1 = शून्य;
	पूर्ण
पूर्ण

अटल व्योम cobalt_मुक्त_msi(काष्ठा cobalt *cobalt, काष्ठा pci_dev *pci_dev)
अणु
	मुक्त_irq(pci_dev->irq, (व्योम *)cobalt);
	pci_मुक्त_irq_vectors(pci_dev);
पूर्ण

अटल पूर्णांक cobalt_setup_pci(काष्ठा cobalt *cobalt, काष्ठा pci_dev *pci_dev,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	u32 ctrl;
	पूर्णांक ret;

	cobalt_dbg(1, "enabling pci device\n");

	ret = pci_enable_device(pci_dev);
	अगर (ret) अणु
		cobalt_err("can't enable device\n");
		वापस ret;
	पूर्ण
	pci_set_master(pci_dev);
	pci_पढ़ो_config_byte(pci_dev, PCI_CLASS_REVISION, &cobalt->card_rev);
	pci_पढ़ो_config_word(pci_dev, PCI_DEVICE_ID, &cobalt->device_id);

	चयन (cobalt->device_id) अणु
	हाल PCI_DEVICE_ID_COBALT:
		cobalt_info("PCI Express interface from Omnitek\n");
		अवरोध;
	शेष:
		cobalt_info("PCI Express interface provider is unknown!\n");
		अवरोध;
	पूर्ण

	अगर (pcie_link_get_lanes(cobalt) != 8) अणु
		cobalt_warn("PCI Express link width is %d lanes.\n",
				pcie_link_get_lanes(cobalt));
		अगर (pcie_bus_link_get_lanes(cobalt) < 8)
			cobalt_warn("The current slot only supports %d lanes, for best performance 8 are needed\n",
					pcie_bus_link_get_lanes(cobalt));
		अगर (pcie_link_get_lanes(cobalt) != pcie_bus_link_get_lanes(cobalt)) अणु
			cobalt_err("The card is most likely not seated correctly in the PCIe slot\n");
			ret = -EIO;
			जाओ err_disable;
		पूर्ण
	पूर्ण

	अगर (pci_set_dma_mask(pci_dev, DMA_BIT_MASK(64))) अणु
		ret = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			cobalt_err("no suitable DMA available\n");
			जाओ err_disable;
		पूर्ण
	पूर्ण

	ret = pci_request_regions(pci_dev, "cobalt");
	अगर (ret) अणु
		cobalt_err("error requesting regions\n");
		जाओ err_disable;
	पूर्ण

	cobalt_pcie_status_show(cobalt);

	cobalt->bar0 = pci_iomap(pci_dev, 0, 0);
	cobalt->bar1 = pci_iomap(pci_dev, 1, 0);
	अगर (cobalt->bar1 == शून्य) अणु
		cobalt->bar1 = pci_iomap(pci_dev, 2, 0);
		cobalt_info("64-bit BAR\n");
	पूर्ण
	अगर (!cobalt->bar0 || !cobalt->bar1) अणु
		ret = -EIO;
		जाओ err_release;
	पूर्ण

	/* Reset the video inमाला_दो beक्रमe enabling any पूर्णांकerrupts */
	ctrl = cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_CTRL_BASE);
	cobalt_ग_लिखो_bar1(cobalt, COBALT_SYS_CTRL_BASE, ctrl & ~0xf00);

	/* Disable पूर्णांकerrupts to prevent any spurious पूर्णांकerrupts
	   from being generated. */
	cobalt_set_पूर्णांकerrupt(cobalt, false);

	अगर (pci_alloc_irq_vectors(pci_dev, 1, 1, PCI_IRQ_MSI) < 1) अणु
		cobalt_err("Could not enable MSI\n");
		ret = -EIO;
		जाओ err_release;
	पूर्ण
	msi_config_show(cobalt, pci_dev);

	/* Register IRQ */
	अगर (request_irq(pci_dev->irq, cobalt_irq_handler, IRQF_SHARED,
			cobalt->v4l2_dev.name, (व्योम *)cobalt)) अणु
		cobalt_err("Failed to register irq %d\n", pci_dev->irq);
		ret = -EIO;
		जाओ err_msi;
	पूर्ण

	omni_sg_dma_init(cobalt);
	वापस 0;

err_msi:
	pci_disable_msi(pci_dev);

err_release:
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(pci_dev);

err_disable:
	pci_disable_device(cobalt->pci_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cobalt_hdl_info_get(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < COBALT_HDL_INFO_SIZE; i++)
		cobalt->hdl_info[i] =
			ioपढ़ो8(cobalt->bar1 + COBALT_HDL_INFO_BASE + i);
	cobalt->hdl_info[COBALT_HDL_INFO_SIZE - 1] = '\0';
	अगर (म_माला(cobalt->hdl_info, COBALT_HDL_SEARCH_STR))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम cobalt_stream_काष्ठा_init(काष्ठा cobalt *cobalt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < COBALT_NUM_STREAMS; i++) अणु
		काष्ठा cobalt_stream *s = &cobalt->streams[i];

		s->cobalt = cobalt;
		s->flags = 0;
		s->is_audio = false;
		s->is_output = false;
		s->is_dummy = true;

		/* The Memory DMA channels will always get a lower channel
		 * number than the FIFO DMA. Video input should map to the
		 * stream 0-3. The other can use stream काष्ठा from 4 and
		 * higher */
		अगर (i <= COBALT_HSMA_IN_NODE) अणु
			s->dma_channel = i + cobalt->first_fअगरo_channel;
			s->video_channel = i;
			s->dma_fअगरo_mask =
				COBALT_SYSSTAT_VI0_LOST_DATA_MSK << (4 * i);
			s->adv_irq_mask =
				COBALT_SYSSTAT_VI0_INT1_MSK << (4 * i);
		पूर्ण अन्यथा अगर (i >= COBALT_AUDIO_IN_STREAM &&
			   i <= COBALT_AUDIO_IN_STREAM + 4) अणु
			अचिन्हित idx = i - COBALT_AUDIO_IN_STREAM;

			s->dma_channel = 6 + idx;
			s->is_audio = true;
			s->video_channel = idx;
			s->dma_fअगरo_mask = COBALT_SYSSTAT_AUD_IN_LOST_DATA_MSK;
		पूर्ण अन्यथा अगर (i == COBALT_HSMA_OUT_NODE) अणु
			s->dma_channel = 11;
			s->is_output = true;
			s->video_channel = 5;
			s->dma_fअगरo_mask = COBALT_SYSSTAT_VOHSMA_LOST_DATA_MSK;
			s->adv_irq_mask = COBALT_SYSSTAT_VOHSMA_INT1_MSK;
		पूर्ण अन्यथा अगर (i == COBALT_AUDIO_OUT_STREAM) अणु
			s->dma_channel = 12;
			s->is_audio = true;
			s->is_output = true;
			s->video_channel = 5;
			s->dma_fअगरo_mask = COBALT_SYSSTAT_AUD_OUT_LOST_DATA_MSK;
		पूर्ण अन्यथा अणु
			/* FIXME: Memory DMA क्रम debug purpose */
			s->dma_channel = i - COBALT_NUM_NODES;
		पूर्ण
		cobalt_info("stream #%d -> dma channel #%d <- video channel %d\n",
			    i, s->dma_channel, s->video_channel);
	पूर्ण
पूर्ण

अटल पूर्णांक cobalt_subdevs_init(काष्ठा cobalt *cobalt)
अणु
	अटल काष्ठा adv76xx_platक्रमm_data adv7604_pdata = अणु
		.disable_pwrdnb = 1,
		.ain_sel = ADV7604_AIN7_8_9_NC_SYNC_3_1,
		.bus_order = ADV7604_BUS_ORDER_BRG,
		.blank_data = 1,
		.op_क्रमmat_mode_sel = ADV7604_OP_FORMAT_MODE0,
		.पूर्णांक1_config = ADV76XX_INT1_CONFIG_ACTIVE_HIGH,
		.dr_str_data = ADV76XX_DR_STR_HIGH,
		.dr_str_clk = ADV76XX_DR_STR_HIGH,
		.dr_str_sync = ADV76XX_DR_STR_HIGH,
		.hdmi_मुक्त_run_mode = 1,
		.inv_vs_pol = 1,
		.inv_hs_pol = 1,
	पूर्ण;
	अटल काष्ठा i2c_board_info adv7604_info = अणु
		.type = "adv7604",
		.addr = 0x20,
		.platक्रमm_data = &adv7604_pdata,
	पूर्ण;

	काष्ठा cobalt_stream *s = cobalt->streams;
	पूर्णांक i;

	क्रम (i = 0; i < COBALT_NUM_INPUTS; i++) अणु
		काष्ठा v4l2_subdev_क्रमmat sd_fmt = अणु
			.pad = ADV7604_PAD_SOURCE,
			.which = V4L2_SUBDEV_FORMAT_ACTIVE,
			.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
		पूर्ण;
		काष्ठा v4l2_subdev_edid cobalt_edid = अणु
			.pad = ADV76XX_PAD_HDMI_PORT_A,
			.start_block = 0,
			.blocks = 2,
			.edid = edid,
		पूर्ण;
		पूर्णांक err;

		s[i].pad_source = ADV7604_PAD_SOURCE;
		s[i].i2c_adap = &cobalt->i2c_adap[i];
		अगर (s[i].i2c_adap->dev.parent == शून्य)
			जारी;
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_NRESET_TO_HDMI_BIT(i), 1);
		s[i].sd = v4l2_i2c_new_subdev_board(&cobalt->v4l2_dev,
			s[i].i2c_adap, &adv7604_info, शून्य);
		अगर (!s[i].sd) अणु
			अगर (cobalt_ignore_err)
				जारी;
			वापस -ENODEV;
		पूर्ण
		err = v4l2_subdev_call(s[i].sd, video, s_routing,
				ADV76XX_PAD_HDMI_PORT_A, 0, 0);
		अगर (err)
			वापस err;
		err = v4l2_subdev_call(s[i].sd, pad, set_edid,
				&cobalt_edid);
		अगर (err)
			वापस err;
		err = v4l2_subdev_call(s[i].sd, pad, set_fmt, शून्य,
				&sd_fmt);
		अगर (err)
			वापस err;
		/* Reset channel video module */
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(i), 0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(i), 1);
		mdelay(1);
		s[i].is_dummy = false;
		cobalt->streams[i + COBALT_AUDIO_IN_STREAM].is_dummy = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cobalt_subdevs_hsma_init(काष्ठा cobalt *cobalt)
अणु
	अटल काष्ठा adv7842_platक्रमm_data adv7842_pdata = अणु
		.disable_pwrdnb = 1,
		.ain_sel = ADV7842_AIN1_2_3_NC_SYNC_1_2,
		.bus_order = ADV7842_BUS_ORDER_RBG,
		.op_क्रमmat_mode_sel = ADV7842_OP_FORMAT_MODE0,
		.blank_data = 1,
		.dr_str_data = 3,
		.dr_str_clk = 3,
		.dr_str_sync = 3,
		.mode = ADV7842_MODE_HDMI,
		.hdmi_मुक्त_run_enable = 1,
		.vid_std_select = ADV7842_HDMI_COMP_VID_STD_HD_1250P,
		.i2c_sdp_io = 0x4a,
		.i2c_sdp = 0x48,
		.i2c_cp = 0x22,
		.i2c_vdp = 0x24,
		.i2c_afe = 0x26,
		.i2c_hdmi = 0x34,
		.i2c_repeater = 0x32,
		.i2c_edid = 0x36,
		.i2c_infoframe = 0x3e,
		.i2c_cec = 0x40,
		.i2c_avlink = 0x42,
	पूर्ण;
	अटल काष्ठा i2c_board_info adv7842_info = अणु
		.type = "adv7842",
		.addr = 0x20,
		.platक्रमm_data = &adv7842_pdata,
	पूर्ण;
	काष्ठा v4l2_subdev_क्रमmat sd_fmt = अणु
		.pad = ADV7842_PAD_SOURCE,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.क्रमmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
	पूर्ण;
	अटल काष्ठा adv7511_platक्रमm_data adv7511_pdata = अणु
		.i2c_edid = 0x7e >> 1,
		.i2c_cec = 0x7c >> 1,
		.i2c_pkपंचांगem = 0x70 >> 1,
		.cec_clk = 12000000,
	पूर्ण;
	अटल काष्ठा i2c_board_info adv7511_info = अणु
		.type = "adv7511-v4l2",
		.addr = 0x39, /* 0x39 or 0x3d */
		.platक्रमm_data = &adv7511_pdata,
	पूर्ण;
	काष्ठा v4l2_subdev_edid cobalt_edid = अणु
		.pad = ADV7842_EDID_PORT_A,
		.start_block = 0,
		.blocks = 2,
		.edid = edid,
	पूर्ण;
	काष्ठा cobalt_stream *s = &cobalt->streams[COBALT_HSMA_IN_NODE];

	s->i2c_adap = &cobalt->i2c_adap[COBALT_NUM_ADAPTERS - 1];
	अगर (s->i2c_adap->dev.parent == शून्य)
		वापस 0;
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_NRESET_TO_HDMI_BIT(4), 1);

	s->sd = v4l2_i2c_new_subdev_board(&cobalt->v4l2_dev,
			s->i2c_adap, &adv7842_info, शून्य);
	अगर (s->sd) अणु
		पूर्णांक err = v4l2_subdev_call(s->sd, pad, set_edid, &cobalt_edid);

		अगर (err)
			वापस err;
		err = v4l2_subdev_call(s->sd, pad, set_fmt, शून्य,
				&sd_fmt);
		अगर (err)
			वापस err;
		cobalt->have_hsma_rx = true;
		s->pad_source = ADV7842_PAD_SOURCE;
		s->is_dummy = false;
		cobalt->streams[4 + COBALT_AUDIO_IN_STREAM].is_dummy = false;
		/* Reset channel video module */
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(4), 0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(4), 1);
		mdelay(1);
		वापस err;
	पूर्ण
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_NRESET_TO_HDMI_BIT(4), 0);
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_PWRDN0_TO_HSMA_TX_BIT, 0);
	s++;
	s->i2c_adap = &cobalt->i2c_adap[COBALT_NUM_ADAPTERS - 1];
	s->sd = v4l2_i2c_new_subdev_board(&cobalt->v4l2_dev,
			s->i2c_adap, &adv7511_info, शून्य);
	अगर (s->sd) अणु
		/* A transmitter is hooked up, so we can set this bit */
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT, 1);
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_RX_RESETN_BIT(4), 0);
		cobalt_s_bit_sysctrl(cobalt,
				COBALT_SYS_CTRL_VIDEO_TX_RESETN_BIT, 1);
		cobalt->have_hsma_tx = true;
		v4l2_subdev_call(s->sd, core, s_घातer, 1);
		v4l2_subdev_call(s->sd, video, s_stream, 1);
		v4l2_subdev_call(s->sd, audio, s_stream, 1);
		v4l2_ctrl_s_ctrl(v4l2_ctrl_find(s->sd->ctrl_handler,
				 V4L2_CID_DV_TX_MODE), V4L2_DV_TX_MODE_HDMI);
		s->is_dummy = false;
		cobalt->streams[COBALT_AUDIO_OUT_STREAM].is_dummy = false;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cobalt_probe(काष्ठा pci_dev *pci_dev,
				  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा cobalt *cobalt;
	पूर्णांक retval = 0;
	पूर्णांक i;

	/* FIXME - module parameter arrays स्थिरrain max instances */
	i = atomic_inc_वापस(&cobalt_instance) - 1;

	cobalt = kzalloc(माप(काष्ठा cobalt), GFP_KERNEL);
	अगर (cobalt == शून्य)
		वापस -ENOMEM;
	cobalt->pci_dev = pci_dev;
	cobalt->instance = i;

	retval = v4l2_device_रेजिस्टर(&pci_dev->dev, &cobalt->v4l2_dev);
	अगर (retval) अणु
		pr_err("cobalt: v4l2_device_register of card %d failed\n",
				cobalt->instance);
		kमुक्त(cobalt);
		वापस retval;
	पूर्ण
	snम_लिखो(cobalt->v4l2_dev.name, माप(cobalt->v4l2_dev.name),
		 "cobalt-%d", cobalt->instance);
	cobalt->v4l2_dev.notअगरy = cobalt_notअगरy;
	cobalt_info("Initializing card %d\n", cobalt->instance);

	cobalt->irq_work_queues =
		create_singlethपढ़ो_workqueue(cobalt->v4l2_dev.name);
	अगर (cobalt->irq_work_queues == शून्य) अणु
		cobalt_err("Could not create workqueue\n");
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	INIT_WORK(&cobalt->irq_work_queue, cobalt_irq_work_handler);

	/* PCI Device Setup */
	retval = cobalt_setup_pci(cobalt, pci_dev, pci_id);
	अगर (retval != 0)
		जाओ err_wq;

	/* Show HDL version info */
	अगर (cobalt_hdl_info_get(cobalt))
		cobalt_info("Not able to read the HDL info\n");
	अन्यथा
		cobalt_info("%s", cobalt->hdl_info);

	retval = cobalt_i2c_init(cobalt);
	अगर (retval)
		जाओ err_pci;

	cobalt_stream_काष्ठा_init(cobalt);

	retval = cobalt_subdevs_init(cobalt);
	अगर (retval)
		जाओ err_i2c;

	अगर (!(cobalt_पढ़ो_bar1(cobalt, COBALT_SYS_STAT_BASE) &
			COBALT_SYSSTAT_HSMA_PRSNTN_MSK)) अणु
		retval = cobalt_subdevs_hsma_init(cobalt);
		अगर (retval)
			जाओ err_i2c;
	पूर्ण

	retval = cobalt_nodes_रेजिस्टर(cobalt);
	अगर (retval) अणु
		cobalt_err("Error %d registering device nodes\n", retval);
		जाओ err_i2c;
	पूर्ण
	cobalt_set_पूर्णांकerrupt(cobalt, true);
	v4l2_device_call_all(&cobalt->v4l2_dev, 0, core,
					पूर्णांकerrupt_service_routine, 0, शून्य);

	cobalt_info("Initialized cobalt card\n");

	cobalt_flash_probe(cobalt);

	वापस 0;

err_i2c:
	cobalt_i2c_निकास(cobalt);
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT, 0);
err_pci:
	cobalt_मुक्त_msi(cobalt, pci_dev);
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(cobalt->pci_dev);
	pci_disable_device(cobalt->pci_dev);
err_wq:
	destroy_workqueue(cobalt->irq_work_queues);
err:
	cobalt_err("error %d on initialization\n", retval);

	v4l2_device_unरेजिस्टर(&cobalt->v4l2_dev);
	kमुक्त(cobalt);
	वापस retval;
पूर्ण

अटल व्योम cobalt_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा cobalt *cobalt = to_cobalt(v4l2_dev);
	पूर्णांक i;

	cobalt_flash_हटाओ(cobalt);
	cobalt_set_पूर्णांकerrupt(cobalt, false);
	flush_workqueue(cobalt->irq_work_queues);
	cobalt_nodes_unरेजिस्टर(cobalt);
	क्रम (i = 0; i < COBALT_NUM_ADAPTERS; i++) अणु
		काष्ठा v4l2_subdev *sd = cobalt->streams[i].sd;
		काष्ठा i2c_client *client;

		अगर (sd == शून्य)
			जारी;
		client = v4l2_get_subdevdata(sd);
		v4l2_device_unरेजिस्टर_subdev(sd);
		i2c_unरेजिस्टर_device(client);
	पूर्ण
	cobalt_i2c_निकास(cobalt);
	cobalt_मुक्त_msi(cobalt, pci_dev);
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT, 0);
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(cobalt->pci_dev);
	pci_disable_device(cobalt->pci_dev);
	destroy_workqueue(cobalt->irq_work_queues);

	cobalt_info("removed cobalt card\n");

	v4l2_device_unरेजिस्टर(v4l2_dev);
	kमुक्त(cobalt);
पूर्ण

/* define a pci_driver क्रम card detection */
अटल काष्ठा pci_driver cobalt_pci_driver = अणु
	.name =     "cobalt",
	.id_table = cobalt_pci_tbl,
	.probe =    cobalt_probe,
	.हटाओ =   cobalt_हटाओ,
पूर्ण;

module_pci_driver(cobalt_pci_driver);
