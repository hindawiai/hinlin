<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित BRCMFMAC_BUS_H
#घोषणा BRCMFMAC_BUS_H

#समावेश "debug.h"

/* IDs of the 6 शेष common rings of msgbuf protocol */
#घोषणा BRCMF_H2D_MSGRING_CONTROL_SUBMIT	0
#घोषणा BRCMF_H2D_MSGRING_RXPOST_SUBMIT		1
#घोषणा BRCMF_H2D_MSGRING_FLOWRING_IDSTART	2
#घोषणा BRCMF_D2H_MSGRING_CONTROL_COMPLETE	2
#घोषणा BRCMF_D2H_MSGRING_TX_COMPLETE		3
#घोषणा BRCMF_D2H_MSGRING_RX_COMPLETE		4


#घोषणा BRCMF_NROF_H2D_COMMON_MSGRINGS		2
#घोषणा BRCMF_NROF_D2H_COMMON_MSGRINGS		3
#घोषणा BRCMF_NROF_COMMON_MSGRINGS	(BRCMF_NROF_H2D_COMMON_MSGRINGS + \
					 BRCMF_NROF_D2H_COMMON_MSGRINGS)

/* The level of bus communication with the करोngle */
क्रमागत brcmf_bus_state अणु
	BRCMF_BUS_DOWN,		/* Not पढ़ोy क्रम frame transfers */
	BRCMF_BUS_UP		/* Ready क्रम frame transfers */
पूर्ण;

/* The level of bus communication with the करोngle */
क्रमागत brcmf_bus_protocol_type अणु
	BRCMF_PROTO_BCDC,
	BRCMF_PROTO_MSGBUF
पूर्ण;

काष्ठा brcmf_mp_device;

काष्ठा brcmf_bus_dcmd अणु
	अक्षर *name;
	अक्षर *param;
	पूर्णांक param_len;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा brcmf_bus_ops - bus callback operations.
 *
 * @preinit: execute bus/device specअगरic करोngle init commands (optional).
 * @init: prepare क्रम communication with करोngle.
 * @stop: clear pending frames, disable data flow.
 * @txdata: send a data frame to the करोngle. When the data
 *	has been transferred, the common driver must be
 *	notअगरied using brcmf_txcomplete(). The common
 *	driver calls this function with पूर्णांकerrupts
 *	disabled.
 * @txctl: transmit a control request message to करोngle.
 * @rxctl: receive a control response message from करोngle.
 * @gettxq: obtain a reference of bus transmit queue (optional).
 * @wowl_config: specअगरy अगर करोngle is configured क्रम wowl when going to suspend
 * @get_ramsize: obtain size of device memory.
 * @get_memdump: obtain device memory dump in provided buffer.
 * @get_fwname: obtain firmware name.
 *
 * This काष्ठाure provides an असलtract पूर्णांकerface towards the
 * bus specअगरic driver. For control messages to common driver
 * will assure there is only one active transaction. Unless
 * indicated otherwise these callbacks are mandatory.
 */
काष्ठा brcmf_bus_ops अणु
	पूर्णांक (*preinit)(काष्ठा device *dev);
	व्योम (*stop)(काष्ठा device *dev);
	पूर्णांक (*txdata)(काष्ठा device *dev, काष्ठा sk_buff *skb);
	पूर्णांक (*txctl)(काष्ठा device *dev, अचिन्हित अक्षर *msg, uपूर्णांक len);
	पूर्णांक (*rxctl)(काष्ठा device *dev, अचिन्हित अक्षर *msg, uपूर्णांक len);
	काष्ठा pktq * (*gettxq)(काष्ठा device *dev);
	व्योम (*wowl_config)(काष्ठा device *dev, bool enabled);
	माप_प्रकार (*get_ramsize)(काष्ठा device *dev);
	पूर्णांक (*get_memdump)(काष्ठा device *dev, व्योम *data, माप_प्रकार len);
	पूर्णांक (*get_fwname)(काष्ठा device *dev, स्थिर अक्षर *ext,
			  अचिन्हित अक्षर *fw_name);
	व्योम (*debugfs_create)(काष्ठा device *dev);
	पूर्णांक (*reset)(काष्ठा device *dev);
पूर्ण;


