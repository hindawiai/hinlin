<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "saa7164.h"

MODULE_DESCRIPTION("Driver for NXP SAA7164 based TV cards");
MODULE_AUTHOR("Steven Toth <stoth@kernellabs.com>");
MODULE_LICENSE("GPL");

/*
 *  1 Basic
 *  2
 *  4 i2c
 *  8 api
 * 16 cmd
 * 32 bus
 */

अचिन्हित पूर्णांक saa_debug;
module_param_named(debug, saa_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

अटल अचिन्हित पूर्णांक fw_debug;
module_param(fw_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(fw_debug, "Firmware debug level def:2");

अचिन्हित पूर्णांक encoder_buffers = SAA7164_MAX_ENCODER_BUFFERS;
module_param(encoder_buffers, पूर्णांक, 0644);
MODULE_PARM_DESC(encoder_buffers, "Total buffers in read queue 16-512 def:64");

अचिन्हित पूर्णांक vbi_buffers = SAA7164_MAX_VBI_BUFFERS;
module_param(vbi_buffers, पूर्णांक, 0644);
MODULE_PARM_DESC(vbi_buffers, "Total buffers in read queue 16-512 def:64");

अचिन्हित पूर्णांक रुकोsecs = 10;
module_param(रुकोsecs, पूर्णांक, 0644);
MODULE_PARM_DESC(रुकोsecs, "timeout on firmware messages");

अटल अचिन्हित पूर्णांक card[]  = अणु[0 ... (SAA7164_MAXBOARDS - 1)] = UNSET पूर्ण;
module_param_array(card,  पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "card type");

अटल अचिन्हित पूर्णांक prपूर्णांक_histogram = 64;
module_param(prपूर्णांक_histogram, पूर्णांक, 0644);
MODULE_PARM_DESC(prपूर्णांक_histogram, "print histogram values once");

अचिन्हित पूर्णांक crc_checking = 1;
module_param(crc_checking, पूर्णांक, 0644);
MODULE_PARM_DESC(crc_checking, "enable crc sanity checking on buffers");

अटल अचिन्हित पूर्णांक guard_checking = 1;
module_param(guard_checking, पूर्णांक, 0644);
MODULE_PARM_DESC(guard_checking,
	"enable dma sanity checking for buffer overruns");

अटल bool enable_msi = true;
module_param(enable_msi, bool, 0444);
MODULE_PARM_DESC(enable_msi,
		"enable the use of an msi interrupt if available");

अटल अचिन्हित पूर्णांक saa7164_devcount;

अटल DEFINE_MUTEX(devlist);
LIST_HEAD(saa7164_devlist);

#घोषणा INT_SIZE 16

अटल व्योम saa7164_pack_verअगरier(काष्ठा saa7164_buffer *buf)
अणु
	u8 *p = (u8 *)buf->cpu;
	पूर्णांक i;

	क्रम (i = 0; i < buf->actual_size; i += 2048) अणु

		अगर ((*(p + i + 0) != 0x00) || (*(p + i + 1) != 0x00) ||
			(*(p + i + 2) != 0x01) || (*(p + i + 3) != 0xBA)) अणु
			prपूर्णांकk(KERN_ERR "No pack at 0x%x\n", i);
#अगर 0
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
				       p + 1, 32, false);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा FIXED_VIDEO_PID 0xf1
#घोषणा FIXED_AUDIO_PID 0xf2

अटल व्योम saa7164_ts_verअगरier(काष्ठा saa7164_buffer *buf)
अणु
	काष्ठा saa7164_port *port = buf->port;
	u32 i;
	u8 cc, a;
	u16 pid;
	u8 *bufcpu = (u8 *)buf->cpu;

	port->sync_errors = 0;
	port->v_cc_errors = 0;
	port->a_cc_errors = 0;

	क्रम (i = 0; i < buf->actual_size; i += 188) अणु
		अगर (*(bufcpu + i) != 0x47)
			port->sync_errors++;

		/* TODO: Query pid lower 8 bits, ignoring upper bits पूर्णांकensionally */
		pid = ((*(bufcpu + i + 1) & 0x1f) << 8) | *(bufcpu + i + 2);
		cc = *(bufcpu + i + 3) & 0x0f;

		अगर (pid == FIXED_VIDEO_PID) अणु
			a = ((port->last_v_cc + 1) & 0x0f);
			अगर (a != cc) अणु
				prपूर्णांकk(KERN_ERR "video cc last = %x current = %x i = %d\n",
					port->last_v_cc, cc, i);
				port->v_cc_errors++;
			पूर्ण

			port->last_v_cc = cc;
		पूर्ण अन्यथा
		अगर (pid == FIXED_AUDIO_PID) अणु
			a = ((port->last_a_cc + 1) & 0x0f);
			अगर (a != cc) अणु
				prपूर्णांकk(KERN_ERR "audio cc last = %x current = %x i = %d\n",
					port->last_a_cc, cc, i);
				port->a_cc_errors++;
			पूर्ण

			port->last_a_cc = cc;
		पूर्ण

	पूर्ण

	/* Only report errors अगर we've been through this function at least
	 * once alपढ़ोy and the cached cc values are primed. First समय through
	 * always generates errors.
	 */
	अगर (port->v_cc_errors && (port->करोne_first_पूर्णांकerrupt > 1))
		prपूर्णांकk(KERN_ERR "video pid cc, %d errors\n", port->v_cc_errors);

	अगर (port->a_cc_errors && (port->करोne_first_पूर्णांकerrupt > 1))
		prपूर्णांकk(KERN_ERR "audio pid cc, %d errors\n", port->a_cc_errors);

	अगर (port->sync_errors && (port->करोne_first_पूर्णांकerrupt > 1))
		prपूर्णांकk(KERN_ERR "sync_errors = %d\n", port->sync_errors);

	अगर (port->करोne_first_पूर्णांकerrupt == 1)
		port->करोne_first_पूर्णांकerrupt++;
पूर्ण

अटल व्योम saa7164_histogram_reset(काष्ठा saa7164_histogram *hg, अक्षर *name)
अणु
	पूर्णांक i;

	स_रखो(hg, 0, माप(काष्ठा saa7164_histogram));
	strscpy(hg->name, name, माप(hg->name));

	/* First 30ms x 1ms */
	क्रम (i = 0; i < 30; i++)
		hg->counter1[0 + i].val = i;

	/* 30 - 200ms x 10ms  */
	क्रम (i = 0; i < 18; i++)
		hg->counter1[30 + i].val = 30 + (i * 10);

	/* 200 - 2000ms x 100ms  */
	क्रम (i = 0; i < 15; i++)
		hg->counter1[48 + i].val = 200 + (i * 200);

	/* Catch all massive value (2secs) */
	hg->counter1[55].val = 2000;

	/* Catch all massive value (4secs) */
	hg->counter1[56].val = 4000;

	/* Catch all massive value (8secs) */
	hg->counter1[57].val = 8000;

	/* Catch all massive value (15secs) */
	hg->counter1[58].val = 15000;

	/* Catch all massive value (30secs) */
	hg->counter1[59].val = 30000;

	/* Catch all massive value (60secs) */
	hg->counter1[60].val = 60000;

	/* Catch all massive value (5mins) */
	hg->counter1[61].val = 300000;

	/* Catch all massive value (15mins) */
	hg->counter1[62].val = 900000;

	/* Catch all massive values (1hr) */
	hg->counter1[63].val = 3600000;
पूर्ण

व्योम saa7164_histogram_update(काष्ठा saa7164_histogram *hg, u32 val)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 64; i++) अणु
		अगर (val <= hg->counter1[i].val) अणु
			hg->counter1[i].count++;
			hg->counter1[i].update_समय = jअगरfies;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम saa7164_histogram_prपूर्णांक(काष्ठा saa7164_port *port,
	काष्ठा saa7164_histogram *hg)
