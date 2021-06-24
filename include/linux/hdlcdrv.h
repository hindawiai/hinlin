<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * hdlcdrv.h  -- HDLC packet radio network driver.
 * The Linux soundcard driver क्रम 1200 baud and 9600 baud packet radio
 * (C) 1996-1998 by Thomas Sailer, HB9JNX/AE4WA
 */
#अगर_अघोषित _HDLCDRV_H
#घोषणा _HDLCDRV_H


#समावेश <linux/netdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/spinlock.h>
#समावेश <uapi/linux/hdlcdrv.h>

#घोषणा HDLCDRV_MAGIC      0x5ac6e778
#घोषणा HDLCDRV_HDLCBUFFER  32 /* should be a घातer of 2 क्रम speed reasons */
#घोषणा HDLCDRV_BITBUFFER  256 /* should be a घातer of 2 क्रम speed reasons */
#अघोषित HDLCDRV_LOOPBACK  /* define क्रम HDLC debugging purposes */
#घोषणा HDLCDRV_DEBUG

/* maximum packet length, excluding CRC */
#घोषणा HDLCDRV_MAXFLEN             400	


काष्ठा hdlcdrv_hdlcbuffer अणु
	spinlock_t lock;
	अचिन्हित rd, wr;
	अचिन्हित लघु buf[HDLCDRV_HDLCBUFFER];
पूर्ण;

#अगर_घोषित HDLCDRV_DEBUG
काष्ठा hdlcdrv_bitbuffer अणु
	अचिन्हित पूर्णांक rd;
	अचिन्हित पूर्णांक wr;
	अचिन्हित पूर्णांक shreg;
	अचिन्हित अक्षर buffer[HDLCDRV_BITBUFFER];
पूर्ण;

