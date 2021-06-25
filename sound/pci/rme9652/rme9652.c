<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम RME Digi9652 audio पूर्णांकerfaces 
 *
 *	Copyright (c) 1999 IEM - Winfried Ritsch
 *      Copyright (c) 1999-2001  Paul Davis
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/nospec.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>

#समावेश <यंत्र/current.h>

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल bool precise_ptr[SNDRV_CARDS];			/* Enable precise poपूर्णांकer */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for RME Digi9652 (Hammerfall) soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for RME Digi9652 (Hammerfall) soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable/disable specific RME96{52,36} soundcards.");
module_param_array(precise_ptr, bool, शून्य, 0444);
MODULE_PARM_DESC(precise_ptr, "Enable precise pointer (doesn't work reliably).");
MODULE_AUTHOR("Paul Davis <pbd@op.net>, Winfried Ritsch");
MODULE_DESCRIPTION("RME Digi9652/Digi9636");
MODULE_LICENSE("GPL");

/* The Hammerfall has two sets of 24 ADAT + 2 S/PDIF channels, one क्रम
   capture, one क्रम playback. Both the ADAT and S/PDIF channels appear
   to the host CPU in the same block of memory. There is no functional
   dअगरference between them in terms of access.
   
   The Hammerfall Light is identical to the Hammerfall, except that it
   has 2 sets 18 channels (16 ADAT + 2 S/PDIF) क्रम capture and playback.
*/

#घोषणा RME9652_NCHANNELS       26
#घोषणा RME9636_NCHANNELS       18

/* Preferred sync source choices - used by "sync_pref" control चयन */

#घोषणा RME9652_SYNC_FROM_SPDIF 0
#घोषणा RME9652_SYNC_FROM_ADAT1 1
#घोषणा RME9652_SYNC_FROM_ADAT2 2
#घोषणा RME9652_SYNC_FROM_ADAT3 3

/* Possible sources of S/PDIF input */

#घोषणा RME9652_SPDIFIN_OPTICAL 0	/* optical (ADAT1) */
#घोषणा RME9652_SPDIFIN_COAXIAL 1	/* coaxial (RCA) */
#घोषणा RME9652_SPDIFIN_INTERN  2	/* पूर्णांकernal (CDROM) */

/* ------------- Status-Register bits --------------------- */

#घोषणा RME9652_IRQ	   (1<<0)	/* IRQ is High अगर not reset by irq_clear */
#घोषणा RME9652_lock_2	   (1<<1)	/* ADAT 3-PLL: 1=locked, 0=unlocked */
#घोषणा RME9652_lock_1	   (1<<2)	/* ADAT 2-PLL: 1=locked, 0=unlocked */
#घोषणा RME9652_lock_0	   (1<<3)	/* ADAT 1-PLL: 1=locked, 0=unlocked */
#घोषणा RME9652_fs48	   (1<<4)	/* sample rate is 0=44.1/88.2,1=48/96 Khz */
#घोषणा RME9652_wsel_rd	   (1<<5)	/* अगर Word-Clock is used and valid then 1 */
                                        /* bits 6-15 encode h/w buffer poपूर्णांकer position */
#घोषणा RME9652_sync_2	   (1<<16)	/* अगर ADAT-IN 3 in sync to प्रणाली घड़ी */
#घोषणा RME9652_sync_1	   (1<<17)	/* अगर ADAT-IN 2 in sync to प्रणाली घड़ी */
#घोषणा RME9652_sync_0	   (1<<18)	/* अगर ADAT-IN 1 in sync to प्रणाली घड़ी */
#घोषणा RME9652_DS_rd	   (1<<19)	/* 1=Double Speed Mode, 0=Normal Speed */
#घोषणा RME9652_tc_busy	   (1<<20)	/* 1=समय-code copy in progress (960ms) */
#घोषणा RME9652_tc_out	   (1<<21)	/* समय-code out bit */
#घोषणा RME9652_F_0	   (1<<22)	/* 000=64kHz, 100=88.2kHz, 011=96kHz  */
#घोषणा RME9652_F_1	   (1<<23)	/* 111=32kHz, 110=44.1kHz, 101=48kHz, */
#घोषणा RME9652_F_2	   (1<<24)	/* बाह्यal Crystal Chip अगर ERF=1 */
#घोषणा RME9652_ERF	   (1<<25)	/* Error-Flag of SDPIF Receiver (1=No Lock) */
#घोषणा RME9652_buffer_id  (1<<26)	/* toggles by each पूर्णांकerrupt on rec/play */
#घोषणा RME9652_tc_valid   (1<<27)	/* 1 = a संकेत is detected on समय-code input */
#घोषणा RME9652_SPDIF_READ (1<<28)      /* byte available from Rev 1.5+ S/PDIF पूर्णांकerface */

#घोषणा RME9652_sync	  (RME9652_sync_0|RME9652_sync_1|RME9652_sync_2)
#घोषणा RME9652_lock	  (RME9652_lock_0|RME9652_lock_1|RME9652_lock_2)
#घोषणा RME9652_F	  (RME9652_F_0|RME9652_F_1|RME9652_F_2)
#घोषणा rme9652_decode_spdअगर_rate(x) ((x)>>22)

/* Bit 6..15 : h/w buffer poपूर्णांकer */

#घोषणा RME9652_buf_pos	  0x000FFC0

/* Bits 31,30,29 are bits 5,4,3 of h/w poपूर्णांकer position on later
   Rev G EEPROMS and Rev 1.5 cards or later.
*/ 

#घोषणा RME9652_REV15_buf_pos(x) ((((x)&0xE0000000)>>26)|((x)&RME9652_buf_pos))

/* amount of io space we remap क्रम रेजिस्टर access. i'm not sure we
   even need this much, but 1K is nice round number :)
*/

#घोषणा RME9652_IO_EXTENT     1024

#घोषणा RME9652_init_buffer       0
#घोषणा RME9652_play_buffer       32	/* holds ptr to 26x64kBit host RAM */
#घोषणा RME9652_rec_buffer        36	/* holds ptr to 26x64kBit host RAM */
#घोषणा RME9652_control_रेजिस्टर  64
#घोषणा RME9652_irq_clear         96
#घोषणा RME9652_समय_code         100	/* useful अगर used with alesis adat */
#घोषणा RME9652_thru_base         128	/* 132...228 Thru क्रम 26 channels */

/* Read-only रेजिस्टरs */

/* Writing to any of the रेजिस्टर locations ग_लिखोs to the status
   रेजिस्टर. We'll use the first location as our poपूर्णांक of access.
*/

#घोषणा RME9652_status_रेजिस्टर    0

/* --------- Control-Register Bits ---------------- */


#घोषणा RME9652_start_bit	   (1<<0)	/* start record/play */
                                                /* bits 1-3 encode buffersize/latency */
#घोषणा RME9652_Master		   (1<<4)	/* Clock Mode Master=1,Slave/Auto=0 */
#घोषणा RME9652_IE		   (1<<5)	/* Interrupt Enable */
#घोषणा RME9652_freq		   (1<<6)       /* samplerate 0=44.1/88.2, 1=48/96 kHz */
#घोषणा RME9652_freq1		   (1<<7)       /* अगर 0, 32kHz, अन्यथा always 1 */
#घोषणा RME9652_DS                 (1<<8)	/* Doule Speed 0=44.1/48, 1=88.2/96 Khz */
#घोषणा RME9652_PRO		   (1<<9)	/* S/PDIF out: 0=consumer, 1=professional */
#घोषणा RME9652_EMP		   (1<<10)	/*  Emphasis 0=None, 1=ON */
#घोषणा RME9652_Dolby		   (1<<11)	/*  Non-audio bit 1=set, 0=unset */
#घोषणा RME9652_opt_out	           (1<<12)	/* Use 1st optical OUT as SPDIF: 1=yes,0=no */
#घोषणा RME9652_wsel		   (1<<13)	/* use Wordघड़ी as sync (overग_लिखोs master) */
#घोषणा RME9652_inp_0		   (1<<14)	/* SPDIF-IN: 00=optical (ADAT1),     */
#घोषणा RME9652_inp_1		   (1<<15)	/* 01=koaxial (Cinch), 10=Internal CDROM */
#घोषणा RME9652_SyncPref_ADAT2	   (1<<16)
#घोषणा RME9652_SyncPref_ADAT3	   (1<<17)
#घोषणा RME9652_SPDIF_RESET        (1<<18)      /* Rev 1.5+: h/w S/PDIF receiver */
#घोषणा RME9652_SPDIF_SELECT       (1<<19)
#घोषणा RME9652_SPDIF_CLOCK        (1<<20)
#घोषणा RME9652_SPDIF_WRITE        (1<<21)
#घोषणा RME9652_ADAT1_INTERNAL     (1<<22)      /* Rev 1.5+: अगर set, पूर्णांकernal CD connector carries ADAT */

/* buffersize = 512Bytes * 2^n, where n is made from Bit2 ... Bit0 */

#घोषणा RME9652_latency            0x0e
#घोषणा rme9652_encode_latency(x)  (((x)&0x7)<<1)
#घोषणा rme9652_decode_latency(x)  (((x)>>1)&0x7)
#घोषणा rme9652_running_द्विगुन_speed(s) ((s)->control_रेजिस्टर & RME9652_DS)
#घोषणा RME9652_inp                (RME9652_inp_0|RME9652_inp_1)
#घोषणा rme9652_encode_spdअगर_in(x) (((x)&0x3)<<14)
#घोषणा rme9652_decode_spdअगर_in(x) (((x)>>14)&0x3)

#घोषणा RME9652_SyncPref_Mask      (RME9652_SyncPref_ADAT2|RME9652_SyncPref_ADAT3)
#घोषणा RME9652_SyncPref_ADAT1	   0
#घोषणा RME9652_SyncPref_SPDIF	   (RME9652_SyncPref_ADAT2|RME9652_SyncPref_ADAT3)

/* the size of a substream (1 mono data stream) */