अणु
	u32 entries = 0;
	पूर्णांक i;

	prपूर्णांकk(KERN_ERR "Histogram named %s (ms, count, last_update_jiffy)\n", hg->name);
	क्रम (i = 0; i < 64; i++) अणु
		अगर (hg->counter1[i].count == 0)
			जारी;

		prपूर्णांकk(KERN_ERR " %4d %12d %Ld\n",
			hg->counter1[i].val,
			hg->counter1[i].count,
			hg->counter1[i].update_समय);

		entries++;
	पूर्ण
	prपूर्णांकk(KERN_ERR "Total: %d\n", entries);
पूर्ण

अटल व्योम saa7164_work_enchandler_helper(काष्ठा saa7164_port *port, पूर्णांक bufnr)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf = शून्य;
	काष्ठा saa7164_user_buffer *ubuf = शून्य;
	काष्ठा list_head *c, *n;
	पूर्णांक i = 0;
	u8 *p;

	mutex_lock(&port->dmaqueue_lock);
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु

		buf = list_entry(c, काष्ठा saa7164_buffer, list);
		अगर (i++ > port->hwcfg.buffercount) अणु
			prपूर्णांकk(KERN_ERR "%s() illegal i count %d\n",
				__func__, i);
			अवरोध;
		पूर्ण

		अगर (buf->idx == bufnr) अणु

			/* Found the buffer, deal with it */
			dprपूर्णांकk(DBGLVL_IRQ, "%s() bufnr: %d\n", __func__, bufnr);

			अगर (crc_checking) अणु
				/* Throw a new checksum on the dma buffer */
				buf->crc = crc32(0, buf->cpu, buf->actual_size);
			पूर्ण

			अगर (guard_checking) अणु
				p = (u8 *)buf->cpu;
				अगर ((*(p + buf->actual_size + 0) != 0xff) ||
					(*(p + buf->actual_size + 1) != 0xff) ||
					(*(p + buf->actual_size + 2) != 0xff) ||
					(*(p + buf->actual_size + 3) != 0xff) ||
					(*(p + buf->actual_size + 0x10) != 0xff) ||
					(*(p + buf->actual_size + 0x11) != 0xff) ||
					(*(p + buf->actual_size + 0x12) != 0xff) ||
					(*(p + buf->actual_size + 0x13) != 0xff)) अणु
						prपूर्णांकk(KERN_ERR "%s() buf %p guard buffer breach\n",
							__func__, buf);
#अगर 0
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
				       p + buf->actual_size - 32, 64, false);
#पूर्ण_अगर
				पूर्ण
			पूर्ण

			अगर ((port->nr != SAA7164_PORT_VBI1) && (port->nr != SAA7164_PORT_VBI2)) अणु
				/* Validate the incoming buffer content */
				अगर (port->encoder_params.stream_type == V4L2_MPEG_STREAM_TYPE_MPEG2_TS)
					saa7164_ts_verअगरier(buf);
				अन्यथा अगर (port->encoder_params.stream_type == V4L2_MPEG_STREAM_TYPE_MPEG2_PS)
					saa7164_pack_verअगरier(buf);
			पूर्ण

			/* find a मुक्त user buffer and clone to it */
			अगर (!list_empty(&port->list_buf_मुक्त.list)) अणु

				/* Pull the first buffer from the used list */
				ubuf = list_first_entry(&port->list_buf_मुक्त.list,
					काष्ठा saa7164_user_buffer, list);

				अगर (buf->actual_size <= ubuf->actual_size) अणु

					स_नकल(ubuf->data, buf->cpu, ubuf->actual_size);

					अगर (crc_checking) अणु
						/* Throw a new checksum on the पढ़ो buffer */
						ubuf->crc = crc32(0, ubuf->data, ubuf->actual_size);
					पूर्ण

					/* Requeue the buffer on the मुक्त list */
					ubuf->pos = 0;

					list_move_tail(&ubuf->list,
						&port->list_buf_used.list);

					/* Flag any userland रुकोers */
					wake_up_पूर्णांकerruptible(&port->रुको_पढ़ो);

				पूर्ण अन्यथा अणु
					prपूर्णांकk(KERN_ERR "buf %p bufsize fails match\n", buf);
				पूर्ण

			पूर्ण अन्यथा
				prपूर्णांकk(KERN_ERR "encirq no free buffers, increase param encoder_buffers\n");

			/* Ensure offset पूर्णांकo buffer reमुख्यs 0, fill buffer
			 * with known bad data. We check क्रम this data at a later poपूर्णांक
			 * in समय. */
			saa7164_buffer_zero_offsets(port, bufnr);
			स_रखो(buf->cpu, 0xff, buf->pci_size);
			अगर (crc_checking) अणु
				/* Throw yet aanother new checksum on the dma buffer */
				buf->crc = crc32(0, buf->cpu, buf->actual_size);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);
पूर्ण

