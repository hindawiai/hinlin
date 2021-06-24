<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HackRF driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

/*
 * Used Avago MGA-81563 RF amplअगरier could be destroyed pretty easily with too
 * strong संकेत or transmitting to bad antenna.
 * Set RF gain control to 'grabbed' state by शेष क्रम sure.
 */
अटल bool hackrf_enable_rf_gain_ctrl;
module_param_named(enable_rf_gain_ctrl, hackrf_enable_rf_gain_ctrl, bool, 0644);
MODULE_PARM_DESC(enable_rf_gain_ctrl, "enable RX/TX RF amplifier control (warn: could damage amplifier)");

/* HackRF USB API commands (from HackRF Library) */
क्रमागत अणु
	CMD_SET_TRANSCEIVER_MODE           = 0x01,
	CMD_SAMPLE_RATE_SET                = 0x06,
	CMD_BASEBAND_FILTER_BANDWIDTH_SET  = 0x07,
	CMD_BOARD_ID_READ                  = 0x0e,
	CMD_VERSION_STRING_READ            = 0x0f,
	CMD_SET_FREQ                       = 0x10,
	CMD_AMP_ENABLE                     = 0x11,
	CMD_SET_LNA_GAIN                   = 0x13,
	CMD_SET_VGA_GAIN                   = 0x14,
	CMD_SET_TXVGA_GAIN                 = 0x15,
पूर्ण;

/*
 *       bEndpoपूर्णांकAddress     0x81  EP 1 IN
 *         Transfer Type            Bulk
 *       wMaxPacketSize     0x0200  1x 512 bytes
 */
#घोषणा MAX_BULK_BUFS            (6)
#घोषणा BULK_BUFFER_SIZE         (128 * 512)

अटल स्थिर काष्ठा v4l2_frequency_band bands_adc_dac[] = अणु
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_SDR,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =   200000,
		.rangehigh  = 24000000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands_rx_tx[] = अणु
	अणु
		.tuner = 1,
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =          1,
		.rangehigh  = 4294967294LL, /* max u32, hw goes over 7GHz */
	पूर्ण,
पूर्ण;

/* stream क्रमmats */
काष्ठा hackrf_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	buffersize;
पूर्ण;

/* क्रमmat descriptions क्रम capture and preview */
अटल काष्ठा hackrf_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CS8,
		.buffersize	= BULK_BUFFER_SIZE,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक NUM_FORMATS = ARRAY_SIZE(क्रमmats);

/* पूर्णांकermediate buffers with raw data from the USB device */
काष्ठा hackrf_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा hackrf_dev अणु
#घोषणा USB_STATE_URB_BUF                1 /* XXX: set manually */
#घोषणा RX_ON                            4
#घोषणा TX_ON                            5
#घोषणा RX_ADC_FREQUENCY                11
#घोषणा TX_DAC_FREQUENCY                12
#घोषणा RX_BANDWIDTH                    13
#घोषणा TX_BANDWIDTH                    14
#घोषणा RX_RF_FREQUENCY                 15
#घोषणा TX_RF_FREQUENCY                 16
#घोषणा RX_RF_GAIN                      17
#घोषणा TX_RF_GAIN                      18
#घोषणा RX_IF_GAIN                      19
#घोषणा RX_LNA_GAIN                     20
#घोषणा TX_LNA_GAIN                     21
	अचिन्हित दीर्घ flags;

	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा device *dev;
	काष्ठा usb_device *udev;
	काष्ठा video_device rx_vdev;
	काष्ठा video_device tx_vdev;
	काष्ठा v4l2_device v4l2_dev;

	/* videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue rx_vb2_queue;
	काष्ठा vb2_queue tx_vb2_queue;
	काष्ठा list_head rx_buffer_list;
	काष्ठा list_head tx_buffer_list;
	spinlock_t buffer_list_lock; /* Protects buffer_list */
	अचिन्हित पूर्णांक sequence;	     /* Buffer sequence counter */
	अचिन्हित पूर्णांक vb_full;        /* vb is full and packets dropped */
	अचिन्हित पूर्णांक vb_empty;       /* vb is empty and packets dropped */

	/* Note अगर taking both locks v4l2_lock must always be locked first! */
	काष्ठा mutex v4l2_lock;      /* Protects everything अन्यथा */
	काष्ठा mutex vb_queue_lock;  /* Protects vb_queue */

	काष्ठा urb     *urb_list[MAX_BULK_BUFS];
	पूर्णांक            buf_num;
	अचिन्हित दीर्घ  buf_size;
	u8             *buf_list[MAX_BULK_BUFS];
	dma_addr_t     dma_addr[MAX_BULK_BUFS];
	पूर्णांक            urbs_initialized;
	पूर्णांक            urbs_submitted;

	/* USB control message buffer */
	#घोषणा BUF_SIZE 24
	u8 buf[BUF_SIZE];

	/* Current configuration */
	अचिन्हित पूर्णांक f_adc;
	अचिन्हित पूर्णांक f_dac;
	अचिन्हित पूर्णांक f_rx;
	अचिन्हित पूर्णांक f_tx;
	u32 pixelक्रमmat;
	u32 buffersize;

	/* Controls */
	काष्ठा v4l2_ctrl_handler rx_ctrl_handler;
	काष्ठा v4l2_ctrl *rx_bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *rx_bandwidth;
	काष्ठा v4l2_ctrl *rx_rf_gain;
	काष्ठा v4l2_ctrl *rx_lna_gain;
	काष्ठा v4l2_ctrl *rx_अगर_gain;
	काष्ठा v4l2_ctrl_handler tx_ctrl_handler;
	काष्ठा v4l2_ctrl *tx_bandwidth_स्वतः;
	काष्ठा v4l2_ctrl *tx_bandwidth;
	काष्ठा v4l2_ctrl *tx_rf_gain;
	काष्ठा v4l2_ctrl *tx_lna_gain;

	/* Sample rate calc */
	अचिन्हित दीर्घ jअगरfies_next;
	अचिन्हित पूर्णांक sample;
	अचिन्हित पूर्णांक sample_measured;
पूर्ण;

#घोषणा hackrf_dbg_usb_control_msg(_dev, _r, _t, _v, _i, _b, _l) अणु \
	अक्षर *_direction; \
	अगर (_t & USB_सूची_IN) \
		_direction = "<<<"; \
	अन्यथा \
		_direction = ">>>"; \
	dev_dbg(_dev, "%02x %02x %02x %02x %02x %02x %02x %02x %s %*ph\n", \
			_t, _r, _v & 0xff, _v >> 8, _i & 0xff, \
			_i >> 8, _l & 0xff, _l >> 8, _direction, _l, _b); \
पूर्ण