#घोषणा RME9652_CHANNEL_BUFFER_SAMPLES  (16*1024)
#घोषणा RME9652_CHANNEL_BUFFER_BYTES    (4*RME9652_CHANNEL_BUFFER_SAMPLES)

/* the size of the area we need to allocate क्रम DMA transfers. the
   size is the same regardless of the number of channels - the 
   9636 still uses the same memory area.

   Note that we allocate 1 more channel than is apparently needed
   because the h/w seems to ग_लिखो 1 byte beyond the end of the last
   page. Sigh.
*/

#घोषणा RME9652_DMA_AREA_BYTES ((RME9652_NCHANNELS+1) * RME9652_CHANNEL_BUFFER_BYTES)
#घोषणा RME9652_DMA_AREA_KILOBYTES (RME9652_DMA_AREA_BYTES/1024)

काष्ठा snd_rme9652 अणु
	पूर्णांक dev;

	spinlock_t lock;
	पूर्णांक irq;
	अचिन्हित दीर्घ port;
	व्योम __iomem *iobase;
	
	पूर्णांक precise_ptr;

	u32 control_रेजिस्टर;	/* cached value */
	u32 thru_bits;		/* thru 1=on, 0=off channel 1=Bit1... channel 26= Bit26 */

	u32 creg_spdअगर;
	u32 creg_spdअगर_stream;

	अक्षर *card_name;		/* hammerfall or hammerfall light names */

        माप_प्रकार hw_offseपंचांगask;     	/* &-with status रेजिस्टर to get real hw_offset */
	माप_प्रकार prev_hw_offset;		/* previous hw offset */
	माप_प्रकार max_jitter;		/* maximum jitter in frames क्रम 
					   hw poपूर्णांकer */
	माप_प्रकार period_bytes;		/* guess what this is */

	अचिन्हित अक्षर ds_channels;
	अचिन्हित अक्षर ss_channels;	/* dअगरferent क्रम hammerfall/hammerfall-light */

	काष्ठा snd_dma_buffer playback_dma_buf;
	काष्ठा snd_dma_buffer capture_dma_buf;

	अचिन्हित अक्षर *capture_buffer;	/* suitably aligned address */
	अचिन्हित अक्षर *playback_buffer;	/* suitably aligned address */

	pid_t capture_pid;
	pid_t playback_pid;

	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा snd_pcm_substream *playback_substream;
	पूर्णांक running;

        पूर्णांक passthru;                   /* non-zero अगर करोing pass-thru */
        पूर्णांक hw_rev;                     /* h/w rev * 10 (i.e. 1.5 has hw_rev = 15) */

	पूर्णांक last_spdअगर_sample_rate;	/* so that we can catch बाह्यally ... */
	पूर्णांक last_adat_sample_rate;	/* ... induced rate changes            */

	स्थिर अक्षर *channel_map;

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा pci_dev *pci;
	काष्ठा snd_kcontrol *spdअगर_ctl;

पूर्ण;

/* These tables map the ALSA channels 1..N to the channels that we
   need to use in order to find the relevant channel buffer. RME
   refer to this kind of mapping as between "the ADAT channel and
   the DMA channel." We index it using the logical audio channel,
   and the value is the DMA channel (i.e. channel buffer number)
   where the data क्रम that channel can be पढ़ो/written from/to.
*/

अटल स्थिर अक्षर channel_map_9652_ss[26] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25
पूर्ण;

अटल स्थिर अक्षर channel_map_9636_ss[26] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
	/* channels 16 and 17 are S/PDIF */
	24, 25,
	/* channels 18-25 करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_9652_ds[26] = अणु
	/* ADAT channels are remapped */
	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23,
	/* channels 12 and 13 are S/PDIF */
	24, 25,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_9636_ds[26] = अणु
	/* ADAT channels are remapped */
	1, 3, 5, 7, 9, 11, 13, 15,
	/* channels 8 and 9 are S/PDIF */
	24, 25,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल पूर्णांक snd_hammerfall_get_buffer(काष्ठा pci_dev *pci, काष्ठा snd_dma_buffer *dmab, माप_प्रकार size)
अणु
	वापस snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev, size, dmab);
पूर्ण

अटल व्योम snd_hammerfall_मुक्त_buffer(काष्ठा snd_dma_buffer *dmab, काष्ठा pci_dev *pci)
अणु
	अगर (dmab->area)
		snd_dma_मुक्त_pages(dmab);
पूर्ण


अटल स्थिर काष्ठा pci_device_id snd_rme9652_ids[] = अणु
	अणु
		.venकरोr	   = 0x10ee,
		.device	   = 0x3fc4,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,	/* RME Digi9652 */
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_rme9652_ids);

अटल अंतरभूत व्योम rme9652_ग_लिखो(काष्ठा snd_rme9652 *rme9652, पूर्णांक reg, पूर्णांक val)
अणु
	ग_लिखोl(val, rme9652->iobase + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rme9652_पढ़ो(काष्ठा snd_rme9652 *rme9652, पूर्णांक reg)
अणु
	वापस पढ़ोl(rme9652->iobase + reg);
पूर्ण

अटल अंतरभूत पूर्णांक snd_rme9652_use_is_exclusive(काष्ठा snd_rme9652 *rme9652)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 1;

	spin_lock_irqsave(&rme9652->lock, flags);
	अगर ((rme9652->playback_pid != rme9652->capture_pid) &&
	    (rme9652->playback_pid >= 0) && (rme9652->capture_pid >= 0)) अणु
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&rme9652->lock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rme9652_adat_sample_rate(काष्ठा snd_rme9652 *rme9652)
अणु
	अगर (rme9652_running_द्विगुन_speed(rme9652)) अणु
		वापस (rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर) &
			RME9652_fs48) ? 96000 : 88200;
	पूर्ण अन्यथा अणु
		वापस (rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर) &
			RME9652_fs48) ? 48000 : 44100;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rme9652_compute_period_size(काष्ठा snd_rme9652 *rme9652)
अणु
	अचिन्हित पूर्णांक i;

	i = rme9652->control_रेजिस्टर & RME9652_latency;
	rme9652->period_bytes = 1 << ((rme9652_decode_latency(i) + 8));
	rme9652->hw_offseपंचांगask = 
		(rme9652->period_bytes * 2 - 1) & RME9652_buf_pos;
	rme9652->max_jitter = 80;
पूर्ण

अटल snd_pcm_uframes_t rme9652_hw_poपूर्णांकer(काष्ठा snd_rme9652 *rme9652)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक offset, frag;
	snd_pcm_uframes_t period_size = rme9652->period_bytes / 4;
	snd_pcm_sframes_t delta;

	status = rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर);
	अगर (!rme9652->precise_ptr)
		वापस (status & RME9652_buffer_id) ? period_size : 0;
	offset = status & RME9652_buf_pos;

	/* The hardware may give a backward movement क्रम up to 80 frames
           Martin Kirst <martin.kirst@मुक्तnet.de> knows the details.
	*/

	delta = rme9652->prev_hw_offset - offset;
	delta &= 0xffff;
	अगर (delta <= (snd_pcm_sframes_t)rme9652->max_jitter * 4)
		offset = rme9652->prev_hw_offset;
	अन्यथा
		rme9652->prev_hw_offset = offset;
	offset &= rme9652->hw_offseपंचांगask;
	offset /= 4;
	frag = status & RME9652_buffer_id;

	अगर (offset < period_size) अणु
		अगर (offset > rme9652->max_jitter) अणु
			अगर (frag)
				dev_err(rme9652->card->dev,
					"Unexpected hw_pointer position (bufid == 0): status: %x offset: %d\n",
					status, offset);
		पूर्ण अन्यथा अगर (!frag)
			वापस 0;
		offset -= rme9652->max_jitter;
		अगर ((पूर्णांक)offset < 0)
			offset += period_size * 2;
	पूर्ण अन्यथा अणु
		अगर (offset > period_size + rme9652->max_jitter) अणु
			अगर (!frag)
				dev_err(rme9652->card->dev,
					"Unexpected hw_pointer position (bufid == 1): status: %x offset: %d\n",
					status, offset);
		पूर्ण अन्यथा अगर (frag)
			वापस period_size;
		offset -= rme9652->max_jitter;
	पूर्ण

	वापस offset;
पूर्ण

अटल अंतरभूत व्योम rme9652_reset_hw_poपूर्णांकer(काष्ठा snd_rme9652 *rme9652)
अणु
	पूर्णांक i;

	/* reset the FIFO poपूर्णांकer to zero. We करो this by writing to 8
	   रेजिस्टरs, each of which is a 32bit wide रेजिस्टर, and set
	   them all to zero. Note that s->iobase is a poपूर्णांकer to
	   पूर्णांक32, not poपूर्णांकer to अक्षर.  
	*/

	क्रम (i = 0; i < 8; i++) अणु
		rme9652_ग_लिखो(rme9652, i * 4, 0);
		udelay(10);
	पूर्ण
	rme9652->prev_hw_offset = 0;
पूर्ण

अटल अंतरभूत व्योम rme9652_start(काष्ठा snd_rme9652 *s)
अणु
	s->control_रेजिस्टर |= (RME9652_IE | RME9652_start_bit);
	rme9652_ग_लिखो(s, RME9652_control_रेजिस्टर, s->control_रेजिस्टर);
पूर्ण

अटल अंतरभूत व्योम rme9652_stop(काष्ठा snd_rme9652 *s)
अणु
	s->control_रेजिस्टर &= ~(RME9652_start_bit | RME9652_IE);
	rme9652_ग_लिखो(s, RME9652_control_रेजिस्टर, s->control_रेजिस्टर);
पूर्ण

अटल पूर्णांक rme9652_set_पूर्णांकerrupt_पूर्णांकerval(काष्ठा snd_rme9652 *s,
					  अचिन्हित पूर्णांक frames)