अटल अंतरभूत व्योम hdlcdrv_add_bitbuffer(काष्ठा hdlcdrv_bitbuffer *buf, 
					 अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित अक्षर new;

	new = buf->shreg & 1;
	buf->shreg >>= 1;
	buf->shreg |= (!!bit) << 7;
	अगर (new) अणु
		buf->buffer[buf->wr] = buf->shreg;
		buf->wr = (buf->wr+1) % माप(buf->buffer);
		buf->shreg = 0x80;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hdlcdrv_add_bitbuffer_word(काष्ठा hdlcdrv_bitbuffer *buf, 
					      अचिन्हित पूर्णांक bits)
अणु
	buf->buffer[buf->wr] = bits & 0xff;
	buf->wr = (buf->wr+1) % माप(buf->buffer);
	buf->buffer[buf->wr] = (bits >> 8) & 0xff;
	buf->wr = (buf->wr+1) % माप(buf->buffer);

पूर्ण
#पूर्ण_अगर /* HDLCDRV_DEBUG */

/* -------------------------------------------------------------------- */
/*
 * Inक्रमmation that need to be kept क्रम each driver. 
 */

काष्ठा hdlcdrv_ops अणु
	/*
	 * first some inक्रमmations needed by the hdlcdrv routines
	 */
	स्थिर अक्षर *drvname;
	स्थिर अक्षर *drvinfo;
	/*
	 * the routines called by the hdlcdrv routines
	 */
	पूर्णांक (*खोलो)(काष्ठा net_device *);
	पूर्णांक (*बंद)(काष्ठा net_device *);
	पूर्णांक (*ioctl)(काष्ठा net_device *, काष्ठा अगरreq *, 
		     काष्ठा hdlcdrv_ioctl *, पूर्णांक);
पूर्ण;

काष्ठा hdlcdrv_state अणु
	पूर्णांक magic;
	पूर्णांक खोलोed;

	स्थिर काष्ठा hdlcdrv_ops *ops;

	काष्ठा अणु
		पूर्णांक bitrate;
	पूर्ण par;

	काष्ठा hdlcdrv_pttoutput अणु
		पूर्णांक dma2;
		पूर्णांक seriobase;
		पूर्णांक pariobase;
		पूर्णांक midiiobase;
		अचिन्हित पूर्णांक flags;
	पूर्ण ptt_out;

	काष्ठा hdlcdrv_channel_params ch_params;

	काष्ठा hdlcdrv_hdlcrx अणु
		काष्ठा hdlcdrv_hdlcbuffer hbuf;
		अचिन्हित दीर्घ in_hdlc_rx;
		/* 0 = sync hunt, != 0 receiving */
		पूर्णांक rx_state;	
		अचिन्हित पूर्णांक bitstream;
		अचिन्हित पूर्णांक bitbuf;
		पूर्णांक numbits;
		अचिन्हित अक्षर dcd;
		
		पूर्णांक len;
		अचिन्हित अक्षर *bp;
		अचिन्हित अक्षर buffer[HDLCDRV_MAXFLEN+2];
	पूर्ण hdlcrx;

	काष्ठा hdlcdrv_hdlctx अणु
		काष्ठा hdlcdrv_hdlcbuffer hbuf;
		अचिन्हित दीर्घ in_hdlc_tx;
		/*
		 * 0 = send flags
		 * 1 = send txtail (flags)
		 * 2 = send packet
		 */
		पूर्णांक tx_state;	
		पूर्णांक numflags;
		अचिन्हित पूर्णांक bitstream;
		अचिन्हित अक्षर ptt;
		पूर्णांक calibrate;
		पूर्णांक slotcnt;

		अचिन्हित पूर्णांक bitbuf;
		पूर्णांक numbits;
		
		पूर्णांक len;
		अचिन्हित अक्षर *bp;
		अचिन्हित अक्षर buffer[HDLCDRV_MAXFLEN+2];
	पूर्ण hdlctx;

#अगर_घोषित HDLCDRV_DEBUG
	काष्ठा hdlcdrv_bitbuffer bitbuf_channel;
	काष्ठा hdlcdrv_bitbuffer bitbuf_hdlc;
#पूर्ण_अगर /* HDLCDRV_DEBUG */

	पूर्णांक ptt_keyed;

	/* queued skb क्रम transmission */
	काष्ठा sk_buff *skb;
पूर्ण;


/* -------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक hdlcdrv_hbuf_full(काष्ठा hdlcdrv_hdlcbuffer *hb) 
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	
	spin_lock_irqsave(&hb->lock, flags);
	ret = !((HDLCDRV_HDLCBUFFER - 1 + hb->rd - hb->wr) % HDLCDRV_HDLCBUFFER);
	spin_unlock_irqrestore(&hb->lock, flags);
	वापस ret;
पूर्ण

/* -------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक hdlcdrv_hbuf_empty(काष्ठा hdlcdrv_hdlcbuffer *hb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	
	spin_lock_irqsave(&hb->lock, flags);
	ret = (hb->rd == hb->wr);
	spin_unlock_irqrestore(&hb->lock, flags);
	वापस ret;
पूर्ण

/* -------------------------------------------------------------------- */

अटल अंतरभूत अचिन्हित लघु hdlcdrv_hbuf_get(काष्ठा hdlcdrv_hdlcbuffer *hb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;
	अचिन्हित newr;

	spin_lock_irqsave(&hb->lock, flags);
	अगर (hb->rd == hb->wr)
		val = 0;
	अन्यथा अणु
		newr = (hb->rd+1) % HDLCDRV_HDLCBUFFER;
		val = hb->buf[hb->rd];
		hb->rd = newr;
	पूर्ण
	spin_unlock_irqrestore(&hb->lock, flags);
	वापस val;
पूर्ण

/* -------------------------------------------------------------------- */

अटल अंतरभूत व्योम hdlcdrv_hbuf_put(काष्ठा hdlcdrv_hdlcbuffer *hb, 
				    अचिन्हित लघु val)
अणु
	अचिन्हित newp;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&hb->lock, flags);
	newp = (hb->wr+1) % HDLCDRV_HDLCBUFFER;
	अगर (newp != hb->rd) अणु 
		hb->buf[hb->wr] = val & 0xffff;
		hb->wr = newp;
	पूर्ण
	spin_unlock_irqrestore(&hb->lock, flags);
पूर्ण

/* -------------------------------------------------------------------- */

अटल अंतरभूत व्योम hdlcdrv_putbits(काष्ठा hdlcdrv_state *s, अचिन्हित पूर्णांक bits)
अणु
	hdlcdrv_hbuf_put(&s->hdlcrx.hbuf, bits);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hdlcdrv_getbits(काष्ठा hdlcdrv_state *s)
अणु
	अचिन्हित पूर्णांक ret;

	अगर (hdlcdrv_hbuf_empty(&s->hdlctx.hbuf)) अणु
		अगर (s->hdlctx.calibrate > 0)
			s->hdlctx.calibrate--;
		अन्यथा
			s->hdlctx.ptt = 0;
		ret = 0;
	पूर्ण अन्यथा 
		ret = hdlcdrv_hbuf_get(&s->hdlctx.hbuf);
#अगर_घोषित HDLCDRV_LOOPBACK
	hdlcdrv_hbuf_put(&s->hdlcrx.hbuf, ret);
#पूर्ण_अगर /* HDLCDRV_LOOPBACK */
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hdlcdrv_channelbit(काष्ठा hdlcdrv_state *s, अचिन्हित पूर्णांक bit)
अणु
#अगर_घोषित HDLCDRV_DEBUG
	hdlcdrv_add_bitbuffer(&s->bitbuf_channel, bit);
#पूर्ण_अगर /* HDLCDRV_DEBUG */
पूर्ण

अटल अंतरभूत व्योम hdlcdrv_setdcd(काष्ठा hdlcdrv_state *s, पूर्णांक dcd)
अणु
	s->hdlcrx.dcd = !!dcd;
पूर्ण

अटल अंतरभूत पूर्णांक hdlcdrv_ptt(काष्ठा hdlcdrv_state *s)
अणु
	वापस s->hdlctx.ptt || (s->hdlctx.calibrate > 0);
पूर्ण

/* -------------------------------------------------------------------- */

व्योम hdlcdrv_receiver(काष्ठा net_device *, काष्ठा hdlcdrv_state *);
व्योम hdlcdrv_transmitter(काष्ठा net_device *, काष्ठा hdlcdrv_state *);
व्योम hdlcdrv_arbitrate(काष्ठा net_device *, काष्ठा hdlcdrv_state *);
काष्ठा net_device *hdlcdrv_रेजिस्टर(स्थिर काष्ठा hdlcdrv_ops *ops,
				    अचिन्हित पूर्णांक privsize, स्थिर अक्षर *अगरname,
				    अचिन्हित पूर्णांक baseaddr, अचिन्हित पूर्णांक irq, 
				    अचिन्हित पूर्णांक dma);
व्योम hdlcdrv_unरेजिस्टर(काष्ठा net_device *dev);

/* -------------------------------------------------------------------- */



#पूर्ण_अगर /* _HDLCDRV_H */