/**
 * काष्ठा brcmf_bus_msgbuf - bus ringbuf अगर in हाल of msgbuf.
 *
 * @commonrings: commonrings which are always there.
 * @flowrings: commonrings which are dynamically created and destroyed क्रम data.
 * @rx_dataoffset: अगर set then all rx data has this this offset.
 * @max_rxbufpost: maximum number of buffers to post क्रम rx.
 * @max_flowrings: maximum number of tx flow rings supported.
 * @max_submissionrings: maximum number of submission rings(h2d) supported.
 * @max_completionrings: maximum number of completion rings(d2h) supported.
 */
काष्ठा brcmf_bus_msgbuf अणु
	काष्ठा brcmf_commonring *commonrings[BRCMF_NROF_COMMON_MSGRINGS];
	काष्ठा brcmf_commonring **flowrings;
	u32 rx_dataoffset;
	u32 max_rxbufpost;
	u16 max_flowrings;
	u16 max_submissionrings;
	u16 max_completionrings;
पूर्ण;


/**
 * काष्ठा brcmf_bus_stats - bus statistic counters.
 *
 * @pktcowed: packets cowed क्रम extra headroom/unorphan.
 * @pktcow_failed: packets dropped due to failed cow-ing.
 */
काष्ठा brcmf_bus_stats अणु
	atomic_t pktcowed;
	atomic_t pktcow_failed;
पूर्ण;

/**
 * काष्ठा brcmf_bus - पूर्णांकerface काष्ठाure between common and bus layer
 *
 * @bus_priv: poपूर्णांकer to निजी bus device.
 * @proto_type: protocol type, bcdc or msgbuf
 * @dev: device poपूर्णांकer of bus device.
 * @drvr: खुला driver inक्रमmation.
 * @state: operational state of the bus पूर्णांकerface.
 * @stats: statistics shared between common and bus layer.
 * @maxctl: maximum size क्रम rxctl request message.
 * @chip: device identअगरier of the करोngle chip.
 * @always_use_fws_queue: bus wants use queue also when fwसंकेत is inactive.
 * @wowl_supported: is wowl supported by bus driver.
 * @chiprev: revision of the करोngle chip.
 * @msgbuf: msgbuf protocol parameters provided by bus layer.
 */
काष्ठा brcmf_bus अणु
	जोड़ अणु
		काष्ठा brcmf_sdio_dev *sdio;
		काष्ठा brcmf_usbdev *usb;
		काष्ठा brcmf_pciedev *pcie;
	पूर्ण bus_priv;
	क्रमागत brcmf_bus_protocol_type proto_type;
	काष्ठा device *dev;
	काष्ठा brcmf_pub *drvr;
	क्रमागत brcmf_bus_state state;
	काष्ठा brcmf_bus_stats stats;
	uपूर्णांक maxctl;
	u32 chip;
	u32 chiprev;
	bool always_use_fws_queue;
	bool wowl_supported;

	स्थिर काष्ठा brcmf_bus_ops *ops;
	काष्ठा brcmf_bus_msgbuf *msgbuf;
पूर्ण;

/*
 * callback wrappers
 */
अटल अंतरभूत पूर्णांक brcmf_bus_preinit(काष्ठा brcmf_bus *bus)
अणु
	अगर (!bus->ops->preinit)
		वापस 0;
	वापस bus->ops->preinit(bus->dev);
पूर्ण

अटल अंतरभूत व्योम brcmf_bus_stop(काष्ठा brcmf_bus *bus)
अणु
	bus->ops->stop(bus->dev);
पूर्ण

अटल अंतरभूत पूर्णांक brcmf_bus_txdata(काष्ठा brcmf_bus *bus, काष्ठा sk_buff *skb)
अणु
	वापस bus->ops->txdata(bus->dev, skb);
पूर्ण

अटल अंतरभूत
पूर्णांक brcmf_bus_txctl(काष्ठा brcmf_bus *bus, अचिन्हित अक्षर *msg, uपूर्णांक len)
अणु
	वापस bus->ops->txctl(bus->dev, msg, len);
पूर्ण

अटल अंतरभूत
पूर्णांक brcmf_bus_rxctl(काष्ठा brcmf_bus *bus, अचिन्हित अक्षर *msg, uपूर्णांक len)
अणु
	वापस bus->ops->rxctl(bus->dev, msg, len);
पूर्ण

अटल अंतरभूत
काष्ठा pktq *brcmf_bus_gettxq(काष्ठा brcmf_bus *bus)
अणु
	अगर (!bus->ops->gettxq)
		वापस ERR_PTR(-ENOENT);

	वापस bus->ops->gettxq(bus->dev);