अणु
	पूर्णांक restart = 0;
	पूर्णांक n;

	spin_lock_irq(&s->lock);

	अगर ((restart = s->running)) अणु
		rme9652_stop(s);
	पूर्ण

	frames >>= 7;
	n = 0;
	जबतक (frames) अणु
		n++;
		frames >>= 1;
	पूर्ण

	s->control_रेजिस्टर &= ~RME9652_latency;
	s->control_रेजिस्टर |= rme9652_encode_latency(n);

	rme9652_ग_लिखो(s, RME9652_control_रेजिस्टर, s->control_रेजिस्टर);

	rme9652_compute_period_size(s);

	अगर (restart)
		rme9652_start(s);

	spin_unlock_irq(&s->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rme9652_set_rate(काष्ठा snd_rme9652 *rme9652, पूर्णांक rate)
अणु
	पूर्णांक restart;
	पूर्णांक reject_अगर_खोलो = 0;
	पूर्णांक xrate;

	अगर (!snd_rme9652_use_is_exclusive (rme9652)) अणु
		वापस -EBUSY;
	पूर्ण

	/* Changing from a "single speed" to a "double speed" rate is
	   not allowed अगर any substreams are खोलो. This is because
	   such a change causes a shअगरt in the location of 
	   the DMA buffers and a reduction in the number of available
	   buffers. 

	   Note that a similar but essentially insoluble problem
	   exists क्रम बाह्यally-driven rate changes. All we can करो
	   is to flag rate changes in the पढ़ो/ग_लिखो routines.
	 */

	spin_lock_irq(&rme9652->lock);
	xrate = rme9652_adat_sample_rate(rme9652);

	चयन (rate) अणु
	हाल 44100:
		अगर (xrate > 48000) अणु
			reject_अगर_खोलो = 1;
		पूर्ण
		rate = 0;
		अवरोध;
	हाल 48000:
		अगर (xrate > 48000) अणु
			reject_अगर_खोलो = 1;
		पूर्ण
		rate = RME9652_freq;
		अवरोध;
	हाल 88200:
		अगर (xrate < 48000) अणु
			reject_अगर_खोलो = 1;
		पूर्ण
		rate = RME9652_DS;
		अवरोध;
	हाल 96000:
		अगर (xrate < 48000) अणु
			reject_अगर_खोलो = 1;
		पूर्ण
		rate = RME9652_DS | RME9652_freq;
		अवरोध;
	शेष:
		spin_unlock_irq(&rme9652->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (reject_अगर_खोलो && (rme9652->capture_pid >= 0 || rme9652->playback_pid >= 0)) अणु
		spin_unlock_irq(&rme9652->lock);
		वापस -EBUSY;
	पूर्ण

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण
	rme9652->control_रेजिस्टर &= ~(RME9652_freq | RME9652_DS);
	rme9652->control_रेजिस्टर |= rate;
	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	अगर (rate & RME9652_DS) अणु
		अगर (rme9652->ss_channels == RME9652_NCHANNELS) अणु
			rme9652->channel_map = channel_map_9652_ds;
		पूर्ण अन्यथा अणु
			rme9652->channel_map = channel_map_9636_ds;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rme9652->ss_channels == RME9652_NCHANNELS) अणु
			rme9652->channel_map = channel_map_9652_ss;
		पूर्ण अन्यथा अणु
			rme9652->channel_map = channel_map_9636_ss;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल व्योम rme9652_set_thru(काष्ठा snd_rme9652 *rme9652, पूर्णांक channel, पूर्णांक enable)
अणु
	पूर्णांक i;

	rme9652->passthru = 0;

	अगर (channel < 0) अणु

		/* set thru क्रम all channels */

		अगर (enable) अणु
			क्रम (i = 0; i < RME9652_NCHANNELS; i++) अणु
				rme9652->thru_bits |= (1 << i);
				rme9652_ग_लिखो(rme9652, RME9652_thru_base + i * 4, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < RME9652_NCHANNELS; i++) अणु
				rme9652->thru_bits &= ~(1 << i);
				rme9652_ग_लिखो(rme9652, RME9652_thru_base + i * 4, 0);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		पूर्णांक mapped_channel;

		mapped_channel = rme9652->channel_map[channel];

		अगर (enable) अणु
			rme9652->thru_bits |= (1 << mapped_channel);
		पूर्ण अन्यथा अणु
			rme9652->thru_bits &= ~(1 << mapped_channel);
		पूर्ण

		rme9652_ग_लिखो(rme9652,
			       RME9652_thru_base + mapped_channel * 4,
			       enable ? 1 : 0);			       
	पूर्ण
पूर्ण

अटल पूर्णांक rme9652_set_passthru(काष्ठा snd_rme9652 *rme9652, पूर्णांक onoff)
अणु
	अगर (onoff) अणु
		rme9652_set_thru(rme9652, -1, 1);

		/* we करोn't want पूर्णांकerrupts, so करो a
		   custom version of rme9652_start().
		*/

		rme9652->control_रेजिस्टर =
			RME9652_inp_0 | 
			rme9652_encode_latency(7) |
			RME9652_start_bit;

		rme9652_reset_hw_poपूर्णांकer(rme9652);

		rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर,
			      rme9652->control_रेजिस्टर);
		rme9652->passthru = 1;
	पूर्ण अन्यथा अणु
		rme9652_set_thru(rme9652, -1, 0);
		rme9652_stop(rme9652);		
		rme9652->passthru = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rme9652_spdअगर_set_bit (काष्ठा snd_rme9652 *rme9652, पूर्णांक mask, पूर्णांक onoff)
अणु
	अगर (onoff) 
		rme9652->control_रेजिस्टर |= mask;
	अन्यथा 
		rme9652->control_रेजिस्टर &= ~mask;
		
	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);
पूर्ण

अटल व्योम rme9652_spdअगर_ग_लिखो_byte (काष्ठा snd_rme9652 *rme9652, स्थिर पूर्णांक val)
अणु
	दीर्घ mask;
	दीर्घ i;

	क्रम (i = 0, mask = 0x80; i < 8; i++, mask >>= 1) अणु
		अगर (val & mask)
			rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_WRITE, 1);
		अन्यथा 
			rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_WRITE, 0);

		rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_CLOCK, 1);
		rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_CLOCK, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक rme9652_spdअगर_पढ़ो_byte (काष्ठा snd_rme9652 *rme9652)
अणु
	दीर्घ mask;
	दीर्घ val;
	दीर्घ i;

	val = 0;

	क्रम (i = 0, mask = 0x80;  i < 8; i++, mask >>= 1) अणु
		rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_CLOCK, 1);
		अगर (rme9652_पढ़ो (rme9652, RME9652_status_रेजिस्टर) & RME9652_SPDIF_READ)
			val |= mask;
		rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_CLOCK, 0);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम rme9652_ग_लिखो_spdअगर_codec (काष्ठा snd_rme9652 *rme9652, स्थिर पूर्णांक address, स्थिर पूर्णांक data)
अणु
	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 1);
	rme9652_spdअगर_ग_लिखो_byte (rme9652, 0x20);
	rme9652_spdअगर_ग_लिखो_byte (rme9652, address);
	rme9652_spdअगर_ग_लिखो_byte (rme9652, data);
	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 0);
पूर्ण


अटल पूर्णांक rme9652_spdअगर_पढ़ो_codec (काष्ठा snd_rme9652 *rme9652, स्थिर पूर्णांक address)
अणु
	पूर्णांक ret;

	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 1);
	rme9652_spdअगर_ग_लिखो_byte (rme9652, 0x20);
	rme9652_spdअगर_ग_लिखो_byte (rme9652, address);
	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 0);
	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 1);

	rme9652_spdअगर_ग_लिखो_byte (rme9652, 0x21);
	ret = rme9652_spdअगर_पढ़ो_byte (rme9652);
	rme9652_spdअगर_set_bit (rme9652, RME9652_SPDIF_SELECT, 0);

	वापस ret;
पूर्ण

अटल व्योम rme9652_initialize_spdअगर_receiver (काष्ठा snd_rme9652 *rme9652)
अणु
	/* XXX what unsets this ? */

	rme9652->control_रेजिस्टर |= RME9652_SPDIF_RESET;

	rme9652_ग_लिखो_spdअगर_codec (rme9652, 4, 0x40);
	rme9652_ग_लिखो_spdअगर_codec (rme9652, 17, 0x13);
	rme9652_ग_लिखो_spdअगर_codec (rme9652, 6, 0x02);
पूर्ण

अटल अंतरभूत पूर्णांक rme9652_spdअगर_sample_rate(काष्ठा snd_rme9652 *s)
अणु
	अचिन्हित पूर्णांक rate_bits;

	अगर (rme9652_पढ़ो(s, RME9652_status_रेजिस्टर) & RME9652_ERF) अणु
		वापस -1;	/* error condition */
	पूर्ण
	
	अगर (s->hw_rev == 15) अणु

		पूर्णांक x, y, ret;
		
		x = rme9652_spdअगर_पढ़ो_codec (s, 30);

		अगर (x != 0) 
			y = 48000 * 64 / x;
		अन्यथा
			y = 0;

		अगर      (y > 30400 && y < 33600)  ret = 32000; 
		अन्यथा अगर (y > 41900 && y < 46000)  ret = 44100;
		अन्यथा अगर (y > 46000 && y < 50400)  ret = 48000;
		अन्यथा अगर (y > 60800 && y < 67200)  ret = 64000;
		अन्यथा अगर (y > 83700 && y < 92000)  ret = 88200;
		अन्यथा अगर (y > 92000 && y < 100000) ret = 96000;
		अन्यथा                              ret = 0;
		वापस ret;
	पूर्ण

	rate_bits = rme9652_पढ़ो(s, RME9652_status_रेजिस्टर) & RME9652_F;

	चयन (rme9652_decode_spdअगर_rate(rate_bits)) अणु
	हाल 0x7:
		वापस 32000;

	हाल 0x6:
		वापस 44100;

	हाल 0x5:
		वापस 48000;

	हाल 0x4:
		वापस 88200;

	हाल 0x3:
		वापस 96000;

	हाल 0x0:
		वापस 64000;

	शेष:
		dev_err(s->card->dev,
			"%s: unknown S/PDIF input rate (bits = 0x%x)\n",
			   s->card_name, rate_bits);
		वापस 0;
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------------------
  Control Interface
  ----------------------------------------------------------------------------*/