अटल व्योम saa7164_work_enchandler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा saa7164_port *port =
		container_of(w, काष्ठा saa7164_port, workenc);
	काष्ठा saa7164_dev *dev = port->dev;

	u32 wp, mcb, rp, cnt = 0;

	port->last_svc_msecs_dअगरf = port->last_svc_msecs;
	port->last_svc_msecs = jअगरfies_to_msecs(jअगरfies);

	port->last_svc_msecs_dअगरf = port->last_svc_msecs -
		port->last_svc_msecs_dअगरf;

	saa7164_histogram_update(&port->svc_पूर्णांकerval,
		port->last_svc_msecs_dअगरf);

	port->last_irq_svc_msecs_dअगरf = port->last_svc_msecs -
		port->last_irq_msecs;

	saa7164_histogram_update(&port->irq_svc_पूर्णांकerval,
		port->last_irq_svc_msecs_dअगरf);

	dprपूर्णांकk(DBGLVL_IRQ,
		"%s() %Ldms elapsed irq->deferred %Ldms wp: %d rp: %d\n",
		__func__,
		port->last_svc_msecs_dअगरf,
		port->last_irq_svc_msecs_dअगरf,
		port->last_svc_wp,
		port->last_svc_rp
		);

	/* Current ग_लिखो position */
	wp = saa7164_पढ़ोl(port->bufcounter);
	अगर (wp > (port->hwcfg.buffercount - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s() illegal buf count %d\n", __func__, wp);
		वापस;
	पूर्ण

	/* Most current complete buffer */
	अगर (wp == 0)
		mcb = (port->hwcfg.buffercount - 1);
	अन्यथा
		mcb = wp - 1;

	जबतक (1) अणु
		अगर (port->करोne_first_पूर्णांकerrupt == 0) अणु
			port->करोne_first_पूर्णांकerrupt++;
			rp = mcb;
		पूर्ण अन्यथा
			rp = (port->last_svc_rp + 1) % 8;

		अगर (rp > (port->hwcfg.buffercount - 1)) अणु
			prपूर्णांकk(KERN_ERR "%s() illegal rp count %d\n", __func__, rp);
			अवरोध;
		पूर्ण

		saa7164_work_enchandler_helper(port, rp);
		port->last_svc_rp = rp;
		cnt++;

		अगर (rp == mcb)
			अवरोध;
	पूर्ण

	/* TODO: Convert this पूर्णांकo a /proc/saa7164 style पढ़ोable file */
	अगर (prपूर्णांक_histogram == port->nr) अणु
		saa7164_histogram_prपूर्णांक(port, &port->irq_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->svc_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->irq_svc_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->पढ़ो_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->poll_पूर्णांकerval);
		/* TODO: fix this to preserve any previous state */
		prपूर्णांक_histogram = 64 + port->nr;
	पूर्ण
पूर्ण

अटल व्योम saa7164_work_vbihandler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा saa7164_port *port =
		container_of(w, काष्ठा saa7164_port, workenc);
	काष्ठा saa7164_dev *dev = port->dev;

	u32 wp, mcb, rp, cnt = 0;

	port->last_svc_msecs_dअगरf = port->last_svc_msecs;
	port->last_svc_msecs = jअगरfies_to_msecs(jअगरfies);
	port->last_svc_msecs_dअगरf = port->last_svc_msecs -
		port->last_svc_msecs_dअगरf;

	saa7164_histogram_update(&port->svc_पूर्णांकerval,
		port->last_svc_msecs_dअगरf);

	port->last_irq_svc_msecs_dअगरf = port->last_svc_msecs -
		port->last_irq_msecs;

	saa7164_histogram_update(&port->irq_svc_पूर्णांकerval,
		port->last_irq_svc_msecs_dअगरf);

	dprपूर्णांकk(DBGLVL_IRQ,
		"%s() %Ldms elapsed irq->deferred %Ldms wp: %d rp: %d\n",
		__func__,
		port->last_svc_msecs_dअगरf,
		port->last_irq_svc_msecs_dअगरf,
		port->last_svc_wp,
		port->last_svc_rp
		);

	/* Current ग_लिखो position */
	wp = saa7164_पढ़ोl(port->bufcounter);
	अगर (wp > (port->hwcfg.buffercount - 1)) अणु
		prपूर्णांकk(KERN_ERR "%s() illegal buf count %d\n", __func__, wp);
		वापस;
	पूर्ण

	/* Most current complete buffer */
	अगर (wp == 0)
		mcb = (port->hwcfg.buffercount - 1);
	अन्यथा
		mcb = wp - 1;

	जबतक (1) अणु
		अगर (port->करोne_first_पूर्णांकerrupt == 0) अणु
			port->करोne_first_पूर्णांकerrupt++;
			rp = mcb;
		पूर्ण अन्यथा
			rp = (port->last_svc_rp + 1) % 8;

		अगर (rp > (port->hwcfg.buffercount - 1)) अणु
			prपूर्णांकk(KERN_ERR "%s() illegal rp count %d\n", __func__, rp);
			अवरोध;
		पूर्ण

		saa7164_work_enchandler_helper(port, rp);
		port->last_svc_rp = rp;
		cnt++;

		अगर (rp == mcb)
			अवरोध;
	पूर्ण

	/* TODO: Convert this पूर्णांकo a /proc/saa7164 style पढ़ोable file */
	अगर (prपूर्णांक_histogram == port->nr) अणु
		saa7164_histogram_prपूर्णांक(port, &port->irq_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->svc_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->irq_svc_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->पढ़ो_पूर्णांकerval);
		saa7164_histogram_prपूर्णांक(port, &port->poll_पूर्णांकerval);
		/* TODO: fix this to preserve any previous state */
		prपूर्णांक_histogram = 64 + port->nr;
	पूर्ण
पूर्ण

अटल व्योम saa7164_work_cmdhandler(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा saa7164_dev *dev = container_of(w, काष्ठा saa7164_dev, workcmd);

	/* Wake up any complete commands */
	saa7164_irq_dequeue(dev);
पूर्ण

अटल व्योम saa7164_buffer_deliver(काष्ठा saa7164_buffer *buf)
अणु
	काष्ठा saa7164_port *port = buf->port;

	/* Feed the transport payload पूर्णांकo the kernel demux */
	dvb_dmx_swfilter_packets(&port->dvb.demux, (u8 *)buf->cpu,
		SAA7164_TS_NUMBER_OF_LINES);

पूर्ण

अटल irqवापस_t saa7164_irq_vbi(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	/* Store old समय */
	port->last_irq_msecs_dअगरf = port->last_irq_msecs;

	/* Collect new stats */
	port->last_irq_msecs = jअगरfies_to_msecs(jअगरfies);

	/* Calculate stats */
	port->last_irq_msecs_dअगरf = port->last_irq_msecs -
		port->last_irq_msecs_dअगरf;

	saa7164_histogram_update(&port->irq_पूर्णांकerval,
		port->last_irq_msecs_dअगरf);

	dprपूर्णांकk(DBGLVL_IRQ, "%s() %Ldms elapsed\n", __func__,
		port->last_irq_msecs_dअगरf);

	/* Tis calls the vbi irq handler */
	schedule_work(&port->workenc);
	वापस 0;
पूर्ण

अटल irqवापस_t saa7164_irq_encoder(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	/* Store old समय */
	port->last_irq_msecs_dअगरf = port->last_irq_msecs;

	/* Collect new stats */
	port->last_irq_msecs = jअगरfies_to_msecs(jअगरfies);

	/* Calculate stats */
	port->last_irq_msecs_dअगरf = port->last_irq_msecs -
		port->last_irq_msecs_dअगरf;

	saa7164_histogram_update(&port->irq_पूर्णांकerval,
		port->last_irq_msecs_dअगरf);

	dprपूर्णांकk(DBGLVL_IRQ, "%s() %Ldms elapsed\n", __func__,
		port->last_irq_msecs_dअगरf);

	schedule_work(&port->workenc);
	वापस 0;
पूर्ण

अटल irqवापस_t saa7164_irq_ts(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा list_head *c, *n;
	पूर्णांक wp, i = 0, rp;

	/* Find the current ग_लिखो poपूर्णांक from the hardware */
	wp = saa7164_पढ़ोl(port->bufcounter);

	BUG_ON(wp > (port->hwcfg.buffercount - 1));

	/* Find the previous buffer to the current ग_लिखो poपूर्णांक */
	अगर (wp == 0)
		rp = (port->hwcfg.buffercount - 1);
	अन्यथा
		rp = wp - 1;

	/* Lookup the WP in the buffer list */
	/* TODO: turn this पूर्णांकo a worker thपढ़ो */
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		buf = list_entry(c, काष्ठा saa7164_buffer, list);
		BUG_ON(i > port->hwcfg.buffercount);
		i++;

		अगर (buf->idx == rp) अणु
			/* Found the buffer, deal with it */
			dprपूर्णांकk(DBGLVL_IRQ, "%s() wp: %d processing: %d\n",
				__func__, wp, rp);
			saa7164_buffer_deliver(buf);
			अवरोध;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

/* Primary IRQ handler and dispatch mechanism */
अटल irqवापस_t saa7164_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा saa7164_dev *dev = dev_id;
	काष्ठा saa7164_port *porta, *portb, *portc, *portd, *porte, *portf;

	u32 पूर्णांकid, पूर्णांकstat[INT_SIZE/4];
	पूर्णांक i, handled = 0, bit;

	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s() No device specified\n", __func__);
		handled = 0;
		जाओ out;
	पूर्ण

	porta = &dev->ports[SAA7164_PORT_TS1];
	portb = &dev->ports[SAA7164_PORT_TS2];
	portc = &dev->ports[SAA7164_PORT_ENC1];
	portd = &dev->ports[SAA7164_PORT_ENC2];
	porte = &dev->ports[SAA7164_PORT_VBI1];
	portf = &dev->ports[SAA7164_PORT_VBI2];

	/* Check that the hardware is accessible. If the status bytes are
	 * 0xFF then the device is not accessible, the the IRQ beदीर्घs
	 * to another driver.
	 * 4 x u32 पूर्णांकerrupt रेजिस्टरs.
	 */
	क्रम (i = 0; i < INT_SIZE/4; i++) अणु

		/* TODO: Convert पूर्णांकo saa7164_पढ़ोl() */
		/* Read the 4 hardware पूर्णांकerrupt रेजिस्टरs */
		पूर्णांकstat[i] = saa7164_पढ़ोl(dev->पूर्णांक_status + (i * 4));

		अगर (पूर्णांकstat[i])
			handled = 1;
	पूर्ण
	अगर (handled == 0)
		जाओ out;

	/* For each of the HW पूर्णांकerrupt रेजिस्टरs */
	क्रम (i = 0; i < INT_SIZE/4; i++) अणु

		अगर (पूर्णांकstat[i]) अणु
			/* Each function of the board has it's own पूर्णांकerruptid.
			 * Find the function that triggered then call
			 * it's handler.
			 */
			क्रम (bit = 0; bit < 32; bit++) अणु

				अगर (((पूर्णांकstat[i] >> bit) & 0x00000001) == 0)
					जारी;

				/* Calculate the पूर्णांकerrupt id (0x00 to 0x7f) */

				पूर्णांकid = (i * 32) + bit;
				अगर (पूर्णांकid == dev->पूर्णांकfdesc.bInterruptId) अणु
					/* A response to an cmd/api call */
					schedule_work(&dev->workcmd);
				पूर्ण अन्यथा अगर (पूर्णांकid == porta->hwcfg.पूर्णांकerruptid) अणु

					/* Transport path 1 */
					saa7164_irq_ts(porta);

				पूर्ण अन्यथा अगर (पूर्णांकid == portb->hwcfg.पूर्णांकerruptid) अणु

					/* Transport path 2 */
					saa7164_irq_ts(portb);

				पूर्ण अन्यथा अगर (पूर्णांकid == portc->hwcfg.पूर्णांकerruptid) अणु

					/* Encoder path 1 */
					saa7164_irq_encoder(portc);

				पूर्ण अन्यथा अगर (पूर्णांकid == portd->hwcfg.पूर्णांकerruptid) अणु

					/* Encoder path 2 */
					saa7164_irq_encoder(portd);

				पूर्ण अन्यथा अगर (पूर्णांकid == porte->hwcfg.पूर्णांकerruptid) अणु

					/* VBI path 1 */
					saa7164_irq_vbi(porte);

				पूर्ण अन्यथा अगर (पूर्णांकid == portf->hwcfg.पूर्णांकerruptid) अणु

					/* VBI path 2 */
					saa7164_irq_vbi(portf);

				पूर्ण अन्यथा अणु
					/* Find the function */
					dprपूर्णांकk(DBGLVL_IRQ,
						"%s() unhandled interrupt reg 0x%x bit 0x%x intid = 0x%x\n",
						__func__, i, bit, पूर्णांकid);
				पूर्ण
			पूर्ण

			/* Ack it */
			saa7164_ग_लिखोl(dev->पूर्णांक_ack + (i * 4), पूर्णांकstat[i]);

		पूर्ण
	पूर्ण
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

व्योम saa7164_getfirmwarestatus(काष्ठा saa7164_dev *dev)
अणु
	काष्ठा saa7164_fw_status *s = &dev->fw_status;

	dev->fw_status.status = saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_STATUS);
	dev->fw_status.mode = saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_MODE);
	dev->fw_status.spec = saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_SPEC);
	dev->fw_status.inst = saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_INST);
	dev->fw_status.cpuload = saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_CPULOAD);
	dev->fw_status.reमुख्यheap =
		saa7164_पढ़ोl(SAA_DEVICE_SYSINIT_REMAINHEAP);

	dprपूर्णांकk(1, "Firmware status:\n");
	dprपूर्णांकk(1, " .status     = 0x%08x\n", s->status);
	dprपूर्णांकk(1, " .mode       = 0x%08x\n", s->mode);
	dprपूर्णांकk(1, " .spec       = 0x%08x\n", s->spec);
	dprपूर्णांकk(1, " .inst       = 0x%08x\n", s->inst);
	dprपूर्णांकk(1, " .cpuload    = 0x%08x\n", s->cpuload);
	dprपूर्णांकk(1, " .remainheap = 0x%08x\n", s->reमुख्यheap);
पूर्ण

u32 saa7164_अ_लोurrentfirmwareversion(काष्ठा saa7164_dev *dev)
अणु
	u32 reg;

	reg = saa7164_पढ़ोl(SAA_DEVICE_VERSION);
	dprपूर्णांकk(1, "Device running firmware version %d.%d.%d.%d (0x%x)\n",
		(reg & 0x0000fc00) >> 10,
		(reg & 0x000003e0) >> 5,
		(reg & 0x0000001f),
		(reg & 0xffff0000) >> 16,
		reg);

	वापस reg;
पूर्ण

/* TODO: Debugging func, हटाओ */
व्योम saa7164_dumpregs(काष्ठा saa7164_dev *dev, u32 addr)
अणु
	पूर्णांक i;

	dprपूर्णांकk(1, "--------------------> 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");

	क्रम (i = 0; i < 0x100; i += 16)
		dprपूर्णांकk(1, "region0[0x%08x] = %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
			i,
			(u8)saa7164_पढ़ोb(addr + i + 0),
			(u8)saa7164_पढ़ोb(addr + i + 1),
			(u8)saa7164_पढ़ोb(addr + i + 2),
			(u8)saa7164_पढ़ोb(addr + i + 3),
			(u8)saa7164_पढ़ोb(addr + i + 4),
			(u8)saa7164_पढ़ोb(addr + i + 5),
			(u8)saa7164_पढ़ोb(addr + i + 6),
			(u8)saa7164_पढ़ोb(addr + i + 7),
			(u8)saa7164_पढ़ोb(addr + i + 8),
			(u8)saa7164_पढ़ोb(addr + i + 9),
			(u8)saa7164_पढ़ोb(addr + i + 10),
			(u8)saa7164_पढ़ोb(addr + i + 11),
			(u8)saa7164_पढ़ोb(addr + i + 12),
			(u8)saa7164_पढ़ोb(addr + i + 13),
			(u8)saa7164_पढ़ोb(addr + i + 14),
			(u8)saa7164_पढ़ोb(addr + i + 15)
			);
पूर्ण

अटल व्योम saa7164_dump_hwdesc(काष्ठा saa7164_dev *dev)
अणु
	dprपूर्णांकk(1, "@0x%p hwdesc sizeof(struct tmComResHWDescr) = %d bytes\n",
		&dev->hwdesc, (u32)माप(काष्ठा पंचांगComResHWDescr));

	dprपूर्णांकk(1, " .bLength = 0x%x\n", dev->hwdesc.bLength);
	dprपूर्णांकk(1, " .bDescriptorType = 0x%x\n", dev->hwdesc.bDescriptorType);
	dprपूर्णांकk(1, " .bDescriptorSubtype = 0x%x\n",
		dev->hwdesc.bDescriptorSubtype);

	dprपूर्णांकk(1, " .bcdSpecVersion = 0x%x\n", dev->hwdesc.bcdSpecVersion);
	dprपूर्णांकk(1, " .dwClockFrequency = 0x%x\n", dev->hwdesc.dwClockFrequency);
	dprपूर्णांकk(1, " .dwClockUpdateRes = 0x%x\n", dev->hwdesc.dwClockUpdateRes);
	dprपूर्णांकk(1, " .bCapabilities = 0x%x\n", dev->hwdesc.bCapabilities);
	dprपूर्णांकk(1, " .dwDeviceRegistersLocation = 0x%x\n",
		dev->hwdesc.dwDeviceRegistersLocation);

	dprपूर्णांकk(1, " .dwHostMemoryRegion = 0x%x\n",
		dev->hwdesc.dwHostMemoryRegion);

	dprपूर्णांकk(1, " .dwHostMemoryRegionSize = 0x%x\n",
		dev->hwdesc.dwHostMemoryRegionSize);

	dprपूर्णांकk(1, " .dwHostHibernatMemRegion = 0x%x\n",
		dev->hwdesc.dwHostHibernatMemRegion);

	dprपूर्णांकk(1, " .dwHostHibernatMemRegionSize = 0x%x\n",
		dev->hwdesc.dwHostHibernatMemRegionSize);
पूर्ण

अटल व्योम saa7164_dump_पूर्णांकfdesc(काष्ठा saa7164_dev *dev)
अणु
	dprपूर्णांकk(1, "@0x%p intfdesc sizeof(struct tmComResInterfaceDescr) = %d bytes\n",
		&dev->पूर्णांकfdesc, (u32)माप(काष्ठा पंचांगComResInterfaceDescr));

	dprपूर्णांकk(1, " .bLength = 0x%x\n", dev->पूर्णांकfdesc.bLength);
	dprपूर्णांकk(1, " .bDescriptorType = 0x%x\n", dev->पूर्णांकfdesc.bDescriptorType);
	dprपूर्णांकk(1, " .bDescriptorSubtype = 0x%x\n",
		dev->पूर्णांकfdesc.bDescriptorSubtype);

	dprपूर्णांकk(1, " .bFlags = 0x%x\n", dev->पूर्णांकfdesc.bFlags);
	dprपूर्णांकk(1, " .bInterfaceType = 0x%x\n", dev->पूर्णांकfdesc.bInterfaceType);
	dprपूर्णांकk(1, " .bInterfaceId = 0x%x\n", dev->पूर्णांकfdesc.bInterfaceId);
	dprपूर्णांकk(1, " .bBaseInterface = 0x%x\n", dev->पूर्णांकfdesc.bBaseInterface);
	dprपूर्णांकk(1, " .bInterruptId = 0x%x\n", dev->पूर्णांकfdesc.bInterruptId);
	dprपूर्णांकk(1, " .bDebugInterruptId = 0x%x\n",
		dev->पूर्णांकfdesc.bDebugInterruptId);

	dprपूर्णांकk(1, " .BARLocation = 0x%x\n", dev->पूर्णांकfdesc.BARLocation);
पूर्ण

अटल व्योम saa7164_dump_busdesc(काष्ठा saa7164_dev *dev)
अणु
	dprपूर्णांकk(1, "@0x%p busdesc sizeof(struct tmComResBusDescr) = %d bytes\n",
		&dev->busdesc, (u32)माप(काष्ठा पंचांगComResBusDescr));

	dprपूर्णांकk(1, " .CommandRing   = 0x%016Lx\n", dev->busdesc.CommandRing);
	dprपूर्णांकk(1, " .ResponseRing  = 0x%016Lx\n", dev->busdesc.ResponseRing);
	dprपूर्णांकk(1, " .CommandWrite  = 0x%x\n", dev->busdesc.CommandWrite);
	dprपूर्णांकk(1, " .CommandRead   = 0x%x\n", dev->busdesc.CommandRead);
	dprपूर्णांकk(1, " .ResponseWrite = 0x%x\n", dev->busdesc.ResponseWrite);
	dprपूर्णांकk(1, " .ResponseRead  = 0x%x\n", dev->busdesc.ResponseRead);
पूर्ण

/* Much of the hardware configuration and PCI रेजिस्टरs are configured
 * dynamically depending on firmware. We have to cache some initial
 * काष्ठाures then use these to locate other important काष्ठाures
 * from PCI space.
 */
अटल व्योम saa7164_get_descriptors(काष्ठा saa7164_dev *dev)
अणु
	स_नकल_fromio(&dev->hwdesc, dev->bmmio, माप(काष्ठा पंचांगComResHWDescr));
	स_नकल_fromio(&dev->पूर्णांकfdesc, dev->bmmio + माप(काष्ठा पंचांगComResHWDescr),
		माप(काष्ठा पंचांगComResInterfaceDescr));
	स_नकल_fromio(&dev->busdesc, dev->bmmio + dev->पूर्णांकfdesc.BARLocation,
		माप(काष्ठा पंचांगComResBusDescr));

	अगर (dev->hwdesc.bLength != माप(काष्ठा पंचांगComResHWDescr)) अणु
		prपूर्णांकk(KERN_ERR "Structure struct tmComResHWDescr is mangled\n");
		prपूर्णांकk(KERN_ERR "Need %x got %d\n", dev->hwdesc.bLength,
			(u32)माप(काष्ठा पंचांगComResHWDescr));
	पूर्ण अन्यथा
		saa7164_dump_hwdesc(dev);

	अगर (dev->पूर्णांकfdesc.bLength != माप(काष्ठा पंचांगComResInterfaceDescr)) अणु
		prपूर्णांकk(KERN_ERR "struct struct tmComResInterfaceDescr is mangled\n");
		prपूर्णांकk(KERN_ERR "Need %x got %d\n", dev->पूर्णांकfdesc.bLength,
			(u32)माप(काष्ठा पंचांगComResInterfaceDescr));
	पूर्ण अन्यथा
		saa7164_dump_पूर्णांकfdesc(dev);

	saa7164_dump_busdesc(dev);
पूर्ण

अटल पूर्णांक saa7164_pci_quirks(काष्ठा saa7164_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक get_resources(काष्ठा saa7164_dev *dev)
अणु
	अगर (request_mem_region(pci_resource_start(dev->pci, 0),
		pci_resource_len(dev->pci, 0), dev->name)) अणु

		अगर (request_mem_region(pci_resource_start(dev->pci, 2),
			pci_resource_len(dev->pci, 2), dev->name))
			वापस 0;
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: can't get MMIO memory @ 0x%llx or 0x%llx\n",
		dev->name,
		(u64)pci_resource_start(dev->pci, 0),
		(u64)pci_resource_start(dev->pci, 2));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक saa7164_port_init(काष्ठा saa7164_dev *dev, पूर्णांक portnr)
अणु
	काष्ठा saa7164_port *port = शून्य;

	BUG_ON((portnr < 0) || (portnr >= SAA7164_MAX_PORTS));

	port = &dev->ports[portnr];

	port->dev = dev;
	port->nr = portnr;

	अगर ((portnr == SAA7164_PORT_TS1) || (portnr == SAA7164_PORT_TS2))
		port->type = SAA7164_MPEG_DVB;
	अन्यथा
	अगर ((portnr == SAA7164_PORT_ENC1) || (portnr == SAA7164_PORT_ENC2)) अणु
		port->type = SAA7164_MPEG_ENCODER;

		/* We need a deferred पूर्णांकerrupt handler क्रम cmd handling */
		INIT_WORK(&port->workenc, saa7164_work_enchandler);
	पूर्ण अन्यथा अगर ((portnr == SAA7164_PORT_VBI1) || (portnr == SAA7164_PORT_VBI2)) अणु
		port->type = SAA7164_MPEG_VBI;

		/* We need a deferred पूर्णांकerrupt handler क्रम cmd handling */
		INIT_WORK(&port->workenc, saa7164_work_vbihandler);
	पूर्ण अन्यथा
		BUG();

	/* Init all the critical resources */
	mutex_init(&port->dvb.lock);
	INIT_LIST_HEAD(&port->dmaqueue.list);
	mutex_init(&port->dmaqueue_lock);

	INIT_LIST_HEAD(&port->list_buf_used.list);
	INIT_LIST_HEAD(&port->list_buf_मुक्त.list);
	init_रुकोqueue_head(&port->रुको_पढ़ो);


	saa7164_histogram_reset(&port->irq_पूर्णांकerval, "irq intervals");
	saa7164_histogram_reset(&port->svc_पूर्णांकerval, "deferred intervals");
	saa7164_histogram_reset(&port->irq_svc_पूर्णांकerval,
		"irq to deferred intervals");
	saa7164_histogram_reset(&port->पढ़ो_पूर्णांकerval,
		"encoder/vbi read() intervals");
	saa7164_histogram_reset(&port->poll_पूर्णांकerval,
		"encoder/vbi poll() intervals");

	वापस 0;
पूर्ण

अटल पूर्णांक saa7164_dev_setup(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक i;

	mutex_init(&dev->lock);
	atomic_inc(&dev->refcount);
	dev->nr = saa7164_devcount++;

	snम_लिखो(dev->name, माप(dev->name), "saa7164[%d]", dev->nr);

	mutex_lock(&devlist);
	list_add_tail(&dev->devlist, &saa7164_devlist);
	mutex_unlock(&devlist);

	/* board config */
	dev->board = UNSET;
	अगर (card[dev->nr] < saa7164_bcount)
		dev->board = card[dev->nr];

	क्रम (i = 0; UNSET == dev->board  &&  i < saa7164_idcount; i++)
		अगर (dev->pci->subप्रणाली_venकरोr == saa7164_subids[i].subvenकरोr &&
			dev->pci->subप्रणाली_device ==
				saa7164_subids[i].subdevice)
				dev->board = saa7164_subids[i].card;

	अगर (UNSET == dev->board) अणु
		dev->board = SAA7164_BOARD_UNKNOWN;
		saa7164_card_list(dev);
	पूर्ण

	dev->pci_bus  = dev->pci->bus->number;
	dev->pci_slot = PCI_SLOT(dev->pci->devfn);

	/* I2C Defaults / setup */
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].nr = 0;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].nr = 1;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].nr = 2;

	/* Transport + Encoder ports 1, 2, 3, 4 - Defaults / setup */
	saa7164_port_init(dev, SAA7164_PORT_TS1);
	saa7164_port_init(dev, SAA7164_PORT_TS2);
	saa7164_port_init(dev, SAA7164_PORT_ENC1);
	saa7164_port_init(dev, SAA7164_PORT_ENC2);
	saa7164_port_init(dev, SAA7164_PORT_VBI1);
	saa7164_port_init(dev, SAA7164_PORT_VBI2);

	अगर (get_resources(dev) < 0) अणु
		prपूर्णांकk(KERN_ERR "CORE %s No more PCIe resources for subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subप्रणाली_venकरोr,
		       dev->pci->subप्रणाली_device);

		saa7164_devcount--;
		वापस -ENODEV;
	पूर्ण

	/* PCI/e allocations */
	dev->lmmio = ioremap(pci_resource_start(dev->pci, 0),
			     pci_resource_len(dev->pci, 0));

	dev->lmmio2 = ioremap(pci_resource_start(dev->pci, 2),
			     pci_resource_len(dev->pci, 2));

	dev->bmmio = (u8 __iomem *)dev->lmmio;
	dev->bmmio2 = (u8 __iomem *)dev->lmmio2;

	/* Interrupt and ack रेजिस्टर locations offset of bmmio */
	dev->पूर्णांक_status = 0x183000 + 0xf80;
	dev->पूर्णांक_ack = 0x183000 + 0xf90;

	prपूर्णांकk(KERN_INFO
		"CORE %s: subsystem: %04x:%04x, board: %s [card=%d,%s]\n",
	       dev->name, dev->pci->subप्रणाली_venकरोr,
	       dev->pci->subप्रणाली_device, saa7164_boards[dev->board].name,
	       dev->board, card[dev->nr] == dev->board ?
	       "insmod option" : "autodetected");

	saa7164_pci_quirks(dev);

	वापस 0;