पूर्ण

अटल अंतरभूत
व्योम brcmf_bus_wowl_config(काष्ठा brcmf_bus *bus, bool enabled)
अणु
	अगर (bus->ops->wowl_config)
		bus->ops->wowl_config(bus->dev, enabled);
पूर्ण

अटल अंतरभूत माप_प्रकार brcmf_bus_get_ramsize(काष्ठा brcmf_bus *bus)
अणु
	अगर (!bus->ops->get_ramsize)
		वापस 0;

	वापस bus->ops->get_ramsize(bus->dev);
पूर्ण

अटल अंतरभूत
पूर्णांक brcmf_bus_get_memdump(काष्ठा brcmf_bus *bus, व्योम *data, माप_प्रकार len)
अणु
	अगर (!bus->ops->get_memdump)
		वापस -EOPNOTSUPP;

	वापस bus->ops->get_memdump(bus->dev, data, len);
पूर्ण

अटल अंतरभूत
पूर्णांक brcmf_bus_get_fwname(काष्ठा brcmf_bus *bus, स्थिर अक्षर *ext,
			 अचिन्हित अक्षर *fw_name)
अणु
	वापस bus->ops->get_fwname(bus->dev, ext, fw_name);
पूर्ण

अटल अंतरभूत
व्योम brcmf_bus_debugfs_create(काष्ठा brcmf_bus *bus)
अणु
	अगर (!bus->ops->debugfs_create)
		वापस;

	वापस bus->ops->debugfs_create(bus->dev);
पूर्ण

अटल अंतरभूत
पूर्णांक brcmf_bus_reset(काष्ठा brcmf_bus *bus)
अणु
	अगर (!bus->ops->reset)
		वापस -EOPNOTSUPP;

	वापस bus->ops->reset(bus->dev);
पूर्ण

/*
 * पूर्णांकerface functions from common layer
 */

/* Receive frame क्रम delivery to OS.  Callee disposes of rxp. */
व्योम brcmf_rx_frame(काष्ठा device *dev, काष्ठा sk_buff *rxp, bool handle_event,
		    bool inirq);
/* Receive async event packet from firmware. Callee disposes of rxp. */
व्योम brcmf_rx_event(काष्ठा device *dev, काष्ठा sk_buff *rxp);

पूर्णांक brcmf_alloc(काष्ठा device *dev, काष्ठा brcmf_mp_device *settings);
/* Indication from bus module regarding presence/insertion of करोngle. */
पूर्णांक brcmf_attach(काष्ठा device *dev);
/* Indication from bus module regarding removal/असलence of करोngle */
व्योम brcmf_detach(काष्ठा device *dev);
व्योम brcmf_मुक्त(काष्ठा device *dev);
/* Indication from bus module that करोngle should be reset */
व्योम brcmf_dev_reset(काष्ठा device *dev);
/* Request from bus module to initiate a coredump */
व्योम brcmf_dev_coredump(काष्ठा device *dev);
/* Indication that firmware has halted or crashed */
व्योम brcmf_fw_crashed(काष्ठा device *dev);

/* Configure the "global" bus state used by upper layers */
व्योम brcmf_bus_change_state(काष्ठा brcmf_bus *bus, क्रमागत brcmf_bus_state state);

s32 brcmf_iovar_data_set(काष्ठा device *dev, अक्षर *name, व्योम *data, u32 len);
व्योम brcmf_bus_add_txhdrlen(काष्ठा device *dev, uपूर्णांक len);

#अगर_घोषित CONFIG_BRCMFMAC_SDIO
व्योम brcmf_sdio_निकास(व्योम);
पूर्णांक brcmf_sdio_रेजिस्टर(व्योम);
#अन्यथा
अटल अंतरभूत व्योम brcmf_sdio_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक brcmf_sdio_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BRCMFMAC_USB
व्योम brcmf_usb_निकास(व्योम);
पूर्णांक brcmf_usb_रेजिस्टर(व्योम);
#अन्यथा
अटल अंतरभूत व्योम brcmf_usb_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक brcmf_usb_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BRCMFMAC_PCIE
व्योम brcmf_pcie_निकास(व्योम);
पूर्णांक brcmf_pcie_रेजिस्टर(व्योम);
#अन्यथा
अटल अंतरभूत व्योम brcmf_pcie_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक brcmf_pcie_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* BRCMFMAC_BUS_H */