अटल u32 snd_rme9652_convert_from_aes(काष्ठा snd_aes_iec958 *aes)
अणु
	u32 val = 0;
	val |= (aes->status[0] & IEC958_AES0_PROFESSIONAL) ? RME9652_PRO : 0;
	val |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? RME9652_Dolby : 0;
	अगर (val & RME9652_PRO)
		val |= (aes->status[0] & IEC958_AES0_PRO_EMPHASIS_5015) ? RME9652_EMP : 0;
	अन्यथा
		val |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? RME9652_EMP : 0;
	वापस val;
पूर्ण

अटल व्योम snd_rme9652_convert_to_aes(काष्ठा snd_aes_iec958 *aes, u32 val)
अणु
	aes->status[0] = ((val & RME9652_PRO) ? IEC958_AES0_PROFESSIONAL : 0) |
			 ((val & RME9652_Dolby) ? IEC958_AES0_NONAUDIO : 0);
	अगर (val & RME9652_PRO)
		aes->status[0] |= (val & RME9652_EMP) ? IEC958_AES0_PRO_EMPHASIS_5015 : 0;
	अन्यथा
		aes->status[0] |= (val & RME9652_EMP) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	snd_rme9652_convert_to_aes(&ucontrol->value.iec958, rme9652->creg_spdअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;
	
	val = snd_rme9652_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme9652->lock);
	change = val != rme9652->creg_spdअगर;
	rme9652->creg_spdअगर = val;
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	snd_rme9652_convert_to_aes(&ucontrol->value.iec958, rme9652->creg_spdअगर_stream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;
	
	val = snd_rme9652_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme9652->lock);
	change = val != rme9652->creg_spdअगर_stream;
	rme9652->creg_spdअगर_stream = val;
	rme9652->control_रेजिस्टर &= ~(RME9652_PRO | RME9652_Dolby | RME9652_EMP);
	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर |= val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_control_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

#घोषणा RME9652_ADAT1_IN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_adat1_in, \
  .get = snd_rme9652_get_adat1_in, \
  .put = snd_rme9652_put_adat1_in पूर्ण

अटल अचिन्हित पूर्णांक rme9652_adat1_in(काष्ठा snd_rme9652 *rme9652)
अणु
	अगर (rme9652->control_रेजिस्टर & RME9652_ADAT1_INTERNAL)
		वापस 1; 
	वापस 0;
पूर्ण