पूर्ण

अटल व्योम saa7164_dev_unरेजिस्टर(काष्ठा saa7164_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	release_mem_region(pci_resource_start(dev->pci, 0),
		pci_resource_len(dev->pci, 0));

	release_mem_region(pci_resource_start(dev->pci, 2),
		pci_resource_len(dev->pci, 2));

	अगर (!atomic_dec_and_test(&dev->refcount))
		वापस;

	iounmap(dev->lmmio);
	iounmap(dev->lmmio2);

	वापस;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम *saa7164_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा saa7164_dev *dev;
	loff_t index = *pos;

	mutex_lock(&devlist);
	list_क्रम_each_entry(dev, &saa7164_devlist, devlist) अणु
		अगर (index-- == 0) अणु
			mutex_unlock(&devlist);
			वापस dev;
		पूर्ण
	पूर्ण
	mutex_unlock(&devlist);

	वापस शून्य;
पूर्ण

अटल व्योम *saa7164_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा saa7164_dev *dev = v;
	व्योम *ret;

	mutex_lock(&devlist);
	अगर (list_is_last(&dev->devlist, &saa7164_devlist))
		ret = शून्य;
	अन्यथा
		ret = list_next_entry(dev, devlist);
	mutex_unlock(&devlist);

	++*pos;

	वापस ret;
पूर्ण

अटल व्योम saa7164_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक saa7164_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा saa7164_dev *dev = v;
	काष्ठा पंचांगComResBusInfo *b;
	पूर्णांक i, c;

	seq_म_लिखो(m, "%s = %p\n", dev->name, dev);

	/* Lock the bus from any other access */
	b = &dev->bus;
	mutex_lock(&b->lock);

	seq_म_लिखो(m, " .m_pdwSetWritePos = 0x%x (0x%08x)\n",
		   b->m_dwSetReadPos, saa7164_पढ़ोl(b->m_dwSetReadPos));

	seq_म_लिखो(m, " .m_pdwSetReadPos  = 0x%x (0x%08x)\n",
		   b->m_dwSetWritePos, saa7164_पढ़ोl(b->m_dwSetWritePos));

	seq_म_लिखो(m, " .m_pdwGetWritePos = 0x%x (0x%08x)\n",
		   b->m_dwGetReadPos, saa7164_पढ़ोl(b->m_dwGetReadPos));

	seq_म_लिखो(m, " .m_pdwGetReadPos  = 0x%x (0x%08x)\n",
		   b->m_dwGetWritePos, saa7164_पढ़ोl(b->m_dwGetWritePos));
	c = 0;
	seq_माला_दो(m, "\n  Set Ring:\n");
	seq_माला_दो(m, "\n addr  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");
	क्रम (i = 0; i < b->m_dwSizeSetRing; i++) अणु
		अगर (c == 0)
			seq_म_लिखो(m, " %04x:", i);

		seq_म_लिखो(m, " %02x", पढ़ोb(b->m_pdwSetRing + i));

		अगर (++c == 16) अणु
			seq_माला_दो(m, "\n");
			c = 0;
		पूर्ण
	पूर्ण

	c = 0;
	seq_माला_दो(m, "\n  Get Ring:\n");
	seq_माला_दो(m, "\n addr  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");
	क्रम (i = 0; i < b->m_dwSizeGetRing; i++) अणु
		अगर (c == 0)
			seq_म_लिखो(m, " %04x:", i);

		seq_म_लिखो(m, " %02x", पढ़ोb(b->m_pdwGetRing + i));

		अगर (++c == 16) अणु
			seq_माला_दो(m, "\n");
			c = 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&b->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations saa7164_sops = अणु
	.start = saa7164_seq_start,
	.next = saa7164_seq_next,
	.stop = saa7164_seq_stop,
	.show = saa7164_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(saa7164);

अटल काष्ठा dentry *saa7614_dentry;

अटल व्योम __init saa7164_debugfs_create(व्योम)
अणु
	saa7614_dentry = debugfs_create_file("saa7164", 0444, शून्य, शून्य,
					     &saa7164_fops);
पूर्ण

अटल व्योम __निकास saa7164_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ(saa7614_dentry);
पूर्ण
#अन्यथा
अटल व्योम saa7164_debugfs_create(व्योम) अणु पूर्ण
अटल व्योम saa7164_debugfs_हटाओ(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक saa7164_thपढ़ो_function(व्योम *data)
अणु
	काष्ठा saa7164_dev *dev = data;
	काष्ठा पंचांगFwInfoStruct fwinfo;
	u64 last_poll_समय = 0;

	dprपूर्णांकk(DBGLVL_THR, "thread started\n");

	set_मुक्तzable();

	जबतक (1) अणु
		msleep_पूर्णांकerruptible(100);
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		try_to_मुक्तze();

		dprपूर्णांकk(DBGLVL_THR, "thread running\n");

		/* Dump the firmware debug message to console */
		/* Polling this costs us 1-2% of the arm CPU */
		/* convert this पूर्णांकo a respnde to पूर्णांकerrupt 0x7a */
		saa7164_api_collect_debug(dev);

		/* Monitor CPU load every 1 second */
		अगर ((last_poll_समय + 1000 /* ms */) < jअगरfies_to_msecs(jअगरfies)) अणु
			saa7164_api_get_load_info(dev, &fwinfo);
			last_poll_समय = jअगरfies_to_msecs(jअगरfies);
		पूर्ण

	पूर्ण

	dprपूर्णांकk(DBGLVL_THR, "thread exiting\n");
	वापस 0;
पूर्ण

अटल bool saa7164_enable_msi(काष्ठा pci_dev *pci_dev, काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक err;

	अगर (!enable_msi) अणु
		prपूर्णांकk(KERN_WARNING "%s() MSI disabled by module parameter 'enable_msi'"
		       , __func__);
		वापस false;
	पूर्ण

	err = pci_enable_msi(pci_dev);

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s() Failed to enable MSI interrupt. Falling back to a shared IRQ\n",
		       __func__);
		वापस false;
	पूर्ण

	/* no error - so request an msi पूर्णांकerrupt */
	err = request_irq(pci_dev->irq, saa7164_irq, 0,
						dev->name, dev);

	अगर (err) अणु
		/* fall back to legacy पूर्णांकerrupt */
		prपूर्णांकk(KERN_ERR "%s() Failed to get an MSI interrupt. Falling back to a shared IRQ\n",
		       __func__);
		pci_disable_msi(pci_dev);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक saa7164_initdev(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा saa7164_dev *dev;
	पूर्णांक err, i;
	u32 version;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (शून्य == dev)
		वापस -ENOMEM;

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev, "v4l2_device_register failed\n");
		जाओ fail_मुक्त;
	पूर्ण

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ fail_मुक्त;
	पूर्ण

	अगर (saa7164_dev_setup(dev) < 0) अणु
		err = -EINVAL;
		जाओ fail_मुक्त;
	पूर्ण

	/* prपूर्णांक pci info */
	dev->pci_rev = pci_dev->revision;
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER,  &dev->pci_lat);
	prपूर्णांकk(KERN_INFO "%s/0: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
	       dev->name,
	       pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
	       dev->pci_lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));

	pci_set_master(pci_dev);
	/* TODO */
	err = dma_set_mask(&pci_dev->dev, 0xffffffff);
	अगर (err) अणु
		prपूर्णांकk("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		जाओ fail_irq;
	पूर्ण

	/* irq bit */
	अगर (saa7164_enable_msi(pci_dev, dev)) अणु
		dev->msi = true;
	पूर्ण अन्यथा अणु
		/* अगर we have an error (i.e. we करोn't have an पूर्णांकerrupt)
			 or msi is not enabled - fallback to shared पूर्णांकerrupt */

		err = request_irq(pci_dev->irq, saa7164_irq,
				IRQF_SHARED, dev->name, dev);

		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: can't get IRQ %d\n", dev->name,
			       pci_dev->irq);
			err = -EIO;
			जाओ fail_irq;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pci_dev, dev);

	/* Init the पूर्णांकernal command list */
	क्रम (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) अणु
		dev->cmds[i].seqno = i;
		dev->cmds[i].inuse = 0;
		mutex_init(&dev->cmds[i].lock);
		init_रुकोqueue_head(&dev->cmds[i].रुको);
	पूर्ण

	/* We need a deferred पूर्णांकerrupt handler क्रम cmd handling */
	INIT_WORK(&dev->workcmd, saa7164_work_cmdhandler);

	/* Only load the firmware अगर we know the board */
	अगर (dev->board != SAA7164_BOARD_UNKNOWN) अणु

		err = saa7164_करोwnloadfirmware(dev);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR
				"Failed to boot firmware, no features registered\n");
			जाओ fail_fw;
		पूर्ण

		saa7164_get_descriptors(dev);
		saa7164_dumpregs(dev, 0);
		saa7164_अ_लोurrentfirmwareversion(dev);
		saa7164_getfirmwarestatus(dev);
		err = saa7164_bus_setup(dev);
		अगर (err < 0)
			prपूर्णांकk(KERN_ERR
				"Failed to setup the bus, will continue\n");
		saa7164_bus_dump(dev);

		/* Ping the running firmware via the command bus and get the
		 * firmware version, this checks the bus is running OK.
		 */
		version = 0;
		अगर (saa7164_api_get_fw_version(dev, &version) == SAA_OK)
			dprपूर्णांकk(1, "Bus is operating correctly using version %d.%d.%d.%d (0x%x)\n",
				(version & 0x0000fc00) >> 10,
				(version & 0x000003e0) >> 5,
				(version & 0x0000001f),
				(version & 0xffff0000) >> 16,
				version);
		अन्यथा
			prपूर्णांकk(KERN_ERR
				"Failed to communicate with the firmware\n");

		/* Bring up the I2C buses */
		saa7164_i2c_रेजिस्टर(&dev->i2c_bus[0]);
		saa7164_i2c_रेजिस्टर(&dev->i2c_bus[1]);
		saa7164_i2c_रेजिस्टर(&dev->i2c_bus[2]);
		saa7164_gpio_setup(dev);
		saa7164_card_setup(dev);

		/* Parse the dynamic device configuration, find various
		 * media endpoपूर्णांकs (MPEG, WMV, PS, TS) and cache their
		 * configuration details पूर्णांकo the driver, so we can
		 * reference them later during simething_रेजिस्टर() func,
		 * पूर्णांकerrupt handlers, deferred work handlers etc.
		 */
		saa7164_api_क्रमागत_subdevs(dev);

		/* Begin to create the video sub-प्रणालीs and रेजिस्टर funcs */
		अगर (saa7164_boards[dev->board].porta == SAA7164_MPEG_DVB) अणु
			अगर (saa7164_dvb_रेजिस्टर(&dev->ports[SAA7164_PORT_TS1]) < 0) अणु
				prपूर्णांकk(KERN_ERR "%s() Failed to register dvb adapters on porta\n",
					__func__);
			पूर्ण
		पूर्ण

		अगर (saa7164_boards[dev->board].portb == SAA7164_MPEG_DVB) अणु
			अगर (saa7164_dvb_रेजिस्टर(&dev->ports[SAA7164_PORT_TS2]) < 0) अणु
				prपूर्णांकk(KERN_ERR"%s() Failed to register dvb adapters on portb\n",
					__func__);
			पूर्ण
		पूर्ण

		अगर (saa7164_boards[dev->board].portc == SAA7164_MPEG_ENCODER) अणु
			अगर (saa7164_encoder_रेजिस्टर(&dev->ports[SAA7164_PORT_ENC1]) < 0) अणु
				prपूर्णांकk(KERN_ERR"%s() Failed to register mpeg encoder\n",
				       __func__);
			पूर्ण
		पूर्ण

		अगर (saa7164_boards[dev->board].portd == SAA7164_MPEG_ENCODER) अणु
			अगर (saa7164_encoder_रेजिस्टर(&dev->ports[SAA7164_PORT_ENC2]) < 0) अणु
				prपूर्णांकk(KERN_ERR"%s() Failed to register mpeg encoder\n",
				       __func__);
			पूर्ण
		पूर्ण

		अगर (saa7164_boards[dev->board].porte == SAA7164_MPEG_VBI) अणु
			अगर (saa7164_vbi_रेजिस्टर(&dev->ports[SAA7164_PORT_VBI1]) < 0) अणु
				prपूर्णांकk(KERN_ERR"%s() Failed to register vbi device\n",
				       __func__);
			पूर्ण
		पूर्ण

		अगर (saa7164_boards[dev->board].portf == SAA7164_MPEG_VBI) अणु
			अगर (saa7164_vbi_रेजिस्टर(&dev->ports[SAA7164_PORT_VBI2]) < 0) अणु
				prपूर्णांकk(KERN_ERR"%s() Failed to register vbi device\n",
				       __func__);
			पूर्ण
		पूर्ण
		saa7164_api_set_debug(dev, fw_debug);

		अगर (fw_debug) अणु
			dev->kthपढ़ो = kthपढ़ो_run(saa7164_thपढ़ो_function, dev,
				"saa7164 debug");
			अगर (IS_ERR(dev->kthपढ़ो)) अणु
				dev->kthपढ़ो = शून्य;
				prपूर्णांकk(KERN_ERR "%s() Failed to create debug kernel thread\n",
				       __func__);
			पूर्ण
		पूर्ण

	पूर्ण /* != BOARD_UNKNOWN */
	अन्यथा
		prपूर्णांकk(KERN_ERR "%s() Unsupported board detected, registering without firmware\n",
		       __func__);

	dprपूर्णांकk(1, "%s() parameter debug = %d\n", __func__, saa_debug);
	dprपूर्णांकk(1, "%s() parameter waitsecs = %d\n", __func__, रुकोsecs);