/* execute firmware command */
अटल पूर्णांक hackrf_ctrl_msg(काष्ठा hackrf_dev *dev, u8 request, u16 value,
		u16 index, u8 *data, u16 size)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	u8 requesttype;

	चयन (request) अणु
	हाल CMD_SET_TRANSCEIVER_MODE:
	हाल CMD_SET_FREQ:
	हाल CMD_AMP_ENABLE:
	हाल CMD_SAMPLE_RATE_SET:
	हाल CMD_BASEBAND_FILTER_BANDWIDTH_SET:
		pipe = usb_sndctrlpipe(dev->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_सूची_OUT);
		अवरोध;
	हाल CMD_BOARD_ID_READ:
	हाल CMD_VERSION_STRING_READ:
	हाल CMD_SET_LNA_GAIN:
	हाल CMD_SET_VGA_GAIN:
	हाल CMD_SET_TXVGA_GAIN:
		pipe = usb_rcvctrlpipe(dev->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_सूची_IN);
		अवरोध;
	शेष:
		dev_err(dev->dev, "Unknown command %02x\n", request);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* ग_लिखो request */
	अगर (!(requesttype & USB_सूची_IN))
		स_नकल(dev->buf, data, size);

	ret = usb_control_msg(dev->udev, pipe, request, requesttype, value,
			index, dev->buf, size, 1000);
	hackrf_dbg_usb_control_msg(dev->dev, request, requesttype, value,
			index, dev->buf, size);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "usb_control_msg() failed %d request %02x\n",
				ret, request);
		जाओ err;
	पूर्ण

	/* पढ़ो request */
	अगर (requesttype & USB_सूची_IN)
		स_नकल(data, dev->buf, size);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_set_params(काष्ठा hackrf_dev *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक ret, i;
	u8 buf[8], u8पंचांगp;
	अचिन्हित पूर्णांक uiपंचांगp, uiपंचांगp1, uiपंचांगp2;
	स्थिर bool rx = test_bit(RX_ON, &dev->flags);
	स्थिर bool tx = test_bit(TX_ON, &dev->flags);
	अटल स्थिर काष्ठा अणु
		u32 freq;
	पूर्ण bandwidth_lut[] = अणु
		अणु 1750000पूर्ण, /*  1.75 MHz */
		अणु 2500000पूर्ण, /*  2.5  MHz */
		अणु 3500000पूर्ण, /*  3.5  MHz */
		अणु 5000000पूर्ण, /*  5    MHz */
		अणु 5500000पूर्ण, /*  5.5  MHz */
		अणु 6000000पूर्ण, /*  6    MHz */
		अणु 7000000पूर्ण, /*  7    MHz */
		अणु 8000000पूर्ण, /*  8    MHz */
		अणु 9000000पूर्ण, /*  9    MHz */
		अणु10000000पूर्ण, /* 10    MHz */
		अणु12000000पूर्ण, /* 12    MHz */
		अणु14000000पूर्ण, /* 14    MHz */
		अणु15000000पूर्ण, /* 15    MHz */
		अणु20000000पूर्ण, /* 20    MHz */
		अणु24000000पूर्ण, /* 24    MHz */
		अणु28000000पूर्ण, /* 28    MHz */
	पूर्ण;

	अगर (!rx && !tx) अणु
		dev_dbg(&पूर्णांकf->dev, "device is sleeping\n");
		वापस 0;
	पूर्ण

	/* ADC / DAC frequency */
	अगर (rx && test_and_clear_bit(RX_ADC_FREQUENCY, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "RX ADC frequency=%u Hz\n", dev->f_adc);
		uiपंचांगp1 = dev->f_adc;
		uiपंचांगp2 = 1;
		set_bit(TX_DAC_FREQUENCY, &dev->flags);
	पूर्ण अन्यथा अगर (tx && test_and_clear_bit(TX_DAC_FREQUENCY, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "TX DAC frequency=%u Hz\n", dev->f_dac);
		uiपंचांगp1 = dev->f_dac;
		uiपंचांगp2 = 1;
		set_bit(RX_ADC_FREQUENCY, &dev->flags);
	पूर्ण अन्यथा अणु
		uiपंचांगp1 = uiपंचांगp2 = 0;
	पूर्ण
	अगर (uiपंचांगp1 || uiपंचांगp2) अणु
		buf[0] = (uiपंचांगp1 >>  0) & 0xff;
		buf[1] = (uiपंचांगp1 >>  8) & 0xff;
		buf[2] = (uiपंचांगp1 >> 16) & 0xff;
		buf[3] = (uiपंचांगp1 >> 24) & 0xff;
		buf[4] = (uiपंचांगp2 >>  0) & 0xff;
		buf[5] = (uiपंचांगp2 >>  8) & 0xff;
		buf[6] = (uiपंचांगp2 >> 16) & 0xff;
		buf[7] = (uiपंचांगp2 >> 24) & 0xff;
		ret = hackrf_ctrl_msg(dev, CMD_SAMPLE_RATE_SET, 0, 0, buf, 8);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* bandwidth */
	अगर (rx && test_and_clear_bit(RX_BANDWIDTH, &dev->flags)) अणु
		अगर (dev->rx_bandwidth_स्वतः->val == true)
			uiपंचांगp = dev->f_adc;
		अन्यथा
			uiपंचांगp = dev->rx_bandwidth->val;

		क्रम (i = 0; i < ARRAY_SIZE(bandwidth_lut); i++) अणु
			अगर (uiपंचांगp <= bandwidth_lut[i].freq) अणु
				uiपंचांगp = bandwidth_lut[i].freq;
				अवरोध;
			पूर्ण
		पूर्ण
		dev->rx_bandwidth->val = uiपंचांगp;
		dev->rx_bandwidth->cur.val = uiपंचांगp;
		dev_dbg(&पूर्णांकf->dev, "RX bandwidth selected=%u\n", uiपंचांगp);
		set_bit(TX_BANDWIDTH, &dev->flags);
	पूर्ण अन्यथा अगर (tx && test_and_clear_bit(TX_BANDWIDTH, &dev->flags)) अणु
		अगर (dev->tx_bandwidth_स्वतः->val == true)
			uiपंचांगp = dev->f_dac;
		अन्यथा
			uiपंचांगp = dev->tx_bandwidth->val;

		क्रम (i = 0; i < ARRAY_SIZE(bandwidth_lut); i++) अणु
			अगर (uiपंचांगp <= bandwidth_lut[i].freq) अणु
				uiपंचांगp = bandwidth_lut[i].freq;
				अवरोध;
			पूर्ण
		पूर्ण
		dev->tx_bandwidth->val = uiपंचांगp;
		dev->tx_bandwidth->cur.val = uiपंचांगp;
		dev_dbg(&पूर्णांकf->dev, "TX bandwidth selected=%u\n", uiपंचांगp);
		set_bit(RX_BANDWIDTH, &dev->flags);
	पूर्ण अन्यथा अणु
		uiपंचांगp = 0;
	पूर्ण
	अगर (uiपंचांगp) अणु
		uiपंचांगp1 = uiपंचांगp2 = 0;
		uiपंचांगp1 |= ((uiपंचांगp >>  0) & 0xff) << 0;
		uiपंचांगp1 |= ((uiपंचांगp >>  8) & 0xff) << 8;
		uiपंचांगp2 |= ((uiपंचांगp >> 16) & 0xff) << 0;
		uiपंचांगp2 |= ((uiपंचांगp >> 24) & 0xff) << 8;
		ret = hackrf_ctrl_msg(dev, CMD_BASEBAND_FILTER_BANDWIDTH_SET,
				      uiपंचांगp1, uiपंचांगp2, शून्य, 0);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* RX / TX RF frequency */
	अगर (rx && test_and_clear_bit(RX_RF_FREQUENCY, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "RX RF frequency=%u Hz\n", dev->f_rx);
		uiपंचांगp1 = dev->f_rx / 1000000;
		uiपंचांगp2 = dev->f_rx % 1000000;
		set_bit(TX_RF_FREQUENCY, &dev->flags);
	पूर्ण अन्यथा अगर (tx && test_and_clear_bit(TX_RF_FREQUENCY, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "TX RF frequency=%u Hz\n", dev->f_tx);
		uiपंचांगp1 = dev->f_tx / 1000000;
		uiपंचांगp2 = dev->f_tx % 1000000;
		set_bit(RX_RF_FREQUENCY, &dev->flags);
	पूर्ण अन्यथा अणु
		uiपंचांगp1 = uiपंचांगp2 = 0;
	पूर्ण
	अगर (uiपंचांगp1 || uiपंचांगp2) अणु
		buf[0] = (uiपंचांगp1 >>  0) & 0xff;
		buf[1] = (uiपंचांगp1 >>  8) & 0xff;
		buf[2] = (uiपंचांगp1 >> 16) & 0xff;
		buf[3] = (uiपंचांगp1 >> 24) & 0xff;
		buf[4] = (uiपंचांगp2 >>  0) & 0xff;
		buf[5] = (uiपंचांगp2 >>  8) & 0xff;
		buf[6] = (uiपंचांगp2 >> 16) & 0xff;
		buf[7] = (uiपंचांगp2 >> 24) & 0xff;
		ret = hackrf_ctrl_msg(dev, CMD_SET_FREQ, 0, 0, buf, 8);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* RX RF gain */
	अगर (rx && test_and_clear_bit(RX_RF_GAIN, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "RX RF gain val=%d->%d\n",
			dev->rx_rf_gain->cur.val, dev->rx_rf_gain->val);

		u8पंचांगp = (dev->rx_rf_gain->val) ? 1 : 0;
		ret = hackrf_ctrl_msg(dev, CMD_AMP_ENABLE, u8पंचांगp, 0, शून्य, 0);
		अगर (ret)
			जाओ err;
		set_bit(TX_RF_GAIN, &dev->flags);
	पूर्ण

	/* TX RF gain */
	अगर (tx && test_and_clear_bit(TX_RF_GAIN, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "TX RF gain val=%d->%d\n",
			dev->tx_rf_gain->cur.val, dev->tx_rf_gain->val);

		u8पंचांगp = (dev->tx_rf_gain->val) ? 1 : 0;
		ret = hackrf_ctrl_msg(dev, CMD_AMP_ENABLE, u8पंचांगp, 0, शून्य, 0);
		अगर (ret)
			जाओ err;
		set_bit(RX_RF_GAIN, &dev->flags);
	पूर्ण

	/* RX LNA gain */
	अगर (rx && test_and_clear_bit(RX_LNA_GAIN, &dev->flags)) अणु
		dev_dbg(dev->dev, "RX LNA gain val=%d->%d\n",
			dev->rx_lna_gain->cur.val, dev->rx_lna_gain->val);

		ret = hackrf_ctrl_msg(dev, CMD_SET_LNA_GAIN, 0,
				      dev->rx_lna_gain->val, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* RX IF gain */
	अगर (rx && test_and_clear_bit(RX_IF_GAIN, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "IF gain val=%d->%d\n",
			dev->rx_अगर_gain->cur.val, dev->rx_अगर_gain->val);

		ret = hackrf_ctrl_msg(dev, CMD_SET_VGA_GAIN, 0,
				      dev->rx_अगर_gain->val, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* TX LNA gain */
	अगर (tx && test_and_clear_bit(TX_LNA_GAIN, &dev->flags)) अणु
		dev_dbg(&पूर्णांकf->dev, "TX LNA gain val=%d->%d\n",
			dev->tx_lna_gain->cur.val, dev->tx_lna_gain->val);

		ret = hackrf_ctrl_msg(dev, CMD_SET_TXVGA_GAIN, 0,
				      dev->tx_lna_gain->val, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/* Private functions */
अटल काष्ठा hackrf_buffer *hackrf_get_next_buffer(काष्ठा hackrf_dev *dev,
						    काष्ठा list_head *buffer_list)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hackrf_buffer *buffer = शून्य;

	spin_lock_irqsave(&dev->buffer_list_lock, flags);
	अगर (list_empty(buffer_list))
		जाओ leave;

	buffer = list_entry(buffer_list->next, काष्ठा hackrf_buffer, list);
	list_del(&buffer->list);
leave:
	spin_unlock_irqrestore(&dev->buffer_list_lock, flags);
	वापस buffer;
पूर्ण

अटल व्योम hackrf_copy_stream(काष्ठा hackrf_dev *dev, व्योम *dst, व्योम *src,
			       अचिन्हित पूर्णांक src_len)
अणु
	स_नकल(dst, src, src_len);

	/* calculate sample rate and output it in 10 seconds पूर्णांकervals */
	अगर (unlikely(समय_is_beक्रमe_jअगरfies(dev->jअगरfies_next))) अणु
		#घोषणा MSECS 10000UL
		अचिन्हित पूर्णांक msecs = jअगरfies_to_msecs(jअगरfies -
				dev->jअगरfies_next + msecs_to_jअगरfies(MSECS));
		अचिन्हित पूर्णांक samples = dev->sample - dev->sample_measured;

		dev->jअगरfies_next = jअगरfies + msecs_to_jअगरfies(MSECS);
		dev->sample_measured = dev->sample;
		dev_dbg(dev->dev, "slen=%u samples=%u msecs=%u sample rate=%lu\n",
				src_len, samples, msecs,
				samples * 1000UL / msecs);
	पूर्ण

	/* total number of samples */
	dev->sample += src_len / 2;
पूर्ण

/*
 * This माला_लो called क्रम the bulk stream pipe. This is करोne in पूर्णांकerrupt
 * समय, so it has to be fast, not crash, and not stall. Neat.
 */
अटल व्योम hackrf_urb_complete_in(काष्ठा urb *urb)
अणु
	काष्ठा hackrf_dev *dev = urb->context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	काष्ठा hackrf_buffer *buffer;
	अचिन्हित पूर्णांक len;

	dev_dbg_ratelimited(&पूर्णांकf->dev, "status=%d length=%u/%u\n", urb->status,
			    urb->actual_length, urb->transfer_buffer_length);

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:            /* error */
		dev_err_ratelimited(&पूर्णांकf->dev, "URB failed %d\n", urb->status);
		जाओ निकास_usb_submit_urb;
	पूर्ण

	/* get buffer to ग_लिखो */
	buffer = hackrf_get_next_buffer(dev, &dev->rx_buffer_list);
	अगर (unlikely(buffer == शून्य)) अणु
		dev->vb_full++;
		dev_notice_ratelimited(&पूर्णांकf->dev,
				       "buffer is full - %u packets dropped\n",
				       dev->vb_full);
		जाओ निकास_usb_submit_urb;
	पूर्ण

	len = min_t(अचिन्हित दीर्घ, vb2_plane_size(&buffer->vb.vb2_buf, 0),
		    urb->actual_length);
	hackrf_copy_stream(dev, vb2_plane_vaddr(&buffer->vb.vb2_buf, 0),
		    urb->transfer_buffer, len);
	vb2_set_plane_payload(&buffer->vb.vb2_buf, 0, len);
	buffer->vb.sequence = dev->sequence++;
	buffer->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&buffer->vb.vb2_buf, VB2_BUF_STATE_DONE);
निकास_usb_submit_urb:
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम hackrf_urb_complete_out(काष्ठा urb *urb)
अणु
	काष्ठा hackrf_dev *dev = urb->context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	काष्ठा hackrf_buffer *buffer;
	अचिन्हित पूर्णांक len;

	dev_dbg_ratelimited(&पूर्णांकf->dev, "status=%d length=%u/%u\n", urb->status,
			    urb->actual_length, urb->transfer_buffer_length);

	चयन (urb->status) अणु
	हाल 0:             /* success */
	हाल -ETIMEDOUT:    /* NAK */
		अवरोध;
	हाल -ECONNRESET:   /* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:            /* error */
		dev_err_ratelimited(&पूर्णांकf->dev, "URB failed %d\n", urb->status);
	पूर्ण

	/* get buffer to पढ़ो */
	buffer = hackrf_get_next_buffer(dev, &dev->tx_buffer_list);
	अगर (unlikely(buffer == शून्य)) अणु
		dev->vb_empty++;
		dev_notice_ratelimited(&पूर्णांकf->dev,
				       "buffer is empty - %u packets dropped\n",
				       dev->vb_empty);
		urb->actual_length = 0;
		जाओ निकास_usb_submit_urb;
	पूर्ण

	len = min_t(अचिन्हित दीर्घ, urb->transfer_buffer_length,
		    vb2_get_plane_payload(&buffer->vb.vb2_buf, 0));
	hackrf_copy_stream(dev, urb->transfer_buffer,
			   vb2_plane_vaddr(&buffer->vb.vb2_buf, 0), len);
	urb->actual_length = len;
	buffer->vb.sequence = dev->sequence++;
	buffer->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&buffer->vb.vb2_buf, VB2_BUF_STATE_DONE);
निकास_usb_submit_urb:
	usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक hackrf_समाप्त_urbs(काष्ठा hackrf_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = dev->urbs_submitted - 1; i >= 0; i--) अणु
		dev_dbg(dev->dev, "kill urb=%d\n", i);
		/* stop the URB */
		usb_समाप्त_urb(dev->urb_list[i]);
	पूर्ण
	dev->urbs_submitted = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_submit_urbs(काष्ठा hackrf_dev *dev)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < dev->urbs_initialized; i++) अणु
		dev_dbg(dev->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(dev->urb_list[i], GFP_KERNEL);
		अगर (ret) अणु
			dev_err(dev->dev, "Could not submit URB no. %d - get them all back\n",
					i);
			hackrf_समाप्त_urbs(dev);
			वापस ret;
		पूर्ण
		dev->urbs_submitted++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_मुक्त_stream_bufs(काष्ठा hackrf_dev *dev)
अणु
	अगर (dev->flags & USB_STATE_URB_BUF) अणु
		जबतक (dev->buf_num) अणु
			dev->buf_num--;
			dev_dbg(dev->dev, "free buf=%d\n", dev->buf_num);
			usb_मुक्त_coherent(dev->udev, dev->buf_size,
					  dev->buf_list[dev->buf_num],
					  dev->dma_addr[dev->buf_num]);
		पूर्ण
	पूर्ण
	dev->flags &= ~USB_STATE_URB_BUF;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_alloc_stream_bufs(काष्ठा hackrf_dev *dev)
अणु
	dev->buf_num = 0;
	dev->buf_size = BULK_BUFFER_SIZE;

	dev_dbg(dev->dev, "all in all I will use %u bytes for streaming\n",
			MAX_BULK_BUFS * BULK_BUFFER_SIZE);

	क्रम (dev->buf_num = 0; dev->buf_num < MAX_BULK_BUFS; dev->buf_num++) अणु
		dev->buf_list[dev->buf_num] = usb_alloc_coherent(dev->udev,
				BULK_BUFFER_SIZE, GFP_KERNEL,
				&dev->dma_addr[dev->buf_num]);
		अगर (!dev->buf_list[dev->buf_num]) अणु
			dev_dbg(dev->dev, "alloc buf=%d failed\n",
					dev->buf_num);
			hackrf_मुक्त_stream_bufs(dev);
			वापस -ENOMEM;
		पूर्ण

		dev_dbg(dev->dev, "alloc buf=%d %p (dma %llu)\n", dev->buf_num,
				dev->buf_list[dev->buf_num],
				(दीर्घ दीर्घ)dev->dma_addr[dev->buf_num]);
		dev->flags |= USB_STATE_URB_BUF;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_मुक्त_urbs(काष्ठा hackrf_dev *dev)
अणु
	पूर्णांक i;

	hackrf_समाप्त_urbs(dev);

	क्रम (i = dev->urbs_initialized - 1; i >= 0; i--) अणु
		अगर (dev->urb_list[i]) अणु
			dev_dbg(dev->dev, "free urb=%d\n", i);
			/* मुक्त the URBs */
			usb_मुक्त_urb(dev->urb_list[i]);
		पूर्ण
	पूर्ण
	dev->urbs_initialized = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_alloc_urbs(काष्ठा hackrf_dev *dev, bool rcv)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक pipe;
	usb_complete_t complete;

	अगर (rcv) अणु
		pipe = usb_rcvbulkpipe(dev->udev, 0x81);
		complete = &hackrf_urb_complete_in;
	पूर्ण अन्यथा अणु
		pipe = usb_sndbulkpipe(dev->udev, 0x02);
		complete = &hackrf_urb_complete_out;
	पूर्ण

	/* allocate the URBs */
	क्रम (i = 0; i < MAX_BULK_BUFS; i++) अणु
		dev_dbg(dev->dev, "alloc urb=%d\n", i);
		dev->urb_list[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dev->urb_list[i]) अणु
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(dev->urb_list[j]);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_bulk_urb(dev->urb_list[i],
				dev->udev,
				pipe,
				dev->buf_list[i],
				BULK_BUFFER_SIZE,
				complete, dev);

		dev->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		dev->urb_list[i]->transfer_dma = dev->dma_addr[i];
		dev->urbs_initialized++;
	पूर्ण

	वापस 0;
पूर्ण

/* The user yanked out the cable... */
अटल व्योम hackrf_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा hackrf_dev *dev = container_of(v, काष्ठा hackrf_dev, v4l2_dev);

	dev_dbg(dev->dev, "\n");

	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	dev->udev = शून्य;
	v4l2_device_disconnect(&dev->v4l2_dev);
	video_unरेजिस्टर_device(&dev->tx_vdev);
	video_unरेजिस्टर_device(&dev->rx_vdev);
	mutex_unlock(&dev->v4l2_lock);
	mutex_unlock(&dev->vb_queue_lock);

	v4l2_device_put(&dev->v4l2_dev);
पूर्ण

/* Videobuf2 operations */
अटल व्योम hackrf_वापस_all_buffers(काष्ठा vb2_queue *vq,
				      क्रमागत vb2_buffer_state state)
अणु
	काष्ठा hackrf_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	काष्ठा hackrf_buffer *buffer, *node;
	काष्ठा list_head *buffer_list;
	अचिन्हित दीर्घ flags;

	dev_dbg(&पूर्णांकf->dev, "\n");

	अगर (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE)
		buffer_list = &dev->rx_buffer_list;
	अन्यथा
		buffer_list = &dev->tx_buffer_list;

	spin_lock_irqsave(&dev->buffer_list_lock, flags);
	list_क्रम_each_entry_safe(buffer, node, buffer_list, list) अणु
		dev_dbg(&पूर्णांकf->dev, "list_for_each_entry_safe\n");
		vb2_buffer_करोne(&buffer->vb.vb2_buf, state);
		list_del(&buffer->list);
	पूर्ण
	spin_unlock_irqrestore(&dev->buffer_list_lock, flags);
पूर्ण

अटल पूर्णांक hackrf_queue_setup(काष्ठा vb2_queue *vq,
		अचिन्हित पूर्णांक *nbuffers,
		अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा hackrf_dev *dev = vb2_get_drv_priv(vq);

	dev_dbg(dev->dev, "nbuffers=%d\n", *nbuffers);

	/* Need at least 8 buffers */
	अगर (vq->num_buffers + *nbuffers < 8)
		*nbuffers = 8 - vq->num_buffers;
	*nplanes = 1;
	sizes[0] = PAGE_ALIGN(dev->buffersize);

	dev_dbg(dev->dev, "nbuffers=%d sizes[0]=%d\n", *nbuffers, sizes[0]);
	वापस 0;
पूर्ण

अटल व्योम hackrf_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *vq = vb->vb2_queue;
	काष्ठा hackrf_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा hackrf_buffer *buffer = container_of(vbuf, काष्ठा hackrf_buffer, vb);
	काष्ठा list_head *buffer_list;
	अचिन्हित दीर्घ flags;

	dev_dbg_ratelimited(&dev->पूर्णांकf->dev, "\n");

	अगर (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE)
		buffer_list = &dev->rx_buffer_list;
	अन्यथा
		buffer_list = &dev->tx_buffer_list;

	spin_lock_irqsave(&dev->buffer_list_lock, flags);
	list_add_tail(&buffer->list, buffer_list);
	spin_unlock_irqrestore(&dev->buffer_list_lock, flags);
पूर्ण

अटल पूर्णांक hackrf_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा hackrf_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mode;

	dev_dbg(&पूर्णांकf->dev, "count=%i\n", count);

	mutex_lock(&dev->v4l2_lock);

	/* Allow only RX or TX, not both same समय */
	अगर (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE) अणु
		अगर (test_bit(TX_ON, &dev->flags)) अणु
			ret = -EBUSY;
			जाओ err_hackrf_वापस_all_buffers;
		पूर्ण

		mode = 1;
		set_bit(RX_ON, &dev->flags);
	पूर्ण अन्यथा अणु
		अगर (test_bit(RX_ON, &dev->flags)) अणु
			ret = -EBUSY;
			जाओ err_hackrf_वापस_all_buffers;
		पूर्ण

		mode = 2;
		set_bit(TX_ON, &dev->flags);
	पूर्ण

	dev->sequence = 0;

	ret = hackrf_alloc_stream_bufs(dev);
	अगर (ret)
		जाओ err;

	ret = hackrf_alloc_urbs(dev, (mode == 1));
	अगर (ret)
		जाओ err;

	ret = hackrf_submit_urbs(dev);
	अगर (ret)
		जाओ err;

	ret = hackrf_set_params(dev);
	अगर (ret)
		जाओ err;

	/* start hardware streaming */
	ret = hackrf_ctrl_msg(dev, CMD_SET_TRANSCEIVER_MODE, mode, 0, शून्य, 0);
	अगर (ret)
		जाओ err;

	mutex_unlock(&dev->v4l2_lock);

	वापस 0;
err:
	hackrf_समाप्त_urbs(dev);
	hackrf_मुक्त_urbs(dev);
	hackrf_मुक्त_stream_bufs(dev);
	clear_bit(RX_ON, &dev->flags);
	clear_bit(TX_ON, &dev->flags);
err_hackrf_वापस_all_buffers:
	hackrf_वापस_all_buffers(vq, VB2_BUF_STATE_QUEUED);
	mutex_unlock(&dev->v4l2_lock);
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम hackrf_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा hackrf_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	/* stop hardware streaming */
	hackrf_ctrl_msg(dev, CMD_SET_TRANSCEIVER_MODE, 0, 0, शून्य, 0);

	hackrf_समाप्त_urbs(dev);
	hackrf_मुक्त_urbs(dev);
	hackrf_मुक्त_stream_bufs(dev);

	hackrf_वापस_all_buffers(vq, VB2_BUF_STATE_ERROR);

	अगर (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE)
		clear_bit(RX_ON, &dev->flags);
	अन्यथा
		clear_bit(TX_ON, &dev->flags);

	mutex_unlock(&dev->v4l2_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops hackrf_vb2_ops = अणु
	.queue_setup            = hackrf_queue_setup,
	.buf_queue              = hackrf_buf_queue,
	.start_streaming        = hackrf_start_streaming,
	.stop_streaming         = hackrf_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक hackrf_querycap(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_capability *cap)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;

	dev_dbg(&पूर्णांकf->dev, "\n");

	cap->capabilities = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
			    V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR |
			    V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
			    V4L2_CAP_DEVICE_CAPS;
	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, dev->rx_vdev.name, माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_s_fmt_sdr(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा vb2_queue *q;
	पूर्णांक i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
			(अक्षर *)&f->fmt.sdr.pixelक्रमmat);

	अगर (vdev->vfl_dir == VFL_सूची_RX)
		q = &dev->rx_vb2_queue;
	अन्यथा
		q = &dev->tx_vb2_queue;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (f->fmt.sdr.pixelक्रमmat == क्रमmats[i].pixelक्रमmat) अणु
			dev->pixelक्रमmat = क्रमmats[i].pixelक्रमmat;
			dev->buffersize = क्रमmats[i].buffersize;
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	dev->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->buffersize = क्रमmats[0].buffersize;
	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_g_fmt_sdr(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
			(अक्षर *)&dev->pixelक्रमmat);

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	f->fmt.sdr.pixelक्रमmat = dev->pixelक्रमmat;
	f->fmt.sdr.buffersize = dev->buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_try_fmt_sdr(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	पूर्णांक i;

	dev_dbg(dev->dev, "pixelformat fourcc %4.4s\n",
			(अक्षर *)&f->fmt.sdr.pixelक्रमmat);

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < NUM_FORMATS; i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_क्रमागत_fmt_sdr(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "index=%d\n", f->index);

	अगर (f->index >= NUM_FORMATS)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक hackrf_s_tuner(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	अगर (v->index == 0)
		ret = 0;
	अन्यथा अगर (v->index == 1)
		ret = 0;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *v)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "index=%d\n", v->index);

	अगर (v->index == 0) अणु
		strscpy(v->name, "HackRF ADC", माप(v->name));
		v->type = V4L2_TUNER_SDR;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow  = bands_adc_dac[0].rangelow;
		v->rangehigh = bands_adc_dac[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अगर (v->index == 1) अणु
		strscpy(v->name, "HackRF RF", माप(v->name));
		v->type = V4L2_TUNER_RF;
		v->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		v->rangelow  = bands_rx_tx[0].rangelow;
		v->rangehigh = bands_rx_tx[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_s_modulator(काष्ठा file *file, व्योम *fh,
			      स्थिर काष्ठा v4l2_modulator *a)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);

	dev_dbg(dev->dev, "index=%d\n", a->index);

	वापस a->index > 1 ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक hackrf_g_modulator(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_modulator *a)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "index=%d\n", a->index);

	अगर (a->index == 0) अणु
		strscpy(a->name, "HackRF DAC", माप(a->name));
		a->type = V4L2_TUNER_SDR;
		a->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		a->rangelow  = bands_adc_dac[0].rangelow;
		a->rangehigh = bands_adc_dac[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अगर (a->index == 1) अणु
		strscpy(a->name, "HackRF RF", माप(a->name));
		a->type = V4L2_TUNER_RF;
		a->capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		a->rangelow  = bands_rx_tx[0].rangelow;
		a->rangehigh = bands_rx_tx[0].rangehigh;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_s_frequency(काष्ठा file *file, व्योम *priv,
		स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक ret;
	अचिन्हित पूर्णांक uiपंचांगp;

	dev_dbg(&पूर्णांकf->dev, "tuner=%d type=%d frequency=%u\n",
			f->tuner, f->type, f->frequency);

	अगर (f->tuner == 0) अणु
		uiपंचांगp = clamp(f->frequency, bands_adc_dac[0].rangelow,
			      bands_adc_dac[0].rangehigh);
		अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
			dev->f_adc = uiपंचांगp;
			set_bit(RX_ADC_FREQUENCY, &dev->flags);
		पूर्ण अन्यथा अणु
			dev->f_dac = uiपंचांगp;
			set_bit(TX_DAC_FREQUENCY, &dev->flags);
		पूर्ण
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		uiपंचांगp = clamp(f->frequency, bands_rx_tx[0].rangelow,
			      bands_rx_tx[0].rangehigh);
		अगर (vdev->vfl_dir == VFL_सूची_RX) अणु
			dev->f_rx = uiपंचांगp;
			set_bit(RX_RF_FREQUENCY, &dev->flags);
		पूर्ण अन्यथा अणु
			dev->f_tx = uiपंचांगp;
			set_bit(TX_RF_FREQUENCY, &dev->flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = hackrf_set_params(dev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_g_frequency(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency *f)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	काष्ठा video_device *vdev = video_devdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	अगर (f->tuner == 0) अणु
		f->type = V4L2_TUNER_SDR;
		अगर (vdev->vfl_dir == VFL_सूची_RX)
			f->frequency = dev->f_adc;
		अन्यथा
			f->frequency = dev->f_dac;
	पूर्ण अन्यथा अगर (f->tuner == 1) अणु
		f->type = V4L2_TUNER_RF;
		अगर (vdev->vfl_dir == VFL_सूची_RX)
			f->frequency = dev->f_rx;
		अन्यथा
			f->frequency = dev->f_tx;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा hackrf_dev *dev = video_drvdata(file);
	पूर्णांक ret;

	dev_dbg(dev->dev, "tuner=%d type=%d index=%d\n",
			band->tuner, band->type, band->index);

	अगर (band->tuner == 0) अणु
		अगर (band->index >= ARRAY_SIZE(bands_adc_dac)) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			*band = bands_adc_dac[band->index];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (band->tuner == 1) अणु
		अगर (band->index >= ARRAY_SIZE(bands_rx_tx)) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			*band = bands_rx_tx[band->index];
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops hackrf_ioctl_ops = अणु
	.vidioc_querycap          = hackrf_querycap,

	.vidioc_s_fmt_sdr_cap     = hackrf_s_fmt_sdr,
	.vidioc_g_fmt_sdr_cap     = hackrf_g_fmt_sdr,
	.vidioc_क्रमागत_fmt_sdr_cap  = hackrf_क्रमागत_fmt_sdr,
	.vidioc_try_fmt_sdr_cap   = hackrf_try_fmt_sdr,

	.vidioc_s_fmt_sdr_out     = hackrf_s_fmt_sdr,
	.vidioc_g_fmt_sdr_out     = hackrf_g_fmt_sdr,
	.vidioc_क्रमागत_fmt_sdr_out  = hackrf_क्रमागत_fmt_sdr,
	.vidioc_try_fmt_sdr_out   = hackrf_try_fmt_sdr,

	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_create_bufs       = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf       = vb2_ioctl_prepare_buf,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,
	.vidioc_expbuf            = vb2_ioctl_expbuf,

	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,

	.vidioc_s_tuner           = hackrf_s_tuner,
	.vidioc_g_tuner           = hackrf_g_tuner,

	.vidioc_s_modulator       = hackrf_s_modulator,
	.vidioc_g_modulator       = hackrf_g_modulator,

	.vidioc_s_frequency       = hackrf_s_frequency,
	.vidioc_g_frequency       = hackrf_g_frequency,
	.vidioc_क्रमागत_freq_bands   = hackrf_क्रमागत_freq_bands,

	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status        = v4l2_ctrl_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations hackrf_fops = अणु
	.owner                    = THIS_MODULE,
	.खोलो                     = v4l2_fh_खोलो,
	.release                  = vb2_fop_release,
	.पढ़ो                     = vb2_fop_पढ़ो,
	.ग_लिखो                    = vb2_fop_ग_लिखो,
	.poll                     = vb2_fop_poll,
	.mmap                     = vb2_fop_mmap,
	.unlocked_ioctl           = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा video_device hackrf_ढाँचा = अणु
	.name                     = "HackRF One",
	.release                  = video_device_release_empty,
	.fops                     = &hackrf_fops,
	.ioctl_ops                = &hackrf_ioctl_ops,
पूर्ण;

अटल व्योम hackrf_video_release(काष्ठा v4l2_device *v)
अणु
	काष्ठा hackrf_dev *dev = container_of(v, काष्ठा hackrf_dev, v4l2_dev);

	dev_dbg(dev->dev, "\n");

	v4l2_ctrl_handler_मुक्त(&dev->rx_ctrl_handler);
	v4l2_ctrl_handler_मुक्त(&dev->tx_ctrl_handler);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक hackrf_s_ctrl_rx(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hackrf_dev *dev = container_of(ctrl->handler,
			काष्ठा hackrf_dev, rx_ctrl_handler);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		set_bit(RX_BANDWIDTH, &dev->flags);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_RF_GAIN:
		set_bit(RX_RF_GAIN, &dev->flags);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN:
		set_bit(RX_LNA_GAIN, &dev->flags);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_IF_GAIN:
		set_bit(RX_IF_GAIN, &dev->flags);
		अवरोध;
	शेष:
		dev_dbg(&पूर्णांकf->dev, "unknown ctrl: id=%d name=%s\n",
			ctrl->id, ctrl->name);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = hackrf_set_params(dev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hackrf_s_ctrl_tx(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा hackrf_dev *dev = container_of(ctrl->handler,
			काष्ठा hackrf_dev, tx_ctrl_handler);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_RF_TUNER_BANDWIDTH_AUTO:
	हाल V4L2_CID_RF_TUNER_BANDWIDTH:
		set_bit(TX_BANDWIDTH, &dev->flags);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_LNA_GAIN:
		set_bit(TX_LNA_GAIN, &dev->flags);
		अवरोध;
	हाल  V4L2_CID_RF_TUNER_RF_GAIN:
		set_bit(TX_RF_GAIN, &dev->flags);
		अवरोध;
	शेष:
		dev_dbg(&पूर्णांकf->dev, "unknown ctrl: id=%d name=%s\n",
			ctrl->id, ctrl->name);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = hackrf_set_params(dev);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops hackrf_ctrl_ops_rx = अणु
	.s_ctrl = hackrf_s_ctrl_rx,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops hackrf_ctrl_ops_tx = अणु
	.s_ctrl = hackrf_s_ctrl_tx,
पूर्ण;

अटल पूर्णांक hackrf_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा hackrf_dev *dev;
	पूर्णांक ret;
	u8 u8पंचांगp, buf[BUF_SIZE];

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mutex_init(&dev->v4l2_lock);
	mutex_init(&dev->vb_queue_lock);
	spin_lock_init(&dev->buffer_list_lock);
	INIT_LIST_HEAD(&dev->rx_buffer_list);
	INIT_LIST_HEAD(&dev->tx_buffer_list);
	dev->पूर्णांकf = पूर्णांकf;
	dev->dev = &पूर्णांकf->dev;
	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	dev->pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->buffersize = क्रमmats[0].buffersize;
	dev->f_adc = bands_adc_dac[0].rangelow;
	dev->f_dac = bands_adc_dac[0].rangelow;
	dev->f_rx = bands_rx_tx[0].rangelow;
	dev->f_tx = bands_rx_tx[0].rangelow;
	set_bit(RX_ADC_FREQUENCY, &dev->flags);
	set_bit(TX_DAC_FREQUENCY, &dev->flags);
	set_bit(RX_RF_FREQUENCY, &dev->flags);
	set_bit(TX_RF_FREQUENCY, &dev->flags);

	/* Detect device */
	ret = hackrf_ctrl_msg(dev, CMD_BOARD_ID_READ, 0, 0, &u8पंचांगp, 1);
	अगर (ret == 0)
		ret = hackrf_ctrl_msg(dev, CMD_VERSION_STRING_READ, 0, 0,
				buf, BUF_SIZE);
	अगर (ret) अणु
		dev_err(dev->dev, "Could not detect board\n");
		जाओ err_kमुक्त;
	पूर्ण

	buf[BUF_SIZE - 1] = '\0';
	dev_info(dev->dev, "Board ID: %02x\n", u8पंचांगp);
	dev_info(dev->dev, "Firmware version: %s\n", buf);

	/* Init vb2 queue काष्ठाure क्रम receiver */
	dev->rx_vb2_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	dev->rx_vb2_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF |
				     VB2_READ;
	dev->rx_vb2_queue.ops = &hackrf_vb2_ops;
	dev->rx_vb2_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	dev->rx_vb2_queue.drv_priv = dev;
	dev->rx_vb2_queue.buf_काष्ठा_size = माप(काष्ठा hackrf_buffer);
	dev->rx_vb2_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	ret = vb2_queue_init(&dev->rx_vb2_queue);
	अगर (ret) अणु
		dev_err(dev->dev, "Could not initialize rx vb2 queue\n");
		जाओ err_kमुक्त;
	पूर्ण

	/* Init vb2 queue काष्ठाure क्रम transmitter */
	dev->tx_vb2_queue.type = V4L2_BUF_TYPE_SDR_OUTPUT;
	dev->tx_vb2_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF |
				     VB2_WRITE;
	dev->tx_vb2_queue.ops = &hackrf_vb2_ops;
	dev->tx_vb2_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	dev->tx_vb2_queue.drv_priv = dev;
	dev->tx_vb2_queue.buf_काष्ठा_size = माप(काष्ठा hackrf_buffer);
	dev->tx_vb2_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	ret = vb2_queue_init(&dev->tx_vb2_queue);
	अगर (ret) अणु
		dev_err(dev->dev, "Could not initialize tx vb2 queue\n");
		जाओ err_kमुक्त;
	पूर्ण

	/* Register controls क्रम receiver */
	v4l2_ctrl_handler_init(&dev->rx_ctrl_handler, 5);
	dev->rx_bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->rx_ctrl_handler,
		&hackrf_ctrl_ops_rx, V4L2_CID_RF_TUNER_BANDWIDTH_AUTO,
		0, 1, 0, 1);
	dev->rx_bandwidth = v4l2_ctrl_new_std(&dev->rx_ctrl_handler,
		&hackrf_ctrl_ops_rx, V4L2_CID_RF_TUNER_BANDWIDTH,
		1750000, 28000000, 50000, 1750000);
	v4l2_ctrl_स्वतः_cluster(2, &dev->rx_bandwidth_स्वतः, 0, false);
	dev->rx_rf_gain = v4l2_ctrl_new_std(&dev->rx_ctrl_handler,
		&hackrf_ctrl_ops_rx, V4L2_CID_RF_TUNER_RF_GAIN, 0, 12, 12, 0);
	dev->rx_lna_gain = v4l2_ctrl_new_std(&dev->rx_ctrl_handler,
		&hackrf_ctrl_ops_rx, V4L2_CID_RF_TUNER_LNA_GAIN, 0, 40, 8, 0);
	dev->rx_अगर_gain = v4l2_ctrl_new_std(&dev->rx_ctrl_handler,
		&hackrf_ctrl_ops_rx, V4L2_CID_RF_TUNER_IF_GAIN, 0, 62, 2, 0);
	अगर (dev->rx_ctrl_handler.error) अणु
		ret = dev->rx_ctrl_handler.error;
		dev_err(dev->dev, "Could not initialize controls\n");
		जाओ err_v4l2_ctrl_handler_मुक्त_rx;
	पूर्ण
	v4l2_ctrl_grab(dev->rx_rf_gain, !hackrf_enable_rf_gain_ctrl);
	v4l2_ctrl_handler_setup(&dev->rx_ctrl_handler);

	/* Register controls क्रम transmitter */
	v4l2_ctrl_handler_init(&dev->tx_ctrl_handler, 4);
	dev->tx_bandwidth_स्वतः = v4l2_ctrl_new_std(&dev->tx_ctrl_handler,
		&hackrf_ctrl_ops_tx, V4L2_CID_RF_TUNER_BANDWIDTH_AUTO,
		0, 1, 0, 1);
	dev->tx_bandwidth = v4l2_ctrl_new_std(&dev->tx_ctrl_handler,
		&hackrf_ctrl_ops_tx, V4L2_CID_RF_TUNER_BANDWIDTH,
		1750000, 28000000, 50000, 1750000);
	v4l2_ctrl_स्वतः_cluster(2, &dev->tx_bandwidth_स्वतः, 0, false);
	dev->tx_lna_gain = v4l2_ctrl_new_std(&dev->tx_ctrl_handler,
		&hackrf_ctrl_ops_tx, V4L2_CID_RF_TUNER_LNA_GAIN, 0, 47, 1, 0);
	dev->tx_rf_gain = v4l2_ctrl_new_std(&dev->tx_ctrl_handler,
		&hackrf_ctrl_ops_tx, V4L2_CID_RF_TUNER_RF_GAIN, 0, 15, 15, 0);
	अगर (dev->tx_ctrl_handler.error) अणु
		ret = dev->tx_ctrl_handler.error;
		dev_err(dev->dev, "Could not initialize controls\n");
		जाओ err_v4l2_ctrl_handler_मुक्त_tx;
	पूर्ण
	v4l2_ctrl_grab(dev->tx_rf_gain, !hackrf_enable_rf_gain_ctrl);
	v4l2_ctrl_handler_setup(&dev->tx_ctrl_handler);

	/* Register the v4l2_device काष्ठाure */
	dev->v4l2_dev.release = hackrf_video_release;
	ret = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &dev->v4l2_dev);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to register v4l2-device (%d)\n", ret);
		जाओ err_v4l2_ctrl_handler_मुक्त_tx;
	पूर्ण

	/* Init video_device काष्ठाure क्रम receiver */
	dev->rx_vdev = hackrf_ढाँचा;
	dev->rx_vdev.queue = &dev->rx_vb2_queue;
	dev->rx_vdev.queue->lock = &dev->vb_queue_lock;
	dev->rx_vdev.v4l2_dev = &dev->v4l2_dev;
	dev->rx_vdev.ctrl_handler = &dev->rx_ctrl_handler;
	dev->rx_vdev.lock = &dev->v4l2_lock;
	dev->rx_vdev.vfl_dir = VFL_सूची_RX;
	dev->rx_vdev.device_caps = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
				   V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER;
	video_set_drvdata(&dev->rx_vdev, dev);
	ret = video_रेजिस्टर_device(&dev->rx_vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		dev_err(dev->dev,
			"Failed to register as video device (%d)\n", ret);
		जाओ err_v4l2_device_unरेजिस्टर;
	पूर्ण
	dev_info(dev->dev, "Registered as %s\n",
		 video_device_node_name(&dev->rx_vdev));

	/* Init video_device काष्ठाure क्रम transmitter */
	dev->tx_vdev = hackrf_ढाँचा;
	dev->tx_vdev.queue = &dev->tx_vb2_queue;
	dev->tx_vdev.queue->lock = &dev->vb_queue_lock;
	dev->tx_vdev.v4l2_dev = &dev->v4l2_dev;
	dev->tx_vdev.ctrl_handler = &dev->tx_ctrl_handler;
	dev->tx_vdev.lock = &dev->v4l2_lock;
	dev->tx_vdev.vfl_dir = VFL_सूची_TX;
	dev->tx_vdev.device_caps = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
				   V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR;
	video_set_drvdata(&dev->tx_vdev, dev);
	ret = video_रेजिस्टर_device(&dev->tx_vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		dev_err(dev->dev,
			"Failed to register as video device (%d)\n", ret);
		जाओ err_video_unरेजिस्टर_device_rx;
	पूर्ण
	dev_info(dev->dev, "Registered as %s\n",
		 video_device_node_name(&dev->tx_vdev));

	dev_notice(dev->dev, "SDR API is still slightly experimental and functionality changes may follow\n");
	वापस 0;
err_video_unरेजिस्टर_device_rx:
	video_unरेजिस्टर_device(&dev->rx_vdev);
err_v4l2_device_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
err_v4l2_ctrl_handler_मुक्त_tx:
	v4l2_ctrl_handler_मुक्त(&dev->tx_ctrl_handler);
err_v4l2_ctrl_handler_मुक्त_rx:
	v4l2_ctrl_handler_मुक्त(&dev->rx_ctrl_handler);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&पूर्णांकf->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

/* USB device ID list */
अटल स्थिर काष्ठा usb_device_id hackrf_id_table[] = अणु
	अणु USB_DEVICE(0x1d50, 0x6089) पूर्ण, /* HackRF One */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, hackrf_id_table);

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver hackrf_driver = अणु
	.name                     = KBUILD_MODNAME,
	.probe                    = hackrf_probe,
	.disconnect               = hackrf_disconnect,
	.id_table                 = hackrf_id_table,
पूर्ण;

module_usb_driver(hackrf_driver);

MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("HackRF");
MODULE_LICENSE("GPL");