अटल पूर्णांक rme9652_set_adat1_input(काष्ठा snd_rme9652 *rme9652, पूर्णांक पूर्णांकernal)
अणु
	पूर्णांक restart = 0;

	अगर (पूर्णांकernal) अणु
		rme9652->control_रेजिस्टर |= RME9652_ADAT1_INTERNAL;
	पूर्ण अन्यथा अणु
		rme9652->control_रेजिस्टर &= ~RME9652_ADAT1_INTERNAL;
	पूर्ण

	/* XXX करो we actually need to stop the card when we करो this ? */

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_info_adat1_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु"ADAT1", "Internal"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_rme9652_get_adat1_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.क्रमागतerated.item[0] = rme9652_adat1_in(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_adat1_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	
	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0] % 2;
	spin_lock_irq(&rme9652->lock);
	change = val != rme9652_adat1_in(rme9652);
	अगर (change)
		rme9652_set_adat1_input(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

#घोषणा RME9652_SPDIF_IN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_spdअगर_in, \
  .get = snd_rme9652_get_spdअगर_in, .put = snd_rme9652_put_spdअगर_in पूर्ण

अटल अचिन्हित पूर्णांक rme9652_spdअगर_in(काष्ठा snd_rme9652 *rme9652)
अणु
	वापस rme9652_decode_spdअगर_in(rme9652->control_रेजिस्टर &
				       RME9652_inp);
पूर्ण

अटल पूर्णांक rme9652_set_spdअगर_input(काष्ठा snd_rme9652 *rme9652, पूर्णांक in)
अणु
	पूर्णांक restart = 0;

	rme9652->control_रेजिस्टर &= ~RME9652_inp;
	rme9652->control_रेजिस्टर |= rme9652_encode_spdअगर_in(in);

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_info_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु"ADAT1", "Coaxial", "Internal"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_rme9652_get_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.क्रमागतerated.item[0] = rme9652_spdअगर_in(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	
	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0] % 3;
	spin_lock_irq(&rme9652->lock);
	change = val != rme9652_spdअगर_in(rme9652);
	अगर (change)
		rme9652_set_spdअगर_input(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

#घोषणा RME9652_SPDIF_OUT(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_spdअगर_out, \
  .get = snd_rme9652_get_spdअगर_out, .put = snd_rme9652_put_spdअगर_out पूर्ण

अटल पूर्णांक rme9652_spdअगर_out(काष्ठा snd_rme9652 *rme9652)
अणु
	वापस (rme9652->control_रेजिस्टर & RME9652_opt_out) ? 1 : 0;
पूर्ण

अटल पूर्णांक rme9652_set_spdअगर_output(काष्ठा snd_rme9652 *rme9652, पूर्णांक out)
अणु
	पूर्णांक restart = 0;

	अगर (out) अणु
		rme9652->control_रेजिस्टर |= RME9652_opt_out;
	पूर्ण अन्यथा अणु
		rme9652->control_रेजिस्टर &= ~RME9652_opt_out;
	पूर्ण

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा snd_rme9652_info_spdअगर_out	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_rme9652_get_spdअगर_out(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.पूर्णांकeger.value[0] = rme9652_spdअगर_out(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_spdअगर_out(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	
	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&rme9652->lock);
	change = (पूर्णांक)val != rme9652_spdअगर_out(rme9652);
	rme9652_set_spdअगर_output(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

#घोषणा RME9652_SYNC_MODE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_sync_mode, \
  .get = snd_rme9652_get_sync_mode, .put = snd_rme9652_put_sync_mode पूर्ण

अटल पूर्णांक rme9652_sync_mode(काष्ठा snd_rme9652 *rme9652)
अणु
	अगर (rme9652->control_रेजिस्टर & RME9652_wsel) अणु
		वापस 2;
	पूर्ण अन्यथा अगर (rme9652->control_रेजिस्टर & RME9652_Master) अणु
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक rme9652_set_sync_mode(काष्ठा snd_rme9652 *rme9652, पूर्णांक mode)
अणु
	पूर्णांक restart = 0;

	चयन (mode) अणु
	हाल 0:
		rme9652->control_रेजिस्टर &=
		    ~(RME9652_Master | RME9652_wsel);
		अवरोध;
	हाल 1:
		rme9652->control_रेजिस्टर =
		    (rme9652->control_रेजिस्टर & ~RME9652_wsel) | RME9652_Master;
		अवरोध;
	हाल 2:
		rme9652->control_रेजिस्टर |=
		    (RME9652_Master | RME9652_wsel);
		अवरोध;
	पूर्ण

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_info_sync_mode(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"AutoSync", "Master", "Word Clock"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_rme9652_get_sync_mode(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.क्रमागतerated.item[0] = rme9652_sync_mode(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_sync_mode(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	
	val = ucontrol->value.क्रमागतerated.item[0] % 3;
	spin_lock_irq(&rme9652->lock);
	change = (पूर्णांक)val != rme9652_sync_mode(rme9652);
	rme9652_set_sync_mode(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

#घोषणा RME9652_SYNC_PREF(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_sync_pref, \
  .get = snd_rme9652_get_sync_pref, .put = snd_rme9652_put_sync_pref पूर्ण

अटल पूर्णांक rme9652_sync_pref(काष्ठा snd_rme9652 *rme9652)
अणु
	चयन (rme9652->control_रेजिस्टर & RME9652_SyncPref_Mask) अणु
	हाल RME9652_SyncPref_ADAT1:
		वापस RME9652_SYNC_FROM_ADAT1;
	हाल RME9652_SyncPref_ADAT2:
		वापस RME9652_SYNC_FROM_ADAT2;
	हाल RME9652_SyncPref_ADAT3:
		वापस RME9652_SYNC_FROM_ADAT3;
	हाल RME9652_SyncPref_SPDIF:
		वापस RME9652_SYNC_FROM_SPDIF;
	पूर्ण
	/* Not reachable */
	वापस 0;
पूर्ण

अटल पूर्णांक rme9652_set_sync_pref(काष्ठा snd_rme9652 *rme9652, पूर्णांक pref)
अणु
	पूर्णांक restart;

	rme9652->control_रेजिस्टर &= ~RME9652_SyncPref_Mask;
	चयन (pref) अणु
	हाल RME9652_SYNC_FROM_ADAT1:
		rme9652->control_रेजिस्टर |= RME9652_SyncPref_ADAT1;
		अवरोध;
	हाल RME9652_SYNC_FROM_ADAT2:
		rme9652->control_रेजिस्टर |= RME9652_SyncPref_ADAT2;
		अवरोध;
	हाल RME9652_SYNC_FROM_ADAT3:
		rme9652->control_रेजिस्टर |= RME9652_SyncPref_ADAT3;
		अवरोध;
	हाल RME9652_SYNC_FROM_SPDIF:
		rme9652->control_रेजिस्टर |= RME9652_SyncPref_SPDIF;
		अवरोध;
	पूर्ण

	अगर ((restart = rme9652->running)) अणु
		rme9652_stop(rme9652);
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	अगर (restart) अणु
		rme9652_start(rme9652);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_info_sync_pref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"IEC958 In", "ADAT1 In", "ADAT2 In", "ADAT3 In"
	पूर्ण;
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 rme9652->ss_channels == RME9652_NCHANNELS ? 4 : 3,
				 texts);
पूर्ण

अटल पूर्णांक snd_rme9652_get_sync_pref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.क्रमागतerated.item[0] = rme9652_sync_pref(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_sync_pref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, max;
	अचिन्हित पूर्णांक val;
	
	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;
	max = rme9652->ss_channels == RME9652_NCHANNELS ? 4 : 3;
	val = ucontrol->value.क्रमागतerated.item[0] % max;
	spin_lock_irq(&rme9652->lock);
	change = (पूर्णांक)val != rme9652_sync_pref(rme9652);
	rme9652_set_sync_pref(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme9652_info_thru(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = rme9652->ss_channels;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_get_thru(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक k;
	u32 thru_bits = rme9652->thru_bits;

	क्रम (k = 0; k < rme9652->ss_channels; ++k) अणु
		ucontrol->value.पूर्णांकeger.value[k] = !!(thru_bits & (1 << k));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_thru(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक chn;
	u32 thru_bits = 0;

	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;

	क्रम (chn = 0; chn < rme9652->ss_channels; ++chn) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[chn])
			thru_bits |= 1 << chn;
	पूर्ण
	
	spin_lock_irq(&rme9652->lock);
	change = thru_bits ^ rme9652->thru_bits;
	अगर (change) अणु
		क्रम (chn = 0; chn < rme9652->ss_channels; ++chn) अणु
			अगर (!(change & (1 << chn)))
				जारी;
			rme9652_set_thru(rme9652,chn,thru_bits&(1<<chn));
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rme9652->lock);
	वापस !!change;
पूर्ण

#घोषणा RME9652_PASSTHRU(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_rme9652_info_passthru, \
  .put = snd_rme9652_put_passthru, \
  .get = snd_rme9652_get_passthru पूर्ण

#घोषणा snd_rme9652_info_passthru	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_rme9652_get_passthru(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&rme9652->lock);
	ucontrol->value.पूर्णांकeger.value[0] = rme9652->passthru;
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_put_passthru(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;
	पूर्णांक err = 0;

	अगर (!snd_rme9652_use_is_exclusive(rme9652))
		वापस -EBUSY;

	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&rme9652->lock);
	change = (ucontrol->value.पूर्णांकeger.value[0] != rme9652->passthru);
	अगर (change)
		err = rme9652_set_passthru(rme9652, val);
	spin_unlock_irq(&rme9652->lock);
	वापस err ? err : change;
पूर्ण

/* Read-only चयनes */

#घोषणा RME9652_SPDIF_RATE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_rme9652_info_spdअगर_rate, \
  .get = snd_rme9652_get_spdअगर_rate पूर्ण

अटल पूर्णांक snd_rme9652_info_spdअगर_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 96000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_get_spdअगर_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme9652->lock);
	ucontrol->value.पूर्णांकeger.value[0] = rme9652_spdअगर_sample_rate(rme9652);
	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

#घोषणा RME9652_ADAT_SYNC(xname, xindex, xidx) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_rme9652_info_adat_sync, \
  .get = snd_rme9652_get_adat_sync, .निजी_value = xidx पूर्ण

अटल पूर्णांक snd_rme9652_info_adat_sync(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"No Lock", "Lock", "No Lock Sync", "Lock Sync"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण

अटल पूर्णांक snd_rme9652_get_adat_sync(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक mask1, mask2, val;
	
	चयन (kcontrol->निजी_value) अणु
	हाल 0: mask1 = RME9652_lock_0; mask2 = RME9652_sync_0; अवरोध;	
	हाल 1: mask1 = RME9652_lock_1; mask2 = RME9652_sync_1; अवरोध;	
	हाल 2: mask1 = RME9652_lock_2; mask2 = RME9652_sync_2; अवरोध;	
	शेष: वापस -EINVAL;
	पूर्ण
	val = rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर);
	ucontrol->value.क्रमागतerated.item[0] = (val & mask1) ? 1 : 0;
	ucontrol->value.क्रमागतerated.item[0] |= (val & mask2) ? 2 : 0;
	वापस 0;
पूर्ण

#घोषणा RME9652_TC_VALID(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_rme9652_info_tc_valid, \
  .get = snd_rme9652_get_tc_valid पूर्ण

#घोषणा snd_rme9652_info_tc_valid	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_rme9652_get_tc_valid(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = 
		(rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर) & RME9652_tc_valid) ? 1 : 0;
	वापस 0;
पूर्ण

#अगर_घोषित ALSA_HAS_STANDARD_WAY_OF_RETURNING_TIMECODE

/* FIXME: this routine needs a port to the new control API --jk */

अटल पूर्णांक snd_rme9652_get_tc_value(व्योम *निजी_data,
				    snd_kचयन_t *kचयन,
				    snd_चयन_t *uचयन)
अणु
	काष्ठा snd_rme9652 *s = (काष्ठा snd_rme9652 *) निजी_data;
	u32 value;
	पूर्णांक i;

	uचयन->type = SNDRV_SW_TYPE_DWORD;

	अगर ((rme9652_पढ़ो(s, RME9652_status_रेजिस्टर) &
	     RME9652_tc_valid) == 0) अणु
		uचयन->value.data32[0] = 0;
		वापस 0;
	पूर्ण

	/* समयcode request */

	rme9652_ग_लिखो(s, RME9652_समय_code, 0);

	/* XXX bug alert: loop-based timing !!!! */

	क्रम (i = 0; i < 50; i++) अणु
		अगर (!(rme9652_पढ़ो(s, i * 4) & RME9652_tc_busy))
			अवरोध;
	पूर्ण

	अगर (!(rme9652_पढ़ो(s, i * 4) & RME9652_tc_busy)) अणु
		वापस -EIO;
	पूर्ण

	value = 0;

	क्रम (i = 0; i < 32; i++) अणु
		value >>= 1;

		अगर (rme9652_पढ़ो(s, i * 4) & RME9652_tc_out)
			value |= 0x80000000;
	पूर्ण

	अगर (value > 2 * 60 * 48000) अणु
		value -= 2 * 60 * 48000;
	पूर्ण अन्यथा अणु
		value = 0;
	पूर्ण

	uचयन->value.data32[0] = value;

	वापस 0;
पूर्ण

#पूर्ण_अगर				/* ALSA_HAS_STANDARD_WAY_OF_RETURNING_TIMECODE */

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme9652_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_rme9652_control_spdअगर_info,
	.get =		snd_rme9652_control_spdअगर_get,
	.put =		snd_rme9652_control_spdअगर_put,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_rme9652_control_spdअगर_stream_info,
	.get =		snd_rme9652_control_spdअगर_stream_get,
	.put =		snd_rme9652_control_spdअगर_stream_put,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		snd_rme9652_control_spdअगर_mask_info,
	.get =		snd_rme9652_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PROFESSIONAL |
			IEC958_AES0_CON_EMPHASIS,	                                                                                      
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PRO_MASK),
	.info =		snd_rme9652_control_spdअगर_mask_info,
	.get =		snd_rme9652_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PROFESSIONAL |
			IEC958_AES0_PRO_EMPHASIS,
पूर्ण,
RME9652_SPDIF_IN("IEC958 Input Connector", 0),
RME9652_SPDIF_OUT("IEC958 Output also on ADAT1", 0),
RME9652_SYNC_MODE("Sync Mode", 0),
RME9652_SYNC_PREF("Preferred Sync Source", 0),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Channels Thru",
	.index = 0,
	.info = snd_rme9652_info_thru,
	.get = snd_rme9652_get_thru,
	.put = snd_rme9652_put_thru,
पूर्ण,
RME9652_SPDIF_RATE("IEC958 Sample Rate", 0),
RME9652_ADAT_SYNC("ADAT1 Sync Check", 0, 0),
RME9652_ADAT_SYNC("ADAT2 Sync Check", 0, 1),
RME9652_TC_VALID("Timecode Valid", 0),
RME9652_PASSTHRU("Passthru", 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme9652_adat3_check =
RME9652_ADAT_SYNC("ADAT3 Sync Check", 0, 2);

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme9652_adat1_input =
RME9652_ADAT1_IN("ADAT1 Input Source", 0);

अटल पूर्णांक snd_rme9652_create_controls(काष्ठा snd_card *card, काष्ठा snd_rme9652 *rme9652)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_rme9652_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme9652_controls[idx], rme9652))) < 0)
			वापस err;
		अगर (idx == 1)	/* IEC958 (S/PDIF) Stream */
			rme9652->spdअगर_ctl = kctl;
	पूर्ण

	अगर (rme9652->ss_channels == RME9652_NCHANNELS)
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme9652_adat3_check, rme9652))) < 0)
			वापस err;

	अगर (rme9652->hw_rev >= 15)
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme9652_adat1_input, rme9652))) < 0)
			वापस err;

	वापस 0;
पूर्ण

/*------------------------------------------------------------
   /proc पूर्णांकerface 
 ------------------------------------------------------------*/

