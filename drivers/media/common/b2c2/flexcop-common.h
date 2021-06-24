<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-common.h - common header file क्रम device-specअगरic source files
 * see flexcop.c क्रम copyright inक्रमmation
 */
#अगर_अघोषित __FLEXCOP_COMMON_H__
#घोषणा __FLEXCOP_COMMON_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#समावेश "flexcop-reg.h"

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvb_frontend.h>

#घोषणा FC_MAX_FEED 256

#अगर_अघोषित FC_LOG_PREFIX
#warning please define a log prefix क्रम your file, using a शेष one
#घोषणा FC_LOG_PREFIX "b2c2-undef"
#पूर्ण_अगर

/* Steal from usb.h */
#अघोषित err
#घोषणा err(क्रमmat, arg...) \
	prपूर्णांकk(KERN_ERR FC_LOG_PREFIX ": " क्रमmat "\n" , ## arg)
#अघोषित info
#घोषणा info(क्रमmat, arg...) \
	prपूर्णांकk(KERN_INFO FC_LOG_PREFIX ": " क्रमmat "\n" , ## arg)
#अघोषित warn
#घोषणा warn(क्रमmat, arg...) \
	prपूर्णांकk(KERN_WARNING FC_LOG_PREFIX ": " क्रमmat "\n" , ## arg)

काष्ठा flexcop_dma अणु
	काष्ठा pci_dev *pdev;

	u8 *cpu_addr0;
	dma_addr_t dma_addr0;
	u8 *cpu_addr1;
	dma_addr_t dma_addr1;
	u32 size; /* size of each address in bytes */
पूर्ण;

काष्ठा flexcop_i2c_adapter अणु
	काष्ठा flexcop_device *fc;
	काष्ठा i2c_adapter i2c_adap;

	u8 no_base_addr;
	flexcop_i2c_port_t port;
पूर्ण;

/* Control काष्ठाure क्रम data definitions that are common to
 * the B2C2-based PCI and USB devices.
 */
काष्ठा flexcop_device अणु
	/* general */
	काष्ठा device *dev; /* क्रम firmware_class */

#घोषणा FC_STATE_DVB_INIT 0x01
#घोषणा FC_STATE_I2C_INIT 0x02
#घोषणा FC_STATE_FE_INIT  0x04
	पूर्णांक init_state;

	/* device inक्रमmation */
	पूर्णांक has_32_hw_pid_filter;
	flexcop_revision_t rev;
	flexcop_device_type_t dev_type;
	flexcop_bus_t bus_type;

	/* dvb stuff */
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_frontend *fe;
	काष्ठा dvb_net dvbnet;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;
	पूर्णांक (*fe_sleep) (काष्ठा dvb_frontend *);

	काष्ठा flexcop_i2c_adapter fc_i2c_adap[3];
	काष्ठा mutex i2c_mutex;
	काष्ठा module *owner;

	/* options and status */
	पूर्णांक extra_feedcount;
	पूर्णांक feedcount;
	पूर्णांक pid_filtering;
	पूर्णांक fullts_streaming_state;
	पूर्णांक skip_6_hw_pid_filter;

	/* bus specअगरic callbacks */
	flexcop_ibi_value(*पढ़ो_ibi_reg) (काष्ठा flexcop_device *,
			flexcop_ibi_रेजिस्टर);
	पूर्णांक (*ग_लिखो_ibi_reg) (काष्ठा flexcop_device *,
			flexcop_ibi_रेजिस्टर, flexcop_ibi_value);
	पूर्णांक (*i2c_request) (काष्ठा flexcop_i2c_adapter *,
		flexcop_access_op_t, u8 chipaddr, u8 addr, u8 *buf, u16 len);
	पूर्णांक (*stream_control) (काष्ठा flexcop_device *, पूर्णांक);
	पूर्णांक (*get_mac_addr) (काष्ठा flexcop_device *fc, पूर्णांक extended);
	व्योम *bus_specअगरic;
पूर्ण;

/* exported prototypes */

/* from flexcop.c */
व्योम flexcop_pass_dmx_data(काष्ठा flexcop_device *fc, u8 *buf, u32 len);
व्योम flexcop_pass_dmx_packets(काष्ठा flexcop_device *fc, u8 *buf, u32 no);

काष्ठा flexcop_device *flexcop_device_kदो_स्मृति(माप_प्रकार bus_specअगरic_len);
व्योम flexcop_device_kमुक्त(काष्ठा flexcop_device *);

पूर्णांक flexcop_device_initialize(काष्ठा flexcop_device *);
व्योम flexcop_device_निकास(काष्ठा flexcop_device *fc);
व्योम flexcop_reset_block_300(काष्ठा flexcop_device *fc);

/* from flexcop-dma.c */
पूर्णांक flexcop_dma_allocate(काष्ठा pci_dev *pdev,
		काष्ठा flexcop_dma *dma, u32 size);
व्योम flexcop_dma_मुक्त(काष्ठा flexcop_dma *dma);

पूर्णांक flexcop_dma_control_समयr_irq(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t no, पूर्णांक onoff);
पूर्णांक flexcop_dma_control_size_irq(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t no, पूर्णांक onoff);
पूर्णांक flexcop_dma_config(काष्ठा flexcop_device *fc, काष्ठा flexcop_dma *dma,
		flexcop_dma_index_t dma_idx);
पूर्णांक flexcop_dma_xfer_control(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t dma_idx, flexcop_dma_addr_index_t index,
		पूर्णांक onoff);
पूर्णांक flexcop_dma_config_समयr(काष्ठा flexcop_device *fc,
		flexcop_dma_index_t dma_idx, u8 cycles);

/* from flexcop-eeprom.c */
/* the PCI part uses this call to get the MAC address, the USB part has its own */
पूर्णांक flexcop_eeprom_check_mac_addr(काष्ठा flexcop_device *fc, पूर्णांक extended);

/* from flexcop-i2c.c */
/* the PCI part uses this a i2c_request callback, whereas the usb part has its own
 * one. We have it in flexcop-i2c.c, because it is going via the actual
 * I2C-channel of the flexcop.
 */
पूर्णांक flexcop_i2c_request(काष्ठा flexcop_i2c_adapter*, flexcop_access_op_t,
	u8 chipaddr, u8 addr, u8 *buf, u16 len);

/* from flexcop-sram.c */
पूर्णांक flexcop_sram_set_dest(काष्ठा flexcop_device *fc, flexcop_sram_dest_t dest,
	flexcop_sram_dest_target_t target);
व्योम flexcop_wan_set_speed(काष्ठा flexcop_device *fc, flexcop_wan_speed_t s);
व्योम flexcop_sram_ctrl(काष्ठा flexcop_device *fc,
		पूर्णांक usb_wan, पूर्णांक sramdma, पूर्णांक maximumfill);

/* global prototypes क्रम the flexcop-chip */
/* from flexcop-fe-tuner.c */
पूर्णांक flexcop_frontend_init(काष्ठा flexcop_device *fc);
व्योम flexcop_frontend_निकास(काष्ठा flexcop_device *fc);

/* from flexcop-i2c.c */
पूर्णांक flexcop_i2c_init(काष्ठा flexcop_device *fc);
व्योम flexcop_i2c_निकास(काष्ठा flexcop_device *fc);

/* from flexcop-sram.c */
पूर्णांक flexcop_sram_init(काष्ठा flexcop_device *fc);

/* from flexcop-misc.c */
व्योम flexcop_determine_revision(काष्ठा flexcop_device *fc);
व्योम flexcop_device_name(काष्ठा flexcop_device *fc,
		स्थिर अक्षर *prefix, स्थिर अक्षर *suffix);
व्योम flexcop_dump_reg(काष्ठा flexcop_device *fc,
		flexcop_ibi_रेजिस्टर reg, पूर्णांक num);

/* from flexcop-hw-filter.c */
पूर्णांक flexcop_pid_feed_control(काष्ठा flexcop_device *fc,
		काष्ठा dvb_demux_feed *dvbdmxfeed, पूर्णांक onoff);
व्योम flexcop_hw_filter_init(काष्ठा flexcop_device *fc);

व्योम flexcop_smc_ctrl(काष्ठा flexcop_device *fc, पूर्णांक onoff);

व्योम flexcop_set_mac_filter(काष्ठा flexcop_device *fc, u8 mac[6]);
व्योम flexcop_mac_filter_ctrl(काष्ठा flexcop_device *fc, पूर्णांक onoff);

#पूर्ण_अगर