fail_fw:
	वापस 0;

fail_irq:
	saa7164_dev_unरेजिस्टर(dev);
fail_मुक्त:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम saa7164_shutकरोwn(काष्ठा saa7164_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
पूर्ण

अटल व्योम saa7164_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा saa7164_dev *dev = pci_get_drvdata(pci_dev);

	अगर (dev->board != SAA7164_BOARD_UNKNOWN) अणु
		अगर (fw_debug && dev->kthपढ़ो) अणु
			kthपढ़ो_stop(dev->kthपढ़ो);
			dev->kthपढ़ो = शून्य;
		पूर्ण
		अगर (dev->firmwareloaded)
			saa7164_api_set_debug(dev, 0x00);
	पूर्ण

	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].irq_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].svc_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].irq_svc_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].पढ़ो_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].poll_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_VBI1],
		&dev->ports[SAA7164_PORT_VBI1].पढ़ो_पूर्णांकerval);
	saa7164_histogram_prपूर्णांक(&dev->ports[SAA7164_PORT_VBI2],
		&dev->ports[SAA7164_PORT_VBI2].poll_पूर्णांकerval);

	saa7164_shutकरोwn(dev);

	अगर (saa7164_boards[dev->board].porta == SAA7164_MPEG_DVB)
		saa7164_dvb_unरेजिस्टर(&dev->ports[SAA7164_PORT_TS1]);

	अगर (saa7164_boards[dev->board].portb == SAA7164_MPEG_DVB)
		saa7164_dvb_unरेजिस्टर(&dev->ports[SAA7164_PORT_TS2]);

	अगर (saa7164_boards[dev->board].portc == SAA7164_MPEG_ENCODER)
		saa7164_encoder_unरेजिस्टर(&dev->ports[SAA7164_PORT_ENC1]);

	अगर (saa7164_boards[dev->board].portd == SAA7164_MPEG_ENCODER)
		saa7164_encoder_unरेजिस्टर(&dev->ports[SAA7164_PORT_ENC2]);

	अगर (saa7164_boards[dev->board].porte == SAA7164_MPEG_VBI)
		saa7164_vbi_unरेजिस्टर(&dev->ports[SAA7164_PORT_VBI1]);

	अगर (saa7164_boards[dev->board].portf == SAA7164_MPEG_VBI)
		saa7164_vbi_unरेजिस्टर(&dev->ports[SAA7164_PORT_VBI2]);

	saa7164_i2c_unरेजिस्टर(&dev->i2c_bus[0]);
	saa7164_i2c_unरेजिस्टर(&dev->i2c_bus[1]);
	saa7164_i2c_unरेजिस्टर(&dev->i2c_bus[2]);

	/* unरेजिस्टर stuff */
	मुक्त_irq(pci_dev->irq, dev);

	अगर (dev->msi) अणु
		pci_disable_msi(pci_dev);
		dev->msi = false;
	पूर्ण

	pci_disable_device(pci_dev);

	mutex_lock(&devlist);
	list_del(&dev->devlist);
	mutex_unlock(&devlist);

	saa7164_dev_unरेजिस्टर(dev);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id saa7164_pci_tbl[] = अणु
	अणु
		/* SAA7164 */
		.venकरोr       = 0x1131,
		.device       = 0x7164,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	पूर्ण, अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, saa7164_pci_tbl);

अटल काष्ठा pci_driver saa7164_pci_driver = अणु
	.name     = "saa7164",
	.id_table = saa7164_pci_tbl,
	.probe    = saa7164_initdev,
	.हटाओ   = saa7164_finidev,
पूर्ण;

अटल पूर्णांक __init saa7164_init(व्योम)
अणु
	पूर्णांक ret = pci_रेजिस्टर_driver(&saa7164_pci_driver);

	अगर (ret)
		वापस ret;

	saa7164_debugfs_create();

	pr_info("saa7164 driver loaded\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास saa7164_fini(व्योम)
अणु
	saa7164_debugfs_हटाओ();
	pci_unरेजिस्टर_driver(&saa7164_pci_driver);
पूर्ण

module_init(saa7164_init);
module_निकास(saa7164_fini);