अटल व्योम
snd_rme9652_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_rme9652 *rme9652 = (काष्ठा snd_rme9652 *) entry->निजी_data;
	u32 thru_bits = rme9652->thru_bits;
	पूर्णांक show_स्वतः_sync_source = 0;
	पूर्णांक i;
	अचिन्हित पूर्णांक status;
	पूर्णांक x;

	status = rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर);

	snd_iम_लिखो(buffer, "%s (Card #%d)\n", rme9652->card_name, rme9652->card->number + 1);
	snd_iम_लिखो(buffer, "Buffers: capture %p playback %p\n",
		    rme9652->capture_buffer, rme9652->playback_buffer);
	snd_iम_लिखो(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
		    rme9652->irq, rme9652->port, (अचिन्हित दीर्घ)rme9652->iobase);
	snd_iम_लिखो(buffer, "Control register: %x\n", rme9652->control_रेजिस्टर);

	snd_iम_लिखो(buffer, "\n");

	x = 1 << (6 + rme9652_decode_latency(rme9652->control_रेजिस्टर & 
					     RME9652_latency));

	snd_iम_लिखो(buffer, "Latency: %d samples (2 periods of %lu bytes)\n", 
		    x, (अचिन्हित दीर्घ) rme9652->period_bytes);
	snd_iम_लिखो(buffer, "Hardware pointer (frames): %ld\n",
		    rme9652_hw_poपूर्णांकer(rme9652));
	snd_iम_लिखो(buffer, "Passthru: %s\n",
		    rme9652->passthru ? "yes" : "no");

	अगर ((rme9652->control_रेजिस्टर & (RME9652_Master | RME9652_wsel)) == 0) अणु
		snd_iम_लिखो(buffer, "Clock mode: autosync\n");
		show_स्वतः_sync_source = 1;
	पूर्ण अन्यथा अगर (rme9652->control_रेजिस्टर & RME9652_wsel) अणु
		अगर (status & RME9652_wsel_rd) अणु
			snd_iम_लिखो(buffer, "Clock mode: word clock\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "Clock mode: word clock (no signal)\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "Clock mode: master\n");
	पूर्ण

	अगर (show_स्वतः_sync_source) अणु
		चयन (rme9652->control_रेजिस्टर & RME9652_SyncPref_Mask) अणु
		हाल RME9652_SyncPref_ADAT1:
			snd_iम_लिखो(buffer, "Pref. sync source: ADAT1\n");
			अवरोध;
		हाल RME9652_SyncPref_ADAT2:
			snd_iम_लिखो(buffer, "Pref. sync source: ADAT2\n");
			अवरोध;
		हाल RME9652_SyncPref_ADAT3:
			snd_iम_लिखो(buffer, "Pref. sync source: ADAT3\n");
			अवरोध;
		हाल RME9652_SyncPref_SPDIF:
			snd_iम_लिखो(buffer, "Pref. sync source: IEC958\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "Pref. sync source: ???\n");
		पूर्ण
	पूर्ण

	अगर (rme9652->hw_rev >= 15)
		snd_iम_लिखो(buffer, "\nADAT1 Input source: %s\n",
			    (rme9652->control_रेजिस्टर & RME9652_ADAT1_INTERNAL) ?
			    "Internal" : "ADAT1 optical");

	snd_iम_लिखो(buffer, "\n");

	चयन (rme9652_decode_spdअगर_in(rme9652->control_रेजिस्टर & 
					RME9652_inp)) अणु
	हाल RME9652_SPDIFIN_OPTICAL:
		snd_iम_लिखो(buffer, "IEC958 input: ADAT1\n");
		अवरोध;
	हाल RME9652_SPDIFIN_COAXIAL:
		snd_iम_लिखो(buffer, "IEC958 input: Coaxial\n");
		अवरोध;
	हाल RME9652_SPDIFIN_INTERN:
		snd_iम_लिखो(buffer, "IEC958 input: Internal\n");
		अवरोध;
	शेष:
		snd_iम_लिखो(buffer, "IEC958 input: ???\n");
		अवरोध;
	पूर्ण

	अगर (rme9652->control_रेजिस्टर & RME9652_opt_out) अणु
		snd_iम_लिखो(buffer, "IEC958 output: Coaxial & ADAT1\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "IEC958 output: Coaxial only\n");
	पूर्ण

	अगर (rme9652->control_रेजिस्टर & RME9652_PRO) अणु
		snd_iम_लिखो(buffer, "IEC958 quality: Professional\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "IEC958 quality: Consumer\n");
	पूर्ण

	अगर (rme9652->control_रेजिस्टर & RME9652_EMP) अणु
		snd_iम_लिखो(buffer, "IEC958 emphasis: on\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "IEC958 emphasis: off\n");
	पूर्ण

	अगर (rme9652->control_रेजिस्टर & RME9652_Dolby) अणु
		snd_iम_लिखो(buffer, "IEC958 Dolby: on\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "IEC958 Dolby: off\n");
	पूर्ण

	i = rme9652_spdअगर_sample_rate(rme9652);

	अगर (i < 0) अणु
		snd_iम_लिखो(buffer,
			    "IEC958 sample rate: error flag set\n");
	पूर्ण अन्यथा अगर (i == 0) अणु
		snd_iम_लिखो(buffer, "IEC958 sample rate: undetermined\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "IEC958 sample rate: %d\n", i);
	पूर्ण

	snd_iम_लिखो(buffer, "\n");

	snd_iम_लिखो(buffer, "ADAT Sample rate: %dHz\n",
		    rme9652_adat_sample_rate(rme9652));

	/* Sync Check */

	x = status & RME9652_sync_0;
	अगर (status & RME9652_lock_0) अणु
		snd_iम_लिखो(buffer, "ADAT1: %s\n", x ? "Sync" : "Lock");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "ADAT1: No Lock\n");
	पूर्ण

	x = status & RME9652_sync_1;
	अगर (status & RME9652_lock_1) अणु
		snd_iम_लिखो(buffer, "ADAT2: %s\n", x ? "Sync" : "Lock");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "ADAT2: No Lock\n");
	पूर्ण

	x = status & RME9652_sync_2;
	अगर (status & RME9652_lock_2) अणु
		snd_iम_लिखो(buffer, "ADAT3: %s\n", x ? "Sync" : "Lock");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "ADAT3: No Lock\n");
	पूर्ण

	snd_iम_लिखो(buffer, "\n");

	snd_iम_लिखो(buffer, "Timecode signal: %s\n",
		    (status & RME9652_tc_valid) ? "yes" : "no");

	/* thru modes */

	snd_iम_लिखो(buffer, "Punch Status:\n\n");

	क्रम (i = 0; i < rme9652->ss_channels; i++) अणु
		अगर (thru_bits & (1 << i)) अणु
			snd_iम_लिखो(buffer, "%2d:  on ", i + 1);
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "%2d: off ", i + 1);
		पूर्ण

		अगर (((i + 1) % 8) == 0) अणु
			snd_iम_लिखो(buffer, "\n");
		पूर्ण
	पूर्ण

	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम snd_rme9652_proc_init(काष्ठा snd_rme9652 *rme9652)
अणु
	snd_card_ro_proc_new(rme9652->card, "rme9652", rme9652,
			     snd_rme9652_proc_पढ़ो);
पूर्ण

अटल व्योम snd_rme9652_मुक्त_buffers(काष्ठा snd_rme9652 *rme9652)
अणु
	snd_hammerfall_मुक्त_buffer(&rme9652->capture_dma_buf, rme9652->pci);
	snd_hammerfall_मुक्त_buffer(&rme9652->playback_dma_buf, rme9652->pci);
पूर्ण

अटल पूर्णांक snd_rme9652_मुक्त(काष्ठा snd_rme9652 *rme9652)
अणु
	अगर (rme9652->irq >= 0)
		rme9652_stop(rme9652);
	snd_rme9652_मुक्त_buffers(rme9652);

	अगर (rme9652->irq >= 0)
		मुक्त_irq(rme9652->irq, (व्योम *)rme9652);
	iounmap(rme9652->iobase);
	अगर (rme9652->port)
		pci_release_regions(rme9652->pci);

	अगर (pci_is_enabled(rme9652->pci))
		pci_disable_device(rme9652->pci);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_initialize_memory(काष्ठा snd_rme9652 *rme9652)
अणु
	अचिन्हित दीर्घ pb_bus, cb_bus;

	अगर (snd_hammerfall_get_buffer(rme9652->pci, &rme9652->capture_dma_buf, RME9652_DMA_AREA_BYTES) < 0 ||
	    snd_hammerfall_get_buffer(rme9652->pci, &rme9652->playback_dma_buf, RME9652_DMA_AREA_BYTES) < 0) अणु
		अगर (rme9652->capture_dma_buf.area)
			snd_dma_मुक्त_pages(&rme9652->capture_dma_buf);
		dev_err(rme9652->card->dev,
			"%s: no buffers available\n", rme9652->card_name);
		वापस -ENOMEM;
	पूर्ण

	/* Align to bus-space 64K boundary */

	cb_bus = ALIGN(rme9652->capture_dma_buf.addr, 0x10000ul);
	pb_bus = ALIGN(rme9652->playback_dma_buf.addr, 0x10000ul);

	/* Tell the card where it is */

	rme9652_ग_लिखो(rme9652, RME9652_rec_buffer, cb_bus);
	rme9652_ग_लिखो(rme9652, RME9652_play_buffer, pb_bus);

	rme9652->capture_buffer = rme9652->capture_dma_buf.area + (cb_bus - rme9652->capture_dma_buf.addr);
	rme9652->playback_buffer = rme9652->playback_dma_buf.area + (pb_bus - rme9652->playback_dma_buf.addr);

	वापस 0;
पूर्ण

अटल व्योम snd_rme9652_set_शेषs(काष्ठा snd_rme9652 *rme9652)
अणु
	अचिन्हित पूर्णांक k;

	/* ASSUMPTION: rme9652->lock is either held, or
	   there is no need to hold it (e.g. during module
	   initialization).
	 */

	/* set शेषs:

	   SPDIF Input via Coax 
	   स्वतःsync घड़ी mode
	   maximum latency (7 = 8192 samples, 64Kbyte buffer,
	   which implies 2 4096 sample, 32Kbyte periods).
	   
	   अगर rev 1.5, initialize the S/PDIF receiver.

	 */

	rme9652->control_रेजिस्टर =
	    RME9652_inp_0 | rme9652_encode_latency(7);

	rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर);

	rme9652_reset_hw_poपूर्णांकer(rme9652);
	rme9652_compute_period_size(rme9652);

	/* शेष: thru off क्रम all channels */

	क्रम (k = 0; k < RME9652_NCHANNELS; ++k)
		rme9652_ग_लिखो(rme9652, RME9652_thru_base + k * 4, 0);

	rme9652->thru_bits = 0;
	rme9652->passthru = 0;

	/* set a शेष rate so that the channel map is set up */

	rme9652_set_rate(rme9652, 48000);
पूर्ण

अटल irqवापस_t snd_rme9652_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_rme9652 *rme9652 = (काष्ठा snd_rme9652 *) dev_id;

	अगर (!(rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर) & RME9652_IRQ)) अणु
		वापस IRQ_NONE;
	पूर्ण

	rme9652_ग_लिखो(rme9652, RME9652_irq_clear, 0);

	अगर (rme9652->capture_substream) अणु
		snd_pcm_period_elapsed(rme9652->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
	पूर्ण

	अगर (rme9652->playback_substream) अणु
		snd_pcm_period_elapsed(rme9652->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल snd_pcm_uframes_t snd_rme9652_hw_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	वापस rme9652_hw_poपूर्णांकer(rme9652);
पूर्ण

अटल अक्षर *rme9652_channel_buffer_location(काष्ठा snd_rme9652 *rme9652,
					     पूर्णांक stream,
					     पूर्णांक channel)

अणु
	पूर्णांक mapped_channel;

	अगर (snd_BUG_ON(channel < 0 || channel >= RME9652_NCHANNELS))
		वापस शून्य;
        
	अगर ((mapped_channel = rme9652->channel_map[channel]) < 0) अणु
		वापस शून्य;
	पूर्ण
	
	अगर (stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		वापस rme9652->capture_buffer +
			(mapped_channel * RME9652_CHANNEL_BUFFER_BYTES);
	पूर्ण अन्यथा अणु
		वापस rme9652->playback_buffer +
			(mapped_channel * RME9652_CHANNEL_BUFFER_BYTES);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_rme9652_playback_copy(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक channel, अचिन्हित दीर्घ pos,
				     व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	अगर (snd_BUG_ON(pos + count > RME9652_CHANNEL_BUFFER_BYTES))
		वापस -EINVAL;

	channel_buf = rme9652_channel_buffer_location (rme9652,
						       substream->pstr->stream,
						       channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	अगर (copy_from_user(channel_buf + pos, src, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
					    पूर्णांक channel, अचिन्हित दीर्घ pos,
					    व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = rme9652_channel_buffer_location(rme9652,
						      substream->pstr->stream,
						      channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_नकल(channel_buf + pos, src, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_capture_copy(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक channel, अचिन्हित दीर्घ pos,
				    व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	अगर (snd_BUG_ON(pos + count > RME9652_CHANNEL_BUFFER_BYTES))
		वापस -EINVAL;

	channel_buf = rme9652_channel_buffer_location (rme9652,
						       substream->pstr->stream,
						       channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	अगर (copy_to_user(dst, channel_buf + pos, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
					   पूर्णांक channel, अचिन्हित दीर्घ pos,
					   व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = rme9652_channel_buffer_location(rme9652,
						      substream->pstr->stream,
						      channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_नकल(dst, channel_buf + pos, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_hw_silence(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक channel, अचिन्हित दीर्घ pos,
				  अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = rme9652_channel_buffer_location (rme9652,
						       substream->pstr->stream,
						       channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_रखो(channel_buf + pos, 0, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_reset(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = rme9652->capture_substream;
	अन्यथा
		other = rme9652->playback_substream;
	अगर (rme9652->running)
		runसमय->status->hw_ptr = rme9652_hw_poपूर्णांकer(rme9652);
	अन्यथा
		runसमय->status->hw_ptr = 0;
	अगर (other) अणु
		काष्ठा snd_pcm_substream *s;
		काष्ठा snd_pcm_runसमय *orunसमय = other->runसमय;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == other) अणु
				orunसमय->status->hw_ptr = runसमय->status->hw_ptr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	पूर्णांक err;
	pid_t this_pid;
	pid_t other_pid;

	spin_lock_irq(&rme9652->lock);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		rme9652->control_रेजिस्टर &= ~(RME9652_PRO | RME9652_Dolby | RME9652_EMP);
		rme9652_ग_लिखो(rme9652, RME9652_control_रेजिस्टर, rme9652->control_रेजिस्टर |= rme9652->creg_spdअगर_stream);
		this_pid = rme9652->playback_pid;
		other_pid = rme9652->capture_pid;
	पूर्ण अन्यथा अणु
		this_pid = rme9652->capture_pid;
		other_pid = rme9652->playback_pid;
	पूर्ण

	अगर ((other_pid > 0) && (this_pid != other_pid)) अणु

		/* The other stream is खोलो, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		अगर ((पूर्णांक)params_rate(params) !=
		    rme9652_adat_sample_rate(rme9652)) अणु
			spin_unlock_irq(&rme9652->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			वापस -EBUSY;
		पूर्ण

		अगर (params_period_size(params) != rme9652->period_bytes / 4) अणु
			spin_unlock_irq(&rme9652->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
			वापस -EBUSY;
		पूर्ण

		/* We're fine. */

		spin_unlock_irq(&rme9652->lock);
 		वापस 0;

	पूर्ण अन्यथा अणु
		spin_unlock_irq(&rme9652->lock);
	पूर्ण

	/* how to make sure that the rate matches an बाह्यally-set one ?
	 */

	अगर ((err = rme9652_set_rate(rme9652, params_rate(params))) < 0) अणु
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
		वापस err;
	पूर्ण

	अगर ((err = rme9652_set_पूर्णांकerrupt_पूर्णांकerval(rme9652, params_period_size(params))) < 0) अणु
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_channel_info(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_channel_info *info)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	पूर्णांक chn;

	अगर (snd_BUG_ON(info->channel >= RME9652_NCHANNELS))
		वापस -EINVAL;

	chn = rme9652->channel_map[array_index_nospec(info->channel,
						      RME9652_NCHANNELS)];
	अगर (chn < 0)
		वापस -EINVAL;

	info->offset = chn * RME9652_CHANNEL_BUFFER_BYTES;
	info->first = 0;
	info->step = 32;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_ioctl(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL1_RESET:
	अणु
		वापस snd_rme9652_reset(substream);
	पूर्ण
	हाल SNDRV_PCM_IOCTL1_CHANNEL_INFO:
	अणु
		काष्ठा snd_pcm_channel_info *info = arg;
		वापस snd_rme9652_channel_info(substream, info);
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

अटल व्योम rme9652_silence_playback(काष्ठा snd_rme9652 *rme9652)
अणु
	स_रखो(rme9652->playback_buffer, 0, RME9652_DMA_AREA_BYTES);
पूर्ण

अटल पूर्णांक snd_rme9652_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;
	पूर्णांक running;
	spin_lock(&rme9652->lock);
	running = rme9652->running;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		running |= 1 << substream->stream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		running &= ~(1 << substream->stream);
		अवरोध;
	शेष:
		snd_BUG();
		spin_unlock(&rme9652->lock);
		वापस -EINVAL;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = rme9652->capture_substream;
	अन्यथा
		other = rme9652->playback_substream;

	अगर (other) अणु
		काष्ठा snd_pcm_substream *s;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == other) अणु
				snd_pcm_trigger_करोne(s, substream);
				अगर (cmd == SNDRV_PCM_TRIGGER_START)
					running |= 1 << s->stream;
				अन्यथा
					running &= ~(1 << s->stream);
				जाओ _ok;
			पूर्ण
		पूर्ण
		अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
			अगर (!(running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) &&
			    substream->stream == SNDRV_PCM_STREAM_CAPTURE)
				rme9652_silence_playback(rme9652);
		पूर्ण अन्यथा अणु
			अगर (running &&
			    substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				rme9652_silence_playback(rme9652);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) 
			rme9652_silence_playback(rme9652);
	पूर्ण
 _ok:
	snd_pcm_trigger_करोne(substream, substream);
	अगर (!rme9652->running && running)
		rme9652_start(rme9652);
	अन्यथा अगर (rme9652->running && !running)
		rme9652_stop(rme9652);
	rme9652->running = running;
	spin_unlock(&rme9652->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rme9652->lock, flags);
	अगर (!rme9652->running)
		rme9652_reset_hw_poपूर्णांकer(rme9652);
	spin_unlock_irqrestore(&rme9652->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_rme9652_playback_subinfo =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_DOUBLE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		(SNDRV_PCM_RATE_44100 | 
				 SNDRV_PCM_RATE_48000 | 
				 SNDRV_PCM_RATE_88200 | 
				 SNDRV_PCM_RATE_96000),
	.rate_min =		44100,
	.rate_max =		96000,
	.channels_min =		10,
	.channels_max =		26,
	.buffer_bytes_max =	RME9652_CHANNEL_BUFFER_BYTES * 26,
	.period_bytes_min =	(64 * 4) * 10,
	.period_bytes_max =	(8192 * 4) * 26,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_rme9652_capture_subinfo =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		(SNDRV_PCM_RATE_44100 | 
				 SNDRV_PCM_RATE_48000 | 
				 SNDRV_PCM_RATE_88200 | 
				 SNDRV_PCM_RATE_96000),
	.rate_min =		44100,
	.rate_max =		96000,
	.channels_min =		10,
	.channels_max =		26,
	.buffer_bytes_max =	RME9652_CHANNEL_BUFFER_BYTES *26,
	.period_bytes_min =	(64 * 4) * 10,
	.period_bytes_max =	(8192 * 4) * 26,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक period_sizes[] = अणु 64, 128, 256, 512, 1024, 2048, 4096, 8192 पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_period_sizes = अणु
	.count = ARRAY_SIZE(period_sizes),
	.list = period_sizes,
	.mask = 0
पूर्ण;

अटल पूर्णांक snd_rme9652_hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_rme9652 *rme9652 = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अचिन्हित पूर्णांक list[2] = अणु rme9652->ds_channels, rme9652->ss_channels पूर्ण;
	वापस snd_पूर्णांकerval_list(c, 2, list, 0);
पूर्ण

अटल पूर्णांक snd_rme9652_hw_rule_channels_rate(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_rme9652 *rme9652 = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (r->min > 48000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = rme9652->ds_channels,
			.max = rme9652->ds_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->max < 88200) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = rme9652->ss_channels,
			.max = rme9652->ss_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_hw_rule_rate_channels(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_rme9652 *rme9652 = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (c->min >= rme9652->ss_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 44100,
			.max = 48000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= rme9652->ds_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 88200,
			.max = 96000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	spin_lock_irq(&rme9652->lock);

	snd_pcm_set_sync(substream);

        runसमय->hw = snd_rme9652_playback_subinfo;
	runसमय->dma_area = rme9652->playback_buffer;
	runसमय->dma_bytes = RME9652_DMA_AREA_BYTES;

	अगर (rme9652->capture_substream == शून्य) अणु
		rme9652_stop(rme9652);
		rme9652_set_thru(rme9652, -1, 0);
	पूर्ण

	rme9652->playback_pid = current->pid;
	rme9652->playback_substream = substream;

	spin_unlock_irq(&rme9652->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, &hw_स्थिरraपूर्णांकs_period_sizes);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_rme9652_hw_rule_channels, rme9652,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_rme9652_hw_rule_channels_rate, rme9652,
			     SNDRV_PCM_HW_PARAM_RATE, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
			     snd_rme9652_hw_rule_rate_channels, rme9652,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	rme9652->creg_spdअगर_stream = rme9652->creg_spdअगर;
	rme9652->spdअगर_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(rme9652->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &rme9652->spdअगर_ctl->id);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_playback_release(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme9652->lock);

	rme9652->playback_pid = -1;
	rme9652->playback_substream = शून्य;

	spin_unlock_irq(&rme9652->lock);

	rme9652->spdअगर_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(rme9652->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &rme9652->spdअगर_ctl->id);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_rme9652_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	spin_lock_irq(&rme9652->lock);

	snd_pcm_set_sync(substream);

	runसमय->hw = snd_rme9652_capture_subinfo;
	runसमय->dma_area = rme9652->capture_buffer;
	runसमय->dma_bytes = RME9652_DMA_AREA_BYTES;

	अगर (rme9652->playback_substream == शून्य) अणु
		rme9652_stop(rme9652);
		rme9652_set_thru(rme9652, -1, 0);
	पूर्ण

	rme9652->capture_pid = current->pid;
	rme9652->capture_substream = substream;

	spin_unlock_irq(&rme9652->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, &hw_स्थिरraपूर्णांकs_period_sizes);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_rme9652_hw_rule_channels, rme9652,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_rme9652_hw_rule_channels_rate, rme9652,
			     SNDRV_PCM_HW_PARAM_RATE, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
			     snd_rme9652_hw_rule_rate_channels, rme9652,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_capture_release(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme9652->lock);

	rme9652->capture_pid = -1;
	rme9652->capture_substream = शून्य;

	spin_unlock_irq(&rme9652->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_rme9652_playback_ops = अणु
	.खोलो =		snd_rme9652_playback_खोलो,
	.बंद =	snd_rme9652_playback_release,
	.ioctl =	snd_rme9652_ioctl,
	.hw_params =	snd_rme9652_hw_params,
	.prepare =	snd_rme9652_prepare,
	.trigger =	snd_rme9652_trigger,
	.poपूर्णांकer =	snd_rme9652_hw_poपूर्णांकer,
	.copy_user =	snd_rme9652_playback_copy,
	.copy_kernel =	snd_rme9652_playback_copy_kernel,
	.fill_silence =	snd_rme9652_hw_silence,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme9652_capture_ops = अणु
	.खोलो =		snd_rme9652_capture_खोलो,
	.बंद =	snd_rme9652_capture_release,
	.ioctl =	snd_rme9652_ioctl,
	.hw_params =	snd_rme9652_hw_params,
	.prepare =	snd_rme9652_prepare,
	.trigger =	snd_rme9652_trigger,
	.poपूर्णांकer =	snd_rme9652_hw_poपूर्णांकer,
	.copy_user =	snd_rme9652_capture_copy,
	.copy_kernel =	snd_rme9652_capture_copy_kernel,
पूर्ण;

अटल पूर्णांक snd_rme9652_create_pcm(काष्ठा snd_card *card,
				  काष्ठा snd_rme9652 *rme9652)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(card,
			       rme9652->card_name,
			       0, 1, 1, &pcm)) < 0) अणु
		वापस err;
	पूर्ण

	rme9652->pcm = pcm;
	pcm->निजी_data = rme9652;
	म_नकल(pcm->name, rme9652->card_name);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme9652_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme9652_capture_ops);

	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme9652_create(काष्ठा snd_card *card,
			      काष्ठा snd_rme9652 *rme9652,
			      पूर्णांक precise_ptr)
अणु
	काष्ठा pci_dev *pci = rme9652->pci;
	पूर्णांक err;
	पूर्णांक status;
	अचिन्हित लघु rev;

	rme9652->irq = -1;
	rme9652->card = card;

	pci_पढ़ो_config_word(rme9652->pci, PCI_CLASS_REVISION, &rev);

	चयन (rev & 0xff) अणु
	हाल 3:
	हाल 4:
	हाल 8:
	हाल 9:
		अवरोध;

	शेष:
		/* who knows? */
		वापस -ENODEV;
	पूर्ण

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	spin_lock_init(&rme9652->lock);

	अगर ((err = pci_request_regions(pci, "rme9652")) < 0)
		वापस err;
	rme9652->port = pci_resource_start(pci, 0);
	rme9652->iobase = ioremap(rme9652->port, RME9652_IO_EXTENT);
	अगर (rme9652->iobase == शून्य) अणु
		dev_err(card->dev, "unable to remap region 0x%lx-0x%lx\n",
			rme9652->port, rme9652->port + RME9652_IO_EXTENT - 1);
		वापस -EBUSY;
	पूर्ण
	
	अगर (request_irq(pci->irq, snd_rme9652_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, rme9652)) अणु
		dev_err(card->dev, "unable to request IRQ %d\n", pci->irq);
		वापस -EBUSY;
	पूर्ण
	rme9652->irq = pci->irq;
	card->sync_irq = rme9652->irq;
	rme9652->precise_ptr = precise_ptr;

	/* Determine the h/w rev level of the card. This seems like
	   a particularly kludgy way to encode it, but its what RME
	   chose to करो, so we follow them ...
	*/

	status = rme9652_पढ़ो(rme9652, RME9652_status_रेजिस्टर);
	अगर (rme9652_decode_spdअगर_rate(status&RME9652_F) == 1) अणु
		rme9652->hw_rev = 15;
	पूर्ण अन्यथा अणु
		rme9652->hw_rev = 11;
	पूर्ण

	/* Dअगरferentiate between the standard Hammerfall, and the
	   "Light", which करोes not have the expansion board. This
	   method comes from inक्रमmation received from Mathhias
	   Clausen at RME. Display the EEPROM and h/w revID where
	   relevant.  
	*/

	चयन (rev) अणु
	हाल 8: /* original eprom */
		म_नकल(card->driver, "RME9636");
		अगर (rme9652->hw_rev == 15) अणु
			rme9652->card_name = "RME Digi9636 (Rev 1.5)";
		पूर्ण अन्यथा अणु
			rme9652->card_name = "RME Digi9636";
		पूर्ण
		rme9652->ss_channels = RME9636_NCHANNELS;
		अवरोध;
	हाल 9: /* W36_G EPROM */
		म_नकल(card->driver, "RME9636");
		rme9652->card_name = "RME Digi9636 (Rev G)";
		rme9652->ss_channels = RME9636_NCHANNELS;
		अवरोध;
	हाल 4: /* W52_G EPROM */
		म_नकल(card->driver, "RME9652");
		rme9652->card_name = "RME Digi9652 (Rev G)";
		rme9652->ss_channels = RME9652_NCHANNELS;
		अवरोध;
	हाल 3: /* original eprom */
		म_नकल(card->driver, "RME9652");
		अगर (rme9652->hw_rev == 15) अणु
			rme9652->card_name = "RME Digi9652 (Rev 1.5)";
		पूर्ण अन्यथा अणु
			rme9652->card_name = "RME Digi9652";
		पूर्ण
		rme9652->ss_channels = RME9652_NCHANNELS;
		अवरोध;
	पूर्ण

	rme9652->ds_channels = (rme9652->ss_channels - 2) / 2 + 2;

	pci_set_master(rme9652->pci);

	अगर ((err = snd_rme9652_initialize_memory(rme9652)) < 0) अणु
		वापस err;
	पूर्ण

	अगर ((err = snd_rme9652_create_pcm(card, rme9652)) < 0) अणु
		वापस err;
	पूर्ण

	अगर ((err = snd_rme9652_create_controls(card, rme9652)) < 0) अणु
		वापस err;
	पूर्ण

	snd_rme9652_proc_init(rme9652);

	rme9652->last_spdअगर_sample_rate = -1;
	rme9652->last_adat_sample_rate = -1;
	rme9652->playback_pid = -1;
	rme9652->capture_pid = -1;
	rme9652->capture_substream = शून्य;
	rme9652->playback_substream = शून्य;

	snd_rme9652_set_शेषs(rme9652);

	अगर (rme9652->hw_rev == 15) अणु
		rme9652_initialize_spdअगर_receiver (rme9652);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_rme9652_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_rme9652 *rme9652 = (काष्ठा snd_rme9652 *) card->निजी_data;

	अगर (rme9652)
		snd_rme9652_मुक्त(rme9652);
पूर्ण

अटल पूर्णांक snd_rme9652_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_rme9652 *rme9652;
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_rme9652), &card);

	अगर (err < 0)
		वापस err;

	rme9652 = (काष्ठा snd_rme9652 *) card->निजी_data;
	card->निजी_मुक्त = snd_rme9652_card_मुक्त;
	rme9652->dev = dev;
	rme9652->pci = pci;
	err = snd_rme9652_create(card, rme9652, precise_ptr[dev]);
	अगर (err)
		जाओ मुक्त_card;

	म_नकल(card->लघुname, rme9652->card_name);

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d",
		card->लघुname, rme9652->port, rme9652->irq);
	err = snd_card_रेजिस्टर(card);
	अगर (err) अणु
मुक्त_card:
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_rme9652_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver rme9652_driver = अणु
	.name	  = KBUILD_MODNAME,
	.id_table = snd_rme9652_ids,
	.probe	  = snd_rme9652_probe,
	.हटाओ	  = snd_rme9652_हटाओ,
पूर्ण;

module_pci_driver(rme9652_driver);
