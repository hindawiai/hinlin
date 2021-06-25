<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-core.c: Digital Devices bridge core functions
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/समयr.h>
#समावेश <linux/i2c.h>
#समावेश <linux/swab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ddbridge.h"
#समावेश "ddbridge-i2c.h"
#समावेश "ddbridge-regs.h"
#समावेश "ddbridge-max.h"
#समावेश "ddbridge-ci.h"
#समावेश "ddbridge-io.h"

#समावेश "tda18271c2dd.h"
#समावेश "stv6110x.h"
#समावेश "stv090x.h"
#समावेश "lnbh24.h"
#समावेश "drxk.h"
#समावेश "stv0367.h"
#समावेश "stv0367_priv.h"
#समावेश "cxd2841er.h"
#समावेश "tda18212.h"
#समावेश "stv0910.h"
#समावेश "stv6111.h"
#समावेश "lnbh25.h"
#समावेश "cxd2099.h"
#समावेश "ddbridge-dummy-fe.h"

/****************************************************************************/

#घोषणा DDB_MAX_ADAPTER 64

/****************************************************************************/

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक adapter_alloc;
module_param(adapter_alloc, पूर्णांक, 0444);
MODULE_PARM_DESC(adapter_alloc,
		 "0-one adapter per io, 1-one per tab with io, 2-one per tab, 3-one for all");

अटल पूर्णांक ci_bitrate = 70000;
module_param(ci_bitrate, पूर्णांक, 0444);
MODULE_PARM_DESC(ci_bitrate, " Bitrate in KHz for output to CI.");

अटल पूर्णांक ts_loop = -1;
module_param(ts_loop, पूर्णांक, 0444);
MODULE_PARM_DESC(ts_loop, "TS in/out test loop on port ts_loop");

अटल पूर्णांक xo2_speed = 2;
module_param(xo2_speed, पूर्णांक, 0444);
MODULE_PARM_DESC(xo2_speed, "default transfer speed for xo2 based duoflex, 0=55,1=75,2=90,3=104 MBit/s, default=2, use attribute to change for individual cards");

#अगर_घोषित __arm__
अटल पूर्णांक alt_dma = 1;
#अन्यथा
अटल पूर्णांक alt_dma;
#पूर्ण_अगर
module_param(alt_dma, पूर्णांक, 0444);
MODULE_PARM_DESC(alt_dma, "use alternative DMA buffer handling");

अटल पूर्णांक no_init;
module_param(no_init, पूर्णांक, 0444);
MODULE_PARM_DESC(no_init, "do not initialize most devices");

अटल पूर्णांक stv0910_single;
module_param(stv0910_single, पूर्णांक, 0444);
MODULE_PARM_DESC(stv0910_single, "use stv0910 cards as single demods");

अटल पूर्णांक dma_buf_num = 8;
module_param(dma_buf_num, पूर्णांक, 0444);
MODULE_PARM_DESC(dma_buf_num, "Number of DMA buffers, possible values: 8-32");

अटल पूर्णांक dma_buf_size = 21;
module_param(dma_buf_size, पूर्णांक, 0444);
MODULE_PARM_DESC(dma_buf_size,
		 "DMA buffer size as multiple of 128*47, possible values: 1-43");

अटल पूर्णांक dummy_tuner;
module_param(dummy_tuner, पूर्णांक, 0444);
MODULE_PARM_DESC(dummy_tuner,
		 "attach dummy tuner to port 0 on Octopus V3 or Octopus Mini cards");

/****************************************************************************/

अटल DEFINE_MUTEX(redirect_lock);

अटल काष्ठा workqueue_काष्ठा *ddb_wq;

अटल काष्ठा ddb *ddbs[DDB_MAX_ADAPTER];

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

काष्ठा ddb_irq *ddb_irq_set(काष्ठा ddb *dev, u32 link, u32 nr,
			    व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा ddb_irq *irq = &dev->link[link].irq[nr];

	irq->handler = handler;
	irq->data = data;
	वापस irq;
पूर्ण

अटल व्योम ddb_set_dma_table(काष्ठा ddb_io *io)
अणु
	काष्ठा ddb *dev = io->port->dev;
	काष्ठा ddb_dma *dma = io->dma;
	u32 i;
	u64 mem;

	अगर (!dma)
		वापस;
	क्रम (i = 0; i < dma->num; i++) अणु
		mem = dma->pbuf[i];
		ddbग_लिखोl(dev, mem & 0xffffffff, dma->bufregs + i * 8);
		ddbग_लिखोl(dev, mem >> 32, dma->bufregs + i * 8 + 4);
	पूर्ण
	dma->bufval = ((dma->भाग & 0x0f) << 16) |
		((dma->num & 0x1f) << 11) |
		((dma->size >> 7) & 0x7ff);
पूर्ण

अटल व्योम ddb_set_dma_tables(काष्ठा ddb *dev)
अणु
	u32 i;

	क्रम (i = 0; i < DDB_MAX_PORT; i++) अणु
		अगर (dev->port[i].input[0])
			ddb_set_dma_table(dev->port[i].input[0]);
		अगर (dev->port[i].input[1])
			ddb_set_dma_table(dev->port[i].input[1]);
		अगर (dev->port[i].output)
			ddb_set_dma_table(dev->port[i].output);
	पूर्ण
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल व्योम ddb_redirect_dma(काष्ठा ddb *dev,
			     काष्ठा ddb_dma *sdma,
			     काष्ठा ddb_dma *ddma)
अणु
	u32 i, base;
	u64 mem;

	sdma->bufval = ddma->bufval;
	base = sdma->bufregs;
	क्रम (i = 0; i < ddma->num; i++) अणु
		mem = ddma->pbuf[i];
		ddbग_लिखोl(dev, mem & 0xffffffff, base + i * 8);
		ddbग_लिखोl(dev, mem >> 32, base + i * 8 + 4);
	पूर्ण
पूर्ण

अटल पूर्णांक ddb_unredirect(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb_input *oredi, *iredi = शून्य;
	काष्ठा ddb_output *ireकरो = शून्य;

	/* dev_info(port->dev->dev,
	 * "unredirect %d.%d\n", port->dev->nr, port->nr);
	 */
	mutex_lock(&redirect_lock);
	अगर (port->output->dma->running) अणु
		mutex_unlock(&redirect_lock);
		वापस -EBUSY;
	पूर्ण
	oredi = port->output->redi;
	अगर (!oredi)
		जाओ करोne;
	अगर (port->input[0]) अणु
		iredi = port->input[0]->redi;
		ireकरो = port->input[0]->reकरो;

		अगर (ireकरो) अणु
			ireकरो->port->output->redi = oredi;
			अगर (ireकरो->port->input[0]) अणु
				ireकरो->port->input[0]->redi = iredi;
				ddb_redirect_dma(oredi->port->dev,
						 oredi->dma, ireकरो->dma);
			पूर्ण
			port->input[0]->reकरो = शून्य;
			ddb_set_dma_table(port->input[0]);
		पूर्ण
		oredi->redi = iredi;
		port->input[0]->redi = शून्य;
	पूर्ण
	oredi->reकरो = शून्य;
	port->output->redi = शून्य;

	ddb_set_dma_table(oredi);
करोne:
	mutex_unlock(&redirect_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ddb_redirect(u32 i, u32 p)
अणु
	काष्ठा ddb *idev = ddbs[(i >> 4) & 0x3f];
	काष्ठा ddb_input *input, *input2;
	काष्ठा ddb *pdev = ddbs[(p >> 4) & 0x3f];
	काष्ठा ddb_port *port;

	अगर (!idev || !pdev)
		वापस -EINVAL;
	अगर (!idev->has_dma || !pdev->has_dma)
		वापस -EINVAL;

	port = &pdev->port[p & 0x0f];
	अगर (!port->output)
		वापस -EINVAL;
	अगर (ddb_unredirect(port))
		वापस -EBUSY;

	अगर (i == 8)
		वापस 0;

	input = &idev->input[i & 7];
	अगर (!input)
		वापस -EINVAL;

	mutex_lock(&redirect_lock);
	अगर (port->output->dma->running || input->dma->running) अणु
		mutex_unlock(&redirect_lock);
		वापस -EBUSY;
	पूर्ण
	input2 = port->input[0];
	अगर (input2) अणु
		अगर (input->redi) अणु
			input2->redi = input->redi;
			input->redi = शून्य;
		पूर्ण अन्यथा अणु
			input2->redi = input;
		पूर्ण
	पूर्ण
	input->reकरो = port->output;
	port->output->redi = input;

	ddb_redirect_dma(input->port->dev, input->dma, port->output->dma);
	mutex_unlock(&redirect_lock);
	वापस 0;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल व्योम dma_मुक्त(काष्ठा pci_dev *pdev, काष्ठा ddb_dma *dma, पूर्णांक dir)
अणु
	पूर्णांक i;

	अगर (!dma)
		वापस;
	क्रम (i = 0; i < dma->num; i++) अणु
		अगर (dma->vbuf[i]) अणु
			अगर (alt_dma) अणु
				dma_unmap_single(&pdev->dev, dma->pbuf[i],
						 dma->size,
						 dir ? DMA_TO_DEVICE :
						 DMA_FROM_DEVICE);
				kमुक्त(dma->vbuf[i]);
				dma->vbuf[i] = शून्य;
			पूर्ण अन्यथा अणु
				dma_मुक्त_coherent(&pdev->dev, dma->size,
						  dma->vbuf[i], dma->pbuf[i]);
			पूर्ण

			dma->vbuf[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dma_alloc(काष्ठा pci_dev *pdev, काष्ठा ddb_dma *dma, पूर्णांक dir)
अणु
	पूर्णांक i;

	अगर (!dma)
		वापस 0;
	क्रम (i = 0; i < dma->num; i++) अणु
		अगर (alt_dma) अणु
			dma->vbuf[i] = kदो_स्मृति(dma->size, __GFP_RETRY_MAYFAIL);
			अगर (!dma->vbuf[i])
				वापस -ENOMEM;
			dma->pbuf[i] = dma_map_single(&pdev->dev,
						      dma->vbuf[i],
						      dma->size,
						      dir ? DMA_TO_DEVICE :
						      DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, dma->pbuf[i])) अणु
				kमुक्त(dma->vbuf[i]);
				dma->vbuf[i] = शून्य;
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अणु
			dma->vbuf[i] = dma_alloc_coherent(&pdev->dev,
							  dma->size,
							  &dma->pbuf[i],
							  GFP_KERNEL);
			अगर (!dma->vbuf[i])
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ddb_buffers_alloc(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_port *port;

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];
		चयन (port->class) अणु
		हाल DDB_PORT_TUNER:
			अगर (port->input[0]->dma)
				अगर (dma_alloc(dev->pdev, port->input[0]->dma, 0)
					< 0)
					वापस -1;
			अगर (port->input[1]->dma)
				अगर (dma_alloc(dev->pdev, port->input[1]->dma, 0)
					< 0)
					वापस -1;
			अवरोध;
		हाल DDB_PORT_CI:
		हाल DDB_PORT_LOOP:
			अगर (port->input[0]->dma)
				अगर (dma_alloc(dev->pdev, port->input[0]->dma, 0)
					< 0)
					वापस -1;
			अगर (port->output->dma)
				अगर (dma_alloc(dev->pdev, port->output->dma, 1)
					< 0)
					वापस -1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ddb_set_dma_tables(dev);
	वापस 0;
पूर्ण

व्योम ddb_buffers_मुक्त(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_port *port;

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];

		अगर (port->input[0] && port->input[0]->dma)
			dma_मुक्त(dev->pdev, port->input[0]->dma, 0);
		अगर (port->input[1] && port->input[1]->dma)
			dma_मुक्त(dev->pdev, port->input[1]->dma, 0);
		अगर (port->output && port->output->dma)
			dma_मुक्त(dev->pdev, port->output->dma, 1);
	पूर्ण
पूर्ण

अटल व्योम calc_con(काष्ठा ddb_output *output, u32 *con, u32 *con2, u32 flags)
अणु
	काष्ठा ddb *dev = output->port->dev;
	u32 bitrate = output->port->obr, max_bitrate = 72000;
	u32 gap = 4, nco = 0;

	*con = 0x1c;
	अगर (output->port->gap != 0xffffffff) अणु
		flags |= 1;
		gap = output->port->gap;
		max_bitrate = 0;
	पूर्ण
	अगर (dev->link[0].info->type == DDB_OCTOPUS_CI && output->port->nr > 1) अणु
		*con = 0x10c;
		अगर (dev->link[0].ids.regmapid >= 0x10003 && !(flags & 1)) अणु
			अगर (!(flags & 2)) अणु
				/* NCO */
				max_bitrate = 0;
				gap = 0;
				अगर (bitrate != 72000) अणु
					अगर (bitrate >= 96000) अणु
						*con |= 0x800;
					पूर्ण अन्यथा अणु
						*con |= 0x1000;
						nco = (bitrate * 8192 + 71999)
							/ 72000;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Divider and gap */
				*con |= 0x1810;
				अगर (bitrate <= 64000) अणु
					max_bitrate = 64000;
					nco = 8;
				पूर्ण अन्यथा अगर (bitrate <= 72000) अणु
					max_bitrate = 72000;
					nco = 7;
				पूर्ण अन्यथा अणु
					max_bitrate = 96000;
					nco = 5;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bitrate > 72000) अणु
				*con |= 0x810; /* 96 MBit/s and gap */
				max_bitrate = 96000;
			पूर्ण
			*con |= 0x10; /* enable gap */
		पूर्ण
	पूर्ण
	अगर (max_bitrate > 0) अणु
		अगर (bitrate > max_bitrate)
			bitrate = max_bitrate;
		अगर (bitrate < 31000)
			bitrate = 31000;
		gap = ((max_bitrate - bitrate) * 94) / bitrate;
		अगर (gap < 2)
			*con &= ~0x10; /* Disable gap */
		अन्यथा
			gap -= 2;
		अगर (gap > 127)
			gap = 127;
	पूर्ण

	*con2 = (nco << 16) | gap;
पूर्ण

अटल व्योम ddb_output_start(काष्ठा ddb_output *output)
अणु
	काष्ठा ddb *dev = output->port->dev;
	u32 con = 0x11c, con2 = 0;

	spin_lock_irq(&output->dma->lock);
	output->dma->cbuf = 0;
	output->dma->coff = 0;
	output->dma->stat = 0;
	ddbग_लिखोl(dev, 0, DMA_BUFFER_CONTROL(output->dma));

	अगर (output->port->input[0]->port->class == DDB_PORT_LOOP)
		con = (1UL << 13) | 0x14;
	अन्यथा
		calc_con(output, &con, &con2, 0);

	ddbग_लिखोl(dev, 0, TS_CONTROL(output));
	ddbग_लिखोl(dev, 2, TS_CONTROL(output));
	ddbग_लिखोl(dev, 0, TS_CONTROL(output));
	ddbग_लिखोl(dev, con, TS_CONTROL(output));
	ddbग_लिखोl(dev, con2, TS_CONTROL2(output));

	ddbग_लिखोl(dev, output->dma->bufval,
		  DMA_BUFFER_SIZE(output->dma));
	ddbग_लिखोl(dev, 0, DMA_BUFFER_ACK(output->dma));
	ddbग_लिखोl(dev, 1, DMA_BASE_READ);
	ddbग_लिखोl(dev, 7, DMA_BUFFER_CONTROL(output->dma));

	ddbग_लिखोl(dev, con | 1, TS_CONTROL(output));

	output->dma->running = 1;
	spin_unlock_irq(&output->dma->lock);
पूर्ण

अटल व्योम ddb_output_stop(काष्ठा ddb_output *output)
अणु
	काष्ठा ddb *dev = output->port->dev;

	spin_lock_irq(&output->dma->lock);

	ddbग_लिखोl(dev, 0, TS_CONTROL(output));

	ddbग_लिखोl(dev, 0, DMA_BUFFER_CONTROL(output->dma));
	output->dma->running = 0;
	spin_unlock_irq(&output->dma->lock);
पूर्ण

अटल व्योम ddb_input_stop(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb *dev = input->port->dev;
	u32 tag = DDB_LINK_TAG(input->port->lnr);

	spin_lock_irq(&input->dma->lock);

	ddbग_लिखोl(dev, 0, tag | TS_CONTROL(input));

	ddbग_लिखोl(dev, 0, DMA_BUFFER_CONTROL(input->dma));
	input->dma->running = 0;
	spin_unlock_irq(&input->dma->lock);
पूर्ण

अटल व्योम ddb_input_start(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb *dev = input->port->dev;

	spin_lock_irq(&input->dma->lock);
	input->dma->cbuf = 0;
	input->dma->coff = 0;
	input->dma->stat = 0;
	ddbग_लिखोl(dev, 0, DMA_BUFFER_CONTROL(input->dma));

	ddbग_लिखोl(dev, 0, TS_CONTROL(input));
	ddbग_लिखोl(dev, 2, TS_CONTROL(input));
	ddbग_लिखोl(dev, 0, TS_CONTROL(input));

	ddbग_लिखोl(dev, input->dma->bufval,
		  DMA_BUFFER_SIZE(input->dma));
	ddbग_लिखोl(dev, 0, DMA_BUFFER_ACK(input->dma));
	ddbग_लिखोl(dev, 1, DMA_BASE_WRITE);
	ddbग_लिखोl(dev, 3, DMA_BUFFER_CONTROL(input->dma));

	ddbग_लिखोl(dev, 0x09, TS_CONTROL(input));

	अगर (input->port->type == DDB_TUNER_DUMMY)
		ddbग_लिखोl(dev, 0x000fff01, TS_CONTROL2(input));

	input->dma->running = 1;
	spin_unlock_irq(&input->dma->lock);
पूर्ण

अटल व्योम ddb_input_start_all(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb_input *i = input;
	काष्ठा ddb_output *o;

	mutex_lock(&redirect_lock);
	जबतक (i && (o = i->reकरो)) अणु
		ddb_output_start(o);
		i = o->port->input[0];
		अगर (i)
			ddb_input_start(i);
	पूर्ण
	ddb_input_start(input);
	mutex_unlock(&redirect_lock);
पूर्ण

अटल व्योम ddb_input_stop_all(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb_input *i = input;
	काष्ठा ddb_output *o;

	mutex_lock(&redirect_lock);
	ddb_input_stop(input);
	जबतक (i && (o = i->reकरो)) अणु
		ddb_output_stop(o);
		i = o->port->input[0];
		अगर (i)
			ddb_input_stop(i);
	पूर्ण
	mutex_unlock(&redirect_lock);
पूर्ण

अटल u32 ddb_output_मुक्त(काष्ठा ddb_output *output)
अणु
	u32 idx, off, stat = output->dma->stat;
	s32 dअगरf;

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	अगर (output->dma->cbuf != idx) अणु
		अगर ((((output->dma->cbuf + 1) % output->dma->num) == idx) &&
		    (output->dma->size - output->dma->coff <= (2 * 188)))
			वापस 0;
		वापस 188;
	पूर्ण
	dअगरf = off - output->dma->coff;
	अगर (dअगरf <= 0 || dअगरf > (2 * 188))
		वापस 188;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ddb_output_ग_लिखो(काष्ठा ddb_output *output,
				स्थिर __user u8 *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = output->port->dev;
	u32 idx, off, stat = output->dma->stat;
	u32 left = count, len;

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	जबतक (left) अणु
		len = output->dma->size - output->dma->coff;
		अगर ((((output->dma->cbuf + 1) % output->dma->num) == idx) &&
		    off == 0) अणु
			अगर (len <= 188)
				अवरोध;
			len -= 188;
		पूर्ण
		अगर (output->dma->cbuf == idx) अणु
			अगर (off > output->dma->coff) अणु
				len = off - output->dma->coff;
				len -= (len % 188);
				अगर (len <= 188)
					अवरोध;
				len -= 188;
			पूर्ण
		पूर्ण
		अगर (len > left)
			len = left;
		अगर (copy_from_user(output->dma->vbuf[output->dma->cbuf] +
				   output->dma->coff,
				   buf, len))
			वापस -EIO;
		अगर (alt_dma)
			dma_sync_single_क्रम_device(
				dev->dev,
				output->dma->pbuf[output->dma->cbuf],
				output->dma->size, DMA_TO_DEVICE);
		left -= len;
		buf += len;
		output->dma->coff += len;
		अगर (output->dma->coff == output->dma->size) अणु
			output->dma->coff = 0;
			output->dma->cbuf = ((output->dma->cbuf + 1) %
					     output->dma->num);
		पूर्ण
		ddbग_लिखोl(dev,
			  (output->dma->cbuf << 11) |
			  (output->dma->coff >> 7),
			  DMA_BUFFER_ACK(output->dma));
	पूर्ण
	वापस count - left;
पूर्ण

अटल u32 ddb_input_avail(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb *dev = input->port->dev;
	u32 idx, off, stat = input->dma->stat;
	u32 ctrl = ddbपढ़ोl(dev, DMA_BUFFER_CONTROL(input->dma));

	idx = (stat >> 11) & 0x1f;
	off = (stat & 0x7ff) << 7;

	अगर (ctrl & 4) अणु
		dev_err(dev->dev, "IA %d %d %08x\n", idx, off, ctrl);
		ddbग_लिखोl(dev, stat, DMA_BUFFER_ACK(input->dma));
		वापस 0;
	पूर्ण
	अगर (input->dma->cbuf != idx)
		वापस 188;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ddb_input_पढ़ो(काष्ठा ddb_input *input,
			      __user u8 *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = input->port->dev;
	u32 left = count;
	u32 idx, मुक्त, stat = input->dma->stat;
	पूर्णांक ret;

	idx = (stat >> 11) & 0x1f;

	जबतक (left) अणु
		अगर (input->dma->cbuf == idx)
			वापस count - left;
		मुक्त = input->dma->size - input->dma->coff;
		अगर (मुक्त > left)
			मुक्त = left;
		अगर (alt_dma)
			dma_sync_single_क्रम_cpu(
				dev->dev,
				input->dma->pbuf[input->dma->cbuf],
				input->dma->size, DMA_FROM_DEVICE);
		ret = copy_to_user(buf, input->dma->vbuf[input->dma->cbuf] +
				   input->dma->coff, मुक्त);
		अगर (ret)
			वापस -EFAULT;
		input->dma->coff += मुक्त;
		अगर (input->dma->coff == input->dma->size) अणु
			input->dma->coff = 0;
			input->dma->cbuf = (input->dma->cbuf + 1) %
				input->dma->num;
		पूर्ण
		left -= मुक्त;
		buf += मुक्त;
		ddbग_लिखोl(dev,
			  (input->dma->cbuf << 11) | (input->dma->coff >> 7),
			  DMA_BUFFER_ACK(input->dma));
	पूर्ण
	वापस count;
पूर्ण

/****************************************************************************/
/****************************************************************************/

अटल sमाप_प्रकार ts_ग_लिखो(काष्ठा file *file, स्थिर __user अक्षर *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ddb_output *output = dvbdev->priv;
	काष्ठा ddb *dev = output->port->dev;
	माप_प्रकार left = count;
	पूर्णांक stat;

	अगर (!dev->has_dma)
		वापस -EINVAL;
	जबतक (left) अणु
		अगर (ddb_output_मुक्त(output) < 188) अणु
			अगर (file->f_flags & O_NONBLOCK)
				अवरोध;
			अगर (रुको_event_पूर्णांकerruptible(
				    output->dma->wq,
				    ddb_output_मुक्त(output) >= 188) < 0)
				अवरोध;
		पूर्ण
		stat = ddb_output_ग_लिखो(output, buf, left);
		अगर (stat < 0)
			वापस stat;
		buf += stat;
		left -= stat;
	पूर्ण
	वापस (left == count) ? -EAGAIN : (count - left);
पूर्ण

अटल sमाप_प्रकार ts_पढ़ो(काष्ठा file *file, __user अक्षर *buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ddb_output *output = dvbdev->priv;
	काष्ठा ddb_input *input = output->port->input[0];
	काष्ठा ddb *dev = output->port->dev;
	माप_प्रकार left = count;
	पूर्णांक stat;

	अगर (!dev->has_dma)
		वापस -EINVAL;
	जबतक (left) अणु
		अगर (ddb_input_avail(input) < 188) अणु
			अगर (file->f_flags & O_NONBLOCK)
				अवरोध;
			अगर (रुको_event_पूर्णांकerruptible(
				    input->dma->wq,
				    ddb_input_avail(input) >= 188) < 0)
				अवरोध;
		पूर्ण
		stat = ddb_input_पढ़ो(input, buf, left);
		अगर (stat < 0)
			वापस stat;
		left -= stat;
		buf += stat;
	पूर्ण
	वापस (count && (left == count)) ? -EAGAIN : (count - left);
पूर्ण

अटल __poll_t ts_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ddb_output *output = dvbdev->priv;
	काष्ठा ddb_input *input = output->port->input[0];

	__poll_t mask = 0;

	poll_रुको(file, &input->dma->wq, रुको);
	poll_रुको(file, &output->dma->wq, रुको);
	अगर (ddb_input_avail(input) >= 188)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (ddb_output_मुक्त(output) >= 188)
		mask |= EPOLLOUT | EPOLLWRNORM;
	वापस mask;
पूर्ण

अटल पूर्णांक ts_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ddb_output *output = शून्य;
	काष्ठा ddb_input *input = शून्य;

	अगर (dvbdev) अणु
		output = dvbdev->priv;
		input = output->port->input[0];
	पूर्ण

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY) अणु
		अगर (!input)
			वापस -EINVAL;
		ddb_input_stop(input);
	पूर्ण अन्यथा अगर ((file->f_flags & O_ACCMODE) == O_WRONLY) अणु
		अगर (!output)
			वापस -EINVAL;
		ddb_output_stop(output);
	पूर्ण
	वापस dvb_generic_release(inode, file);
पूर्ण

अटल पूर्णांक ts_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा ddb_output *output = शून्य;
	काष्ठा ddb_input *input = शून्य;

	अगर (dvbdev) अणु
		output = dvbdev->priv;
		input = output->port->input[0];
	पूर्ण

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY) अणु
		अगर (!input)
			वापस -EINVAL;
		अगर (input->reकरो || input->redi)
			वापस -EBUSY;
	पूर्ण अन्यथा अगर ((file->f_flags & O_ACCMODE) == O_WRONLY) अणु
		अगर (!output)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	err = dvb_generic_खोलो(inode, file);
	अगर (err < 0)
		वापस err;
	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY)
		ddb_input_start(input);
	अन्यथा अगर ((file->f_flags & O_ACCMODE) == O_WRONLY)
		ddb_output_start(output);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations ci_fops = अणु
	.owner   = THIS_MODULE,
	.पढ़ो    = ts_पढ़ो,
	.ग_लिखो   = ts_ग_लिखो,
	.खोलो    = ts_खोलो,
	.release = ts_release,
	.poll    = ts_poll,
	.mmap    = शून्य,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_ci = अणु
	.priv    = शून्य,
	.पढ़ोers = 1,
	.ग_लिखोrs = 1,
	.users   = 2,
	.fops    = &ci_fops,
पूर्ण;

/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक locked_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा ddb_input *input = fe->sec_priv;
	काष्ठा ddb_port *port = input->port;
	काष्ठा ddb_dvb *dvb = &port->dvb[input->nr & 1];
	पूर्णांक status;

	अगर (enable) अणु
		mutex_lock(&port->i2c_gate_lock);
		status = dvb->i2c_gate_ctrl(fe, 1);
	पूर्ण अन्यथा अणु
		status = dvb->i2c_gate_ctrl(fe, 0);
		mutex_unlock(&port->i2c_gate_lock);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक demod_attach_drxk(काष्ठा ddb_input *input)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा drxk_config config;

	स_रखो(&config, 0, माप(config));
	config.adr = 0x29 + (input->nr & 1);
	config.microcode_name = "drxk_a3.mc";

	dvb->fe = dvb_attach(drxk_attach, &config, i2c);
	अगर (!dvb->fe) अणु
		dev_err(dev, "No DRXK found!\n");
		वापस -ENODEV;
	पूर्ण
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_tda18271(काष्ठा ddb_input *input)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा dvb_frontend *fe;

	अगर (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 1);
	fe = dvb_attach(tda18271c2dd_attach, dvb->fe, i2c, 0x60);
	अगर (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 0);
	अगर (!fe) अणु
		dev_err(dev, "No TDA18271 found!\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

अटल काष्ठा stv0367_config ddb_stv0367_config[] = अणु
	अणु
		.demod_address = 0x1f,
		.xtal = 27000000,
		.अगर_khz = 0,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण, अणु
		.demod_address = 0x1e,
		.xtal = 27000000,
		.अगर_khz = 0,
		.अगर_iq_mode = FE_TER_NORMAL_IF_TUNER,
		.ts_mode = STV0367_SERIAL_PUNCT_CLOCK,
		.clk_pol = STV0367_CLOCKPOLARITY_DEFAULT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक demod_attach_stv0367(काष्ठा ddb_input *input)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;

	/* attach frontend */
	dvb->fe = dvb_attach(stv0367ddb_attach,
			     &ddb_stv0367_config[(input->nr & 1)], i2c);

	अगर (!dvb->fe) अणु
		dev_err(dev, "No stv0367 found!\n");
		वापस -ENODEV;
	पूर्ण
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_tda18212_ping(काष्ठा ddb_input *input, अचिन्हित लघु adr)
अणु
	काष्ठा i2c_adapter *adapter = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	u8 tda_id[2];
	u8 subaddr = 0x00;

	dev_dbg(dev, "stv0367-tda18212 tuner ping\n");
	अगर (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 1);

	अगर (i2c_पढ़ो_regs(adapter, adr, subaddr, tda_id, माप(tda_id)) < 0)
		dev_dbg(dev, "tda18212 ping 1 fail\n");
	अगर (i2c_पढ़ो_regs(adapter, adr, subaddr, tda_id, माप(tda_id)) < 0)
		dev_warn(dev, "tda18212 ping failed, expect problems\n");

	अगर (dvb->fe->ops.i2c_gate_ctrl)
		dvb->fe->ops.i2c_gate_ctrl(dvb->fe, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक demod_attach_cxd28xx(काष्ठा ddb_input *input, पूर्णांक par, पूर्णांक osc24)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा cxd2841er_config cfg;

	/* the cxd2841er driver expects 8bit/shअगरted I2C addresses */
	cfg.i2c_addr = ((input->nr & 1) ? 0x6d : 0x6c) << 1;

	cfg.xtal = osc24 ? SONY_XTAL_24000 : SONY_XTAL_20500;
	cfg.flags = CXD2841ER_AUTO_IFHZ | CXD2841ER_EARLY_TUNE |
		CXD2841ER_NO_WAIT_LOCK | CXD2841ER_NO_AGCNEG |
		CXD2841ER_TSBITS;

	अगर (!par)
		cfg.flags |= CXD2841ER_TS_SERIAL;

	/* attach frontend */
	dvb->fe = dvb_attach(cxd2841er_attach_t_c, &cfg, i2c);

	अगर (!dvb->fe) अणु
		dev_err(dev, "No cxd2837/38/43/54 found!\n");
		वापस -ENODEV;
	पूर्ण
	dvb->fe->sec_priv = input;
	dvb->i2c_gate_ctrl = dvb->fe->ops.i2c_gate_ctrl;
	dvb->fe->ops.i2c_gate_ctrl = locked_gate_ctrl;
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_tda18212(काष्ठा ddb_input *input, u32 porttype)
अणु
	काष्ठा i2c_adapter *adapter = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा i2c_client *client;
	काष्ठा tda18212_config config = अणु
		.fe = dvb->fe,
		.अगर_dvbt_6 = 3550,
		.अगर_dvbt_7 = 3700,
		.अगर_dvbt_8 = 4150,
		.अगर_dvbt2_6 = 3250,
		.अगर_dvbt2_7 = 4000,
		.अगर_dvbt2_8 = 4000,
		.अगर_dvbc = 5000,
	पूर्ण;
	u8 addr = (input->nr & 1) ? 0x63 : 0x60;

	/* due to a hardware quirk with the I2C gate on the stv0367+tda18212
	 * combo, the tda18212 must be probed by पढ़ोing it's id _twice_ when
	 * cold started, or it very likely will fail.
	 */
	अगर (porttype == DDB_TUNER_DVBCT_ST)
		tuner_tda18212_ping(input, addr);

	/* perक्रमm tuner probe/init/attach */
	client = dvb_module_probe("tda18212", शून्य, adapter, addr, &config);
	अगर (!client)
		जाओ err;

	dvb->i2c_client[0] = client;
	वापस 0;
err:
	dev_err(dev, "TDA18212 tuner not found. Device is not fully operational.\n");
	वापस -ENODEV;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल काष्ठा stv090x_config stv0900 = अणु
	.device         = STV0900,
	.demod_mode     = STV090x_DUAL,
	.clk_mode       = STV090x_CLK_EXT,

	.xtal           = 27000000,
	.address        = 0x69,

	.ts1_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,
	.ts2_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,

	.ts1_tei        = 1,
	.ts2_tei        = 1,

	.repeater_level = STV090x_RPTLEVEL_16,

	.adc1_range	= STV090x_ADC_1Vpp,
	.adc2_range	= STV090x_ADC_1Vpp,

	.diseqc_envelope_mode = true,
पूर्ण;

अटल काष्ठा stv090x_config stv0900_aa = अणु
	.device         = STV0900,
	.demod_mode     = STV090x_DUAL,
	.clk_mode       = STV090x_CLK_EXT,

	.xtal           = 27000000,
	.address        = 0x68,

	.ts1_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,
	.ts2_mode       = STV090x_TSMODE_SERIAL_PUNCTURED,

	.ts1_tei        = 1,
	.ts2_tei        = 1,

	.repeater_level = STV090x_RPTLEVEL_16,

	.adc1_range	= STV090x_ADC_1Vpp,
	.adc2_range	= STV090x_ADC_1Vpp,

	.diseqc_envelope_mode = true,
पूर्ण;

अटल काष्ठा stv6110x_config stv6110a = अणु
	.addr    = 0x60,
	.refclk	 = 27000000,
	.clk_भाग = 1,
पूर्ण;

अटल काष्ठा stv6110x_config stv6110b = अणु
	.addr    = 0x63,
	.refclk	 = 27000000,
	.clk_भाग = 1,
पूर्ण;

अटल पूर्णांक demod_attach_stv0900(काष्ठा ddb_input *input, पूर्णांक type)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा stv090x_config *feconf = type ? &stv0900_aa : &stv0900;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;

	dvb->fe = dvb_attach(stv090x_attach, feconf, i2c,
			     (input->nr & 1) ? STV090x_DEMODULATOR_1
			     : STV090x_DEMODULATOR_0);
	अगर (!dvb->fe) अणु
		dev_err(dev, "No STV0900 found!\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!dvb_attach(lnbh24_attach, dvb->fe, i2c, 0,
			0, (input->nr & 1) ?
			(0x09 - type) : (0x0b - type))) अणु
		dev_err(dev, "No LNBH24 found!\n");
		dvb_frontend_detach(dvb->fe);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_stv6110(काष्ठा ddb_input *input, पूर्णांक type)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा stv090x_config *feconf = type ? &stv0900_aa : &stv0900;
	काष्ठा stv6110x_config *tunerconf = (input->nr & 1) ?
		&stv6110b : &stv6110a;
	स्थिर काष्ठा stv6110x_devctl *ctl;

	ctl = dvb_attach(stv6110x_attach, dvb->fe, tunerconf, i2c);
	अगर (!ctl) अणु
		dev_err(dev, "No STV6110X found!\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(dev, "attach tuner input %d adr %02x\n",
		 input->nr, tunerconf->addr);

	feconf->tuner_init          = ctl->tuner_init;
	feconf->tuner_sleep         = ctl->tuner_sleep;
	feconf->tuner_set_mode      = ctl->tuner_set_mode;
	feconf->tuner_set_frequency = ctl->tuner_set_frequency;
	feconf->tuner_get_frequency = ctl->tuner_get_frequency;
	feconf->tuner_set_bandwidth = ctl->tuner_set_bandwidth;
	feconf->tuner_get_bandwidth = ctl->tuner_get_bandwidth;
	feconf->tuner_set_bbgain    = ctl->tuner_set_bbgain;
	feconf->tuner_get_bbgain    = ctl->tuner_get_bbgain;
	feconf->tuner_set_refclk    = ctl->tuner_set_refclk;
	feconf->tuner_get_status    = ctl->tuner_get_status;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा stv0910_cfg stv0910_p = अणु
	.adr      = 0x68,
	.parallel = 1,
	.rptlvl   = 4,
	.clk      = 30000000,
	.tsspeed  = 0x28,
पूर्ण;

अटल स्थिर काष्ठा lnbh25_config lnbh25_cfg = अणु
	.i2c_address = 0x0c << 1,
	.data2_config = LNBH25_TEN
पूर्ण;

अटल पूर्णांक has_lnbh25(काष्ठा i2c_adapter *i2c, u8 adr)
अणु
	u8 val;

	वापस i2c_पढ़ो_reg(i2c, adr, 0, &val) ? 0 : 1;
पूर्ण

अटल पूर्णांक demod_attach_stv0910(काष्ठा ddb_input *input, पूर्णांक type, पूर्णांक tsfast)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा stv0910_cfg cfg = stv0910_p;
	काष्ठा lnbh25_config lnbcfg = lnbh25_cfg;

	अगर (stv0910_single)
		cfg.single = 1;

	अगर (type)
		cfg.parallel = 2;

	अगर (tsfast) अणु
		dev_info(dev, "Enabling stv0910 higher speed TS\n");
		cfg.tsspeed = 0x10;
	पूर्ण

	dvb->fe = dvb_attach(stv0910_attach, i2c, &cfg, (input->nr & 1));
	अगर (!dvb->fe) अणु
		cfg.adr = 0x6c;
		dvb->fe = dvb_attach(stv0910_attach, i2c,
				     &cfg, (input->nr & 1));
	पूर्ण
	अगर (!dvb->fe) अणु
		dev_err(dev, "No STV0910 found!\n");
		वापस -ENODEV;
	पूर्ण

	/* attach lnbh25 - leftshअगरt by one as the lnbh25 driver expects 8bit
	 * i2c addresses
	 */
	अगर (has_lnbh25(i2c, 0x0d))
		lnbcfg.i2c_address = (((input->nr & 1) ? 0x0d : 0x0c) << 1);
	अन्यथा
		lnbcfg.i2c_address = (((input->nr & 1) ? 0x09 : 0x08) << 1);

	अगर (!dvb_attach(lnbh25_attach, dvb->fe, &lnbcfg, i2c)) अणु
		dev_err(dev, "No LNBH25 found!\n");
		dvb_frontend_detach(dvb->fe);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tuner_attach_stv6111(काष्ठा ddb_input *input, पूर्णांक type)
अणु
	काष्ठा i2c_adapter *i2c = &input->port->i2c->adap;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;
	काष्ठा dvb_frontend *fe;
	u8 adr = (type ? 0 : 4) + ((input->nr & 1) ? 0x63 : 0x60);

	fe = dvb_attach(stv6111_attach, dvb->fe, i2c, adr);
	अगर (!fe) अणु
		fe = dvb_attach(stv6111_attach, dvb->fe, i2c, adr & ~4);
		अगर (!fe) अणु
			dev_err(dev, "No STV6111 found at 0x%02x!\n", adr);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक demod_attach_dummy(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा device *dev = input->port->dev->dev;

	dvb->fe = dvb_attach(ddbridge_dummy_fe_qam_attach);
	अगर (!dvb->fe) अणु
		dev_err(dev, "QAM dummy attach failed!\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा ddb_input *input = dvbdmx->priv;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];

	अगर (!dvb->users)
		ddb_input_start_all(input);

	वापस ++dvb->users;
पूर्ण

अटल पूर्णांक stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा ddb_input *input = dvbdmx->priv;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];

	अगर (--dvb->users)
		वापस dvb->users;

	ddb_input_stop_all(input);
	वापस 0;
पूर्ण

अटल व्योम dvb_input_detach(काष्ठा ddb_input *input)
अणु
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा dvb_demux *dvbdemux = &dvb->demux;

	चयन (dvb->attached) अणु
	हाल 0x31:
		अगर (dvb->fe2)
			dvb_unरेजिस्टर_frontend(dvb->fe2);
		अगर (dvb->fe)
			dvb_unरेजिस्टर_frontend(dvb->fe);
		fallthrough;
	हाल 0x30:
		dvb_module_release(dvb->i2c_client[0]);
		dvb->i2c_client[0] = शून्य;

		अगर (dvb->fe2)
			dvb_frontend_detach(dvb->fe2);
		अगर (dvb->fe)
			dvb_frontend_detach(dvb->fe);
		dvb->fe = शून्य;
		dvb->fe2 = शून्य;
		fallthrough;
	हाल 0x20:
		dvb_net_release(&dvb->dvbnet);
		fallthrough;
	हाल 0x12:
		dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx,
					      &dvb->hw_frontend);
		dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx,
					      &dvb->mem_frontend);
		fallthrough;
	हाल 0x11:
		dvb_dmxdev_release(&dvb->dmxdev);
		fallthrough;
	हाल 0x10:
		dvb_dmx_release(&dvb->demux);
		fallthrough;
	हाल 0x01:
		अवरोध;
	पूर्ण
	dvb->attached = 0x00;
पूर्ण

अटल पूर्णांक dvb_रेजिस्टर_adapters(काष्ठा ddb *dev)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा ddb_port *port;
	काष्ठा dvb_adapter *adap;

	अगर (adapter_alloc == 3) अणु
		port = &dev->port[0];
		adap = port->dvb[0].adap;
		ret = dvb_रेजिस्टर_adapter(adap, "DDBridge", THIS_MODULE,
					   port->dev->dev,
					   adapter_nr);
		अगर (ret < 0)
			वापस ret;
		port->dvb[0].adap_रेजिस्टरed = 1;
		क्रम (i = 0; i < dev->port_num; i++) अणु
			port = &dev->port[i];
			port->dvb[0].adap = adap;
			port->dvb[1].adap = adap;
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];
		चयन (port->class) अणु
		हाल DDB_PORT_TUNER:
			adap = port->dvb[0].adap;
			ret = dvb_रेजिस्टर_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			अगर (ret < 0)
				वापस ret;
			port->dvb[0].adap_रेजिस्टरed = 1;

			अगर (adapter_alloc > 0) अणु
				port->dvb[1].adap = port->dvb[0].adap;
				अवरोध;
			पूर्ण
			adap = port->dvb[1].adap;
			ret = dvb_रेजिस्टर_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			अगर (ret < 0)
				वापस ret;
			port->dvb[1].adap_रेजिस्टरed = 1;
			अवरोध;

		हाल DDB_PORT_CI:
		हाल DDB_PORT_LOOP:
			adap = port->dvb[0].adap;
			ret = dvb_रेजिस्टर_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			अगर (ret < 0)
				वापस ret;
			port->dvb[0].adap_रेजिस्टरed = 1;
			अवरोध;
		शेष:
			अगर (adapter_alloc < 2)
				अवरोध;
			adap = port->dvb[0].adap;
			ret = dvb_रेजिस्टर_adapter(adap, "DDBridge",
						   THIS_MODULE,
						   port->dev->dev,
						   adapter_nr);
			अगर (ret < 0)
				वापस ret;
			port->dvb[0].adap_रेजिस्टरed = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dvb_unरेजिस्टर_adapters(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_port *port;
	काष्ठा ddb_dvb *dvb;

	क्रम (i = 0; i < dev->link[0].info->port_num; i++) अणु
		port = &dev->port[i];

		dvb = &port->dvb[0];
		अगर (dvb->adap_रेजिस्टरed)
			dvb_unरेजिस्टर_adapter(dvb->adap);
		dvb->adap_रेजिस्टरed = 0;

		dvb = &port->dvb[1];
		अगर (dvb->adap_रेजिस्टरed)
			dvb_unरेजिस्टर_adapter(dvb->adap);
		dvb->adap_रेजिस्टरed = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dvb_input_attach(काष्ठा ddb_input *input)
अणु
	पूर्णांक ret = 0;
	काष्ठा ddb_dvb *dvb = &input->port->dvb[input->nr & 1];
	काष्ठा ddb_port *port = input->port;
	काष्ठा dvb_adapter *adap = dvb->adap;
	काष्ठा dvb_demux *dvbdemux = &dvb->demux;
	काष्ठा ddb_ids *devids = &input->port->dev->link[input->port->lnr].ids;
	पूर्णांक par = 0, osc24 = 0, tsfast = 0;

	/*
	 * Determine अगर bridges with stv0910 demods can run with fast TS and
	 * thus support high bandwidth transponders.
	 * STV0910_PR and STV0910_P tuner types covers all relevant bridges,
	 * namely the CineS2 V7(A) and the Octopus CI S2 Pro/Advanced. All
	 * DuoFlex S2 V4(A) have type=DDB_TUNER_DVBS_STV0910 without any suffix
	 * and are limited by the serial link to the bridge, thus won't work
	 * in fast TS mode.
	 */
	अगर (port->nr == 0 &&
	    (port->type == DDB_TUNER_DVBS_STV0910_PR ||
	     port->type == DDB_TUNER_DVBS_STV0910_P)) अणु
		/* fast TS on port 0 requires FPGA version >= 1.7 */
		अगर ((devids->hwid & 0x00ffffff) >= 0x00010007)
			tsfast = 1;
	पूर्ण

	dvb->attached = 0x01;

	dvbdemux->priv = input;
	dvbdemux->dmx.capabilities = DMX_TS_FILTERING |
		DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING;
	dvbdemux->start_feed = start_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	ret = dvb_dmx_init(dvbdemux);
	अगर (ret < 0)
		वापस ret;
	dvb->attached = 0x10;

	dvb->dmxdev.filternum = 256;
	dvb->dmxdev.demux = &dvbdemux->dmx;
	ret = dvb_dmxdev_init(&dvb->dmxdev, adap);
	अगर (ret < 0)
		जाओ err_detach;
	dvb->attached = 0x11;

	dvb->mem_frontend.source = DMX_MEMORY_FE;
	dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->mem_frontend);
	dvb->hw_frontend.source = DMX_FRONTEND_0;
	dvb->demux.dmx.add_frontend(&dvb->demux.dmx, &dvb->hw_frontend);
	ret = dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, &dvb->hw_frontend);
	अगर (ret < 0)
		जाओ err_detach;
	dvb->attached = 0x12;

	ret = dvb_net_init(adap, &dvb->dvbnet, dvb->dmxdev.demux);
	अगर (ret < 0)
		जाओ err_detach;
	dvb->attached = 0x20;

	dvb->fe = शून्य;
	dvb->fe2 = शून्य;
	चयन (port->type) अणु
	हाल DDB_TUNER_MXL5XX:
		अगर (ddb_fe_attach_mxl5xx(input) < 0)
			जाओ err_detach;
		अवरोध;
	हाल DDB_TUNER_DVBS_ST:
		अगर (demod_attach_stv0900(input, 0) < 0)
			जाओ err_detach;
		अगर (tuner_attach_stv6110(input, 0) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBS_ST_AA:
		अगर (demod_attach_stv0900(input, 1) < 0)
			जाओ err_detach;
		अगर (tuner_attach_stv6110(input, 1) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBS_STV0910:
		अगर (demod_attach_stv0910(input, 0, tsfast) < 0)
			जाओ err_detach;
		अगर (tuner_attach_stv6111(input, 0) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBS_STV0910_PR:
		अगर (demod_attach_stv0910(input, 1, tsfast) < 0)
			जाओ err_detach;
		अगर (tuner_attach_stv6111(input, 1) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBS_STV0910_P:
		अगर (demod_attach_stv0910(input, 0, tsfast) < 0)
			जाओ err_detach;
		अगर (tuner_attach_stv6111(input, 1) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBCT_TR:
		अगर (demod_attach_drxk(input) < 0)
			जाओ err_detach;
		अगर (tuner_attach_tda18271(input) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBCT_ST:
		अगर (demod_attach_stv0367(input) < 0)
			जाओ err_detach;
		अगर (tuner_attach_tda18212(input, port->type) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBC2T2I_SONY_P:
		अगर (input->port->dev->link[input->port->lnr].info->ts_quirks &
		    TS_QUIRK_ALT_OSC)
			osc24 = 0;
		अन्यथा
			osc24 = 1;
		fallthrough;
	हाल DDB_TUNER_DVBCT2_SONY_P:
	हाल DDB_TUNER_DVBC2T2_SONY_P:
	हाल DDB_TUNER_ISDBT_SONY_P:
		अगर (input->port->dev->link[input->port->lnr].info->ts_quirks
			& TS_QUIRK_SERIAL)
			par = 0;
		अन्यथा
			par = 1;
		अगर (demod_attach_cxd28xx(input, par, osc24) < 0)
			जाओ err_detach;
		अगर (tuner_attach_tda18212(input, port->type) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DVBC2T2I_SONY:
		osc24 = 1;
		fallthrough;
	हाल DDB_TUNER_DVBCT2_SONY:
	हाल DDB_TUNER_DVBC2T2_SONY:
	हाल DDB_TUNER_ISDBT_SONY:
		अगर (demod_attach_cxd28xx(input, 0, osc24) < 0)
			जाओ err_detach;
		अगर (tuner_attach_tda18212(input, port->type) < 0)
			जाओ err_tuner;
		अवरोध;
	हाल DDB_TUNER_DUMMY:
		अगर (demod_attach_dummy(input) < 0)
			जाओ err_detach;
		अवरोध;
	हाल DDB_TUNER_MCI_SX8:
		अगर (ddb_fe_attach_mci(input, port->type) < 0)
			जाओ err_detach;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	dvb->attached = 0x30;

	अगर (dvb->fe) अणु
		अगर (dvb_रेजिस्टर_frontend(adap, dvb->fe) < 0)
			जाओ err_detach;

		अगर (dvb->fe2) अणु
			अगर (dvb_रेजिस्टर_frontend(adap, dvb->fe2) < 0) अणु
				dvb_unरेजिस्टर_frontend(dvb->fe);
				जाओ err_detach;
			पूर्ण
			dvb->fe2->tuner_priv = dvb->fe->tuner_priv;
			स_नकल(&dvb->fe2->ops.tuner_ops,
			       &dvb->fe->ops.tuner_ops,
			       माप(काष्ठा dvb_tuner_ops));
		पूर्ण
	पूर्ण

	dvb->attached = 0x31;
	वापस 0;

err_tuner:
	dev_err(port->dev->dev, "tuner attach failed!\n");

	अगर (dvb->fe2)
		dvb_frontend_detach(dvb->fe2);
	अगर (dvb->fe)
		dvb_frontend_detach(dvb->fe);
err_detach:
	dvb_input_detach(input);

	/* वापस error from ret अगर set */
	अगर (ret < 0)
		वापस ret;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक port_has_encti(काष्ठा ddb_port *port)
अणु
	काष्ठा device *dev = port->dev->dev;
	u8 val;
	पूर्णांक ret = i2c_पढ़ो_reg(&port->i2c->adap, 0x20, 0, &val);

	अगर (!ret)
		dev_info(dev, "[0x20]=0x%02x\n", val);
	वापस ret ? 0 : 1;
पूर्ण

अटल पूर्णांक port_has_cxd(काष्ठा ddb_port *port, u8 *type)
अणु
	u8 val;
	u8 probe[4] = अणु 0xe0, 0x00, 0x00, 0x00 पूर्ण, data[4];
	काष्ठा i2c_msg msgs[2] = अणुअणु .addr = 0x40,  .flags = 0,
				    .buf  = probe, .len   = 4 पूर्ण,
				  अणु .addr = 0x40,  .flags = I2C_M_RD,
				    .buf  = data,  .len   = 4 पूर्ण पूर्ण;
	val = i2c_transfer(&port->i2c->adap, msgs, 2);
	अगर (val != 2)
		वापस 0;

	अगर (data[0] == 0x02 && data[1] == 0x2b && data[3] == 0x43)
		*type = 2;
	अन्यथा
		*type = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_xo2(काष्ठा ddb_port *port, u8 *type, u8 *id)
अणु
	u8 probe[1] = अणु 0x00 पूर्ण, data[4];

	अगर (i2c_io(&port->i2c->adap, 0x10, probe, 1, data, 4))
		वापस 0;
	अगर (data[0] == 'D' && data[1] == 'F') अणु
		*id = data[2];
		*type = 1;
		वापस 1;
	पूर्ण
	अगर (data[0] == 'C' && data[1] == 'I') अणु
		*id = data[2];
		*type = 2;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक port_has_stv0900(काष्ठा ddb_port *port)
अणु
	u8 val;

	अगर (i2c_पढ़ो_reg16(&port->i2c->adap, 0x69, 0xf100, &val) < 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_stv0900_aa(काष्ठा ddb_port *port, u8 *id)
अणु
	अगर (i2c_पढ़ो_reg16(&port->i2c->adap, 0x68, 0xf100, id) < 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_drxks(काष्ठा ddb_port *port)
अणु
	u8 val;

	अगर (i2c_पढ़ो(&port->i2c->adap, 0x29, &val) < 0)
		वापस 0;
	अगर (i2c_पढ़ो(&port->i2c->adap, 0x2a, &val) < 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक port_has_stv0367(काष्ठा ddb_port *port)
अणु
	u8 val;

	अगर (i2c_पढ़ो_reg16(&port->i2c->adap, 0x1e, 0xf000, &val) < 0)
		वापस 0;
	अगर (val != 0x60)
		वापस 0;
	अगर (i2c_पढ़ो_reg16(&port->i2c->adap, 0x1f, 0xf000, &val) < 0)
		वापस 0;
	अगर (val != 0x60)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक init_xo2(काष्ठा ddb_port *port)
अणु
	काष्ठा i2c_adapter *i2c = &port->i2c->adap;
	काष्ठा ddb *dev = port->dev;
	u8 val, data[2];
	पूर्णांक res;

	res = i2c_पढ़ो_regs(i2c, 0x10, 0x04, data, 2);
	अगर (res < 0)
		वापस res;

	अगर (data[0] != 0x01)  अणु
		dev_info(dev->dev, "Port %d: invalid XO2\n", port->nr);
		वापस -1;
	पूर्ण

	i2c_पढ़ो_reg(i2c, 0x10, 0x08, &val);
	अगर (val != 0) अणु
		i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x00);
		msleep(100);
	पूर्ण
	/* Enable tuner घातer, disable pll, reset demods */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x04);
	usleep_range(2000, 3000);
	/* Release demod resets */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x07);

	/* speed: 0=55,1=75,2=90,3=104 MBit/s */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x09, xo2_speed);

	अगर (dev->link[port->lnr].info->con_घड़ी) अणु
		dev_info(dev->dev, "Setting continuous clock for XO2\n");
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0a, 0x03);
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0b, 0x03);
	पूर्ण अन्यथा अणु
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0a, 0x01);
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0b, 0x01);
	पूर्ण

	usleep_range(2000, 3000);
	/* Start XO2 PLL */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x87);

	वापस 0;
पूर्ण

अटल पूर्णांक init_xo2_ci(काष्ठा ddb_port *port)
अणु
	काष्ठा i2c_adapter *i2c = &port->i2c->adap;
	काष्ठा ddb *dev = port->dev;
	u8 val, data[2];
	पूर्णांक res;

	res = i2c_पढ़ो_regs(i2c, 0x10, 0x04, data, 2);
	अगर (res < 0)
		वापस res;

	अगर (data[0] > 1)  अणु
		dev_info(dev->dev, "Port %d: invalid XO2 CI %02x\n",
			 port->nr, data[0]);
		वापस -1;
	पूर्ण
	dev_info(dev->dev, "Port %d: DuoFlex CI %u.%u\n",
		 port->nr, data[0], data[1]);

	i2c_पढ़ो_reg(i2c, 0x10, 0x08, &val);
	अगर (val != 0) अणु
		i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x00);
		msleep(100);
	पूर्ण
	/* Enable both CI */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 3);
	usleep_range(2000, 3000);

	/* speed: 0=55,1=75,2=90,3=104 MBit/s */
	i2c_ग_लिखो_reg(i2c, 0x10, 0x09, 1);

	i2c_ग_लिखो_reg(i2c, 0x10, 0x08, 0x83);
	usleep_range(2000, 3000);

	अगर (dev->link[port->lnr].info->con_घड़ी) अणु
		dev_info(dev->dev, "Setting continuous clock for DuoFlex CI\n");
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0a, 0x03);
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0b, 0x03);
	पूर्ण अन्यथा अणु
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0a, 0x01);
		i2c_ग_लिखो_reg(i2c, 0x10, 0x0b, 0x01);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक port_has_cxd28xx(काष्ठा ddb_port *port, u8 *id)
अणु
	काष्ठा i2c_adapter *i2c = &port->i2c->adap;
	पूर्णांक status;

	status = i2c_ग_लिखो_reg(&port->i2c->adap, 0x6e, 0, 0);
	अगर (status)
		वापस 0;
	status = i2c_पढ़ो_reg(i2c, 0x6e, 0xfd, id);
	अगर (status)
		वापस 0;
	वापस 1;
पूर्ण

अटल अक्षर *xo2names[] = अणु
	"DUAL DVB-S2", "DUAL DVB-C/T/T2",
	"DUAL DVB-ISDBT", "DUAL DVB-C/C2/T/T2",
	"DUAL ATSC", "DUAL DVB-C/C2/T/T2,ISDB-T",
	"", ""
पूर्ण;

अटल अक्षर *xo2types[] = अणु
	"DVBS_ST", "DVBCT2_SONY",
	"ISDBT_SONY", "DVBC2T2_SONY",
	"ATSC_ST", "DVBC2T2I_SONY"
पूर्ण;

अटल व्योम ddb_port_probe(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb *dev = port->dev;
	u32 l = port->lnr;
	काष्ठा ddb_link *link = &dev->link[l];
	u8 id, type;

	port->name = "NO MODULE";
	port->type_name = "NONE";
	port->class = DDB_PORT_NONE;

	/* Handle missing ports and ports without I2C */

	अगर (dummy_tuner && !port->nr &&
	    link->ids.device == 0x0005) अणु
		port->name = "DUMMY";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DUMMY;
		port->type_name = "DUMMY";
		वापस;
	पूर्ण

	अगर (port->nr == ts_loop) अणु
		port->name = "TS LOOP";
		port->class = DDB_PORT_LOOP;
		वापस;
	पूर्ण

	अगर (port->nr == 1 && link->info->type == DDB_OCTOPUS_CI &&
	    link->info->i2c_mask == 1) अणु
		port->name = "NO TAB";
		port->class = DDB_PORT_NONE;
		वापस;
	पूर्ण

	अगर (link->info->type == DDB_OCTOPUS_MAX) अणु
		port->name = "DUAL DVB-S2 MAX";
		port->type_name = "MXL5XX";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_MXL5XX;
		अगर (port->i2c)
			ddbग_लिखोl(dev, I2C_SPEED_400,
				  port->i2c->regs + I2C_TIMING);
		वापस;
	पूर्ण

	अगर (link->info->type == DDB_OCTOPUS_MCI) अणु
		अगर (port->nr >= link->info->mci_ports)
			वापस;
		port->name = "DUAL MCI";
		port->type_name = "MCI";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_MCI + link->info->mci_type;
		वापस;
	पूर्ण

	अगर (port->nr > 1 && link->info->type == DDB_OCTOPUS_CI) अणु
		port->name = "CI internal";
		port->type_name = "INTERNAL";
		port->class = DDB_PORT_CI;
		port->type = DDB_CI_INTERNAL;
	पूर्ण

	अगर (!port->i2c)
		वापस;

	/* Probe ports with I2C */

	अगर (port_has_cxd(port, &id)) अणु
		अगर (id == 1) अणु
			port->name = "CI";
			port->type_name = "CXD2099";
			port->class = DDB_PORT_CI;
			port->type = DDB_CI_EXTERNAL_SONY;
			ddbग_लिखोl(dev, I2C_SPEED_400,
				  port->i2c->regs + I2C_TIMING);
		पूर्ण अन्यथा अणु
			dev_info(dev->dev, "Port %d: Uninitialized DuoFlex\n",
				 port->nr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (port_has_xo2(port, &type, &id)) अणु
		ddbग_लिखोl(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
		/*dev_info(dev->dev, "XO2 ID %02x\n", id);*/
		अगर (type == 2) अणु
			port->name = "DuoFlex CI";
			port->class = DDB_PORT_CI;
			port->type = DDB_CI_EXTERNAL_XO2;
			port->type_name = "CI_XO2";
			init_xo2_ci(port);
			वापस;
		पूर्ण
		id >>= 2;
		अगर (id > 5) अणु
			port->name = "unknown XO2 DuoFlex";
			port->type_name = "UNKNOWN";
		पूर्ण अन्यथा अणु
			port->name = xo2names[id];
			port->class = DDB_PORT_TUNER;
			port->type = DDB_TUNER_XO2 + id;
			port->type_name = xo2types[id];
			init_xo2(port);
		पूर्ण
	पूर्ण अन्यथा अगर (port_has_cxd28xx(port, &id)) अणु
		चयन (id) अणु
		हाल 0xa4:
			port->name = "DUAL DVB-C2T2 CXD2843";
			port->type = DDB_TUNER_DVBC2T2_SONY_P;
			port->type_name = "DVBC2T2_SONY";
			अवरोध;
		हाल 0xb1:
			port->name = "DUAL DVB-CT2 CXD2837";
			port->type = DDB_TUNER_DVBCT2_SONY_P;
			port->type_name = "DVBCT2_SONY";
			अवरोध;
		हाल 0xb0:
			port->name = "DUAL ISDB-T CXD2838";
			port->type = DDB_TUNER_ISDBT_SONY_P;
			port->type_name = "ISDBT_SONY";
			अवरोध;
		हाल 0xc1:
			port->name = "DUAL DVB-C2T2 ISDB-T CXD2854";
			port->type = DDB_TUNER_DVBC2T2I_SONY_P;
			port->type_name = "DVBC2T2I_ISDBT_SONY";
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		port->class = DDB_PORT_TUNER;
		ddbग_लिखोl(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
	पूर्ण अन्यथा अगर (port_has_stv0900(port)) अणु
		port->name = "DUAL DVB-S2";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBS_ST;
		port->type_name = "DVBS_ST";
		ddbग_लिखोl(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	पूर्ण अन्यथा अगर (port_has_stv0900_aa(port, &id)) अणु
		port->name = "DUAL DVB-S2";
		port->class = DDB_PORT_TUNER;
		अगर (id == 0x51) अणु
			अगर (port->nr == 0 &&
			    link->info->ts_quirks & TS_QUIRK_REVERSED)
				port->type = DDB_TUNER_DVBS_STV0910_PR;
			अन्यथा
				port->type = DDB_TUNER_DVBS_STV0910_P;
			port->type_name = "DVBS_ST_0910";
		पूर्ण अन्यथा अणु
			port->type = DDB_TUNER_DVBS_ST_AA;
			port->type_name = "DVBS_ST_AA";
		पूर्ण
		ddbग_लिखोl(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	पूर्ण अन्यथा अगर (port_has_drxks(port)) अणु
		port->name = "DUAL DVB-C/T";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBCT_TR;
		port->type_name = "DVBCT_TR";
		ddbग_लिखोl(dev, I2C_SPEED_400, port->i2c->regs + I2C_TIMING);
	पूर्ण अन्यथा अगर (port_has_stv0367(port)) अणु
		port->name = "DUAL DVB-C/T";
		port->class = DDB_PORT_TUNER;
		port->type = DDB_TUNER_DVBCT_ST;
		port->type_name = "DVBCT_ST";
		ddbग_लिखोl(dev, I2C_SPEED_100, port->i2c->regs + I2C_TIMING);
	पूर्ण अन्यथा अगर (port_has_encti(port)) अणु
		port->name = "ENCTI";
		port->class = DDB_PORT_LOOP;
	पूर्ण
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक ddb_port_attach(काष्ठा ddb_port *port)
अणु
	पूर्णांक ret = 0;

	चयन (port->class) अणु
	हाल DDB_PORT_TUNER:
		ret = dvb_input_attach(port->input[0]);
		अगर (ret < 0)
			अवरोध;
		ret = dvb_input_attach(port->input[1]);
		अगर (ret < 0) अणु
			dvb_input_detach(port->input[0]);
			अवरोध;
		पूर्ण
		port->input[0]->redi = port->input[0];
		port->input[1]->redi = port->input[1];
		अवरोध;
	हाल DDB_PORT_CI:
		ret = ddb_ci_attach(port, ci_bitrate);
		अगर (ret < 0)
			अवरोध;
		fallthrough;
	हाल DDB_PORT_LOOP:
		ret = dvb_रेजिस्टर_device(port->dvb[0].adap,
					  &port->dvb[0].dev,
					  &dvbdev_ci, (व्योम *)port->output,
					  DVB_DEVICE_SEC, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (ret < 0)
		dev_err(port->dev->dev, "port_attach on port %d failed\n",
			port->nr);
	वापस ret;
पूर्ण

पूर्णांक ddb_ports_attach(काष्ठा ddb *dev)
अणु
	पूर्णांक i, numports, err_ports = 0, ret = 0;
	काष्ठा ddb_port *port;

	अगर (dev->port_num) अणु
		ret = dvb_रेजिस्टर_adapters(dev);
		अगर (ret < 0) अणु
			dev_err(dev->dev, "Registering adapters failed. Check DVB_MAX_ADAPTERS in config.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	numports = dev->port_num;

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];
		अगर (port->class != DDB_PORT_NONE) अणु
			ret = ddb_port_attach(port);
			अगर (ret)
				err_ports++;
		पूर्ण अन्यथा अणु
			numports--;
		पूर्ण
	पूर्ण

	अगर (err_ports) अणु
		अगर (err_ports == numports) अणु
			dev_err(dev->dev, "All connected ports failed to initialise!\n");
			वापस -ENODEV;
		पूर्ण

		dev_warn(dev->dev, "%d of %d connected ports failed to initialise!\n",
			 err_ports, numports);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ddb_ports_detach(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_port *port;

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];

		चयन (port->class) अणु
		हाल DDB_PORT_TUNER:
			dvb_input_detach(port->input[1]);
			dvb_input_detach(port->input[0]);
			अवरोध;
		हाल DDB_PORT_CI:
		हाल DDB_PORT_LOOP:
			ddb_ci_detach(port);
			अवरोध;
		पूर्ण
	पूर्ण
	dvb_unरेजिस्टर_adapters(dev);
पूर्ण

/* Copy input DMA poपूर्णांकers to output DMA and ACK. */

अटल व्योम input_ग_लिखो_output(काष्ठा ddb_input *input,
			       काष्ठा ddb_output *output)
अणु
	ddbग_लिखोl(output->port->dev,
		  input->dma->stat, DMA_BUFFER_ACK(output->dma));
	output->dma->cbuf = (input->dma->stat >> 11) & 0x1f;
	output->dma->coff = (input->dma->stat & 0x7ff) << 7;
पूर्ण

अटल व्योम output_ack_input(काष्ठा ddb_output *output,
			     काष्ठा ddb_input *input)
अणु
	ddbग_लिखोl(input->port->dev,
		  output->dma->stat, DMA_BUFFER_ACK(input->dma));
पूर्ण

अटल व्योम input_ग_लिखो_dvb(काष्ठा ddb_input *input,
			    काष्ठा ddb_input *input2)
अणु
	काष्ठा ddb_dvb *dvb = &input2->port->dvb[input2->nr & 1];
	काष्ठा ddb_dma *dma, *dma2;
	काष्ठा ddb *dev = input->port->dev;
	पूर्णांक ack = 1;

	dma = input->dma;
	dma2 = input->dma;
	/*
	 * अगर there also is an output connected, करो not ACK.
	 * input_ग_लिखो_output will ACK.
	 */
	अगर (input->reकरो) अणु
		dma2 = input->reकरो->dma;
		ack = 0;
	पूर्ण
	जबतक (dma->cbuf != ((dma->stat >> 11) & 0x1f) ||
	       (4 & dma->ctrl)) अणु
		अगर (4 & dma->ctrl) अणु
			/* dev_err(dev->dev, "Overflow dma %d\n", dma->nr); */
			ack = 1;
		पूर्ण
		अगर (alt_dma)
			dma_sync_single_क्रम_cpu(dev->dev, dma2->pbuf[dma->cbuf],
						dma2->size, DMA_FROM_DEVICE);
		dvb_dmx_swfilter_packets(&dvb->demux,
					 dma2->vbuf[dma->cbuf],
					 dma2->size / 188);
		dma->cbuf = (dma->cbuf + 1) % dma2->num;
		अगर (ack)
			ddbग_लिखोl(dev, (dma->cbuf << 11),
				  DMA_BUFFER_ACK(dma));
		dma->stat = safe_ddbपढ़ोl(dev, DMA_BUFFER_CURRENT(dma));
		dma->ctrl = safe_ddbपढ़ोl(dev, DMA_BUFFER_CONTROL(dma));
	पूर्ण
पूर्ण

अटल व्योम input_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ddb_dma *dma = container_of(work, काष्ठा ddb_dma, work);
	काष्ठा ddb_input *input = (काष्ठा ddb_input *)dma->io;
	काष्ठा ddb *dev = input->port->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dma->lock, flags);
	अगर (!dma->running) अणु
		spin_unlock_irqrestore(&dma->lock, flags);
		वापस;
	पूर्ण
	dma->stat = ddbपढ़ोl(dev, DMA_BUFFER_CURRENT(dma));
	dma->ctrl = ddbपढ़ोl(dev, DMA_BUFFER_CONTROL(dma));

	अगर (input->redi)
		input_ग_लिखो_dvb(input, input->redi);
	अगर (input->reकरो)
		input_ग_लिखो_output(input, input->reकरो);
	wake_up(&dma->wq);
	spin_unlock_irqrestore(&dma->lock, flags);
पूर्ण

अटल व्योम input_handler(व्योम *data)
अणु
	काष्ठा ddb_input *input = (काष्ठा ddb_input *)data;
	काष्ठा ddb_dma *dma = input->dma;

	queue_work(ddb_wq, &dma->work);
पूर्ण

अटल व्योम output_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ddb_dma *dma = container_of(work, काष्ठा ddb_dma, work);
	काष्ठा ddb_output *output = (काष्ठा ddb_output *)dma->io;
	काष्ठा ddb *dev = output->port->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dma->lock, flags);
	अगर (!dma->running)
		जाओ unlock_निकास;
	dma->stat = ddbपढ़ोl(dev, DMA_BUFFER_CURRENT(dma));
	dma->ctrl = ddbपढ़ोl(dev, DMA_BUFFER_CONTROL(dma));
	अगर (output->redi)
		output_ack_input(output, output->redi);
	wake_up(&dma->wq);
unlock_निकास:
	spin_unlock_irqrestore(&dma->lock, flags);
पूर्ण

अटल व्योम output_handler(व्योम *data)
अणु
	काष्ठा ddb_output *output = (काष्ठा ddb_output *)data;
	काष्ठा ddb_dma *dma = output->dma;

	queue_work(ddb_wq, &dma->work);
पूर्ण

/****************************************************************************/
/****************************************************************************/

अटल स्थिर काष्ठा ddb_regmap *io_regmap(काष्ठा ddb_io *io, पूर्णांक link)
अणु
	स्थिर काष्ठा ddb_info *info;

	अगर (link)
		info = io->port->dev->link[io->port->lnr].info;
	अन्यथा
		info = io->port->dev->link[0].info;

	अगर (!info)
		वापस शून्य;

	वापस info->regmap;
पूर्ण

अटल व्योम ddb_dma_init(काष्ठा ddb_io *io, पूर्णांक nr, पूर्णांक out)
अणु
	काष्ठा ddb_dma *dma;
	स्थिर काष्ठा ddb_regmap *rm = io_regmap(io, 0);

	dma = out ? &io->port->dev->odma[nr] : &io->port->dev->idma[nr];
	io->dma = dma;
	dma->io = io;

	spin_lock_init(&dma->lock);
	init_रुकोqueue_head(&dma->wq);
	अगर (out) अणु
		INIT_WORK(&dma->work, output_work);
		dma->regs = rm->odma->base + rm->odma->size * nr;
		dma->bufregs = rm->odma_buf->base + rm->odma_buf->size * nr;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->भाग = 1;
	पूर्ण अन्यथा अणु
		INIT_WORK(&dma->work, input_work);
		dma->regs = rm->idma->base + rm->idma->size * nr;
		dma->bufregs = rm->idma_buf->base + rm->idma_buf->size * nr;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->भाग = 1;
	पूर्ण
	ddbग_लिखोl(io->port->dev, 0, DMA_BUFFER_ACK(dma));
	dev_dbg(io->port->dev->dev, "init link %u, io %u, dma %u, dmaregs %08x bufregs %08x\n",
		io->port->lnr, io->nr, nr, dma->regs, dma->bufregs);
पूर्ण

अटल व्योम ddb_input_init(काष्ठा ddb_port *port, पूर्णांक nr, पूर्णांक pnr, पूर्णांक anr)
अणु
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_input *input = &dev->input[anr];
	स्थिर काष्ठा ddb_regmap *rm;

	port->input[pnr] = input;
	input->nr = nr;
	input->port = port;
	rm = io_regmap(input, 1);
	input->regs = DDB_LINK_TAG(port->lnr) |
		(rm->input->base + rm->input->size * nr);
	dev_dbg(dev->dev, "init link %u, input %u, regs %08x\n",
		port->lnr, nr, input->regs);

	अगर (dev->has_dma) अणु
		स्थिर काष्ठा ddb_regmap *rm0 = io_regmap(input, 0);
		u32 base = rm0->irq_base_idma;
		u32 dma_nr = nr;

		अगर (port->lnr)
			dma_nr += 32 + (port->lnr - 1) * 8;

		dev_dbg(dev->dev, "init link %u, input %u, handler %u\n",
			port->lnr, nr, dma_nr + base);

		ddb_irq_set(dev, 0, dma_nr + base, &input_handler, input);
		ddb_dma_init(input, dma_nr, 0);
	पूर्ण
पूर्ण

अटल व्योम ddb_output_init(काष्ठा ddb_port *port, पूर्णांक nr)
अणु
	काष्ठा ddb *dev = port->dev;
	काष्ठा ddb_output *output = &dev->output[nr];
	स्थिर काष्ठा ddb_regmap *rm;

	port->output = output;
	output->nr = nr;
	output->port = port;
	rm = io_regmap(output, 1);
	output->regs = DDB_LINK_TAG(port->lnr) |
		(rm->output->base + rm->output->size * nr);

	dev_dbg(dev->dev, "init link %u, output %u, regs %08x\n",
		port->lnr, nr, output->regs);

	अगर (dev->has_dma) अणु
		स्थिर काष्ठा ddb_regmap *rm0 = io_regmap(output, 0);
		u32 base = rm0->irq_base_odma;

		ddb_irq_set(dev, 0, nr + base, &output_handler, output);
		ddb_dma_init(output, nr, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक ddb_port_match_i2c(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb *dev = port->dev;
	u32 i;

	क्रम (i = 0; i < dev->i2c_num; i++) अणु
		अगर (dev->i2c[i].link == port->lnr &&
		    dev->i2c[i].nr == port->nr) अणु
			port->i2c = &dev->i2c[i];
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ddb_port_match_link_i2c(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb *dev = port->dev;
	u32 i;

	क्रम (i = 0; i < dev->i2c_num; i++) अणु
		अगर (dev->i2c[i].link == port->lnr) अणु
			port->i2c = &dev->i2c[i];
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम ddb_ports_init(काष्ठा ddb *dev)
अणु
	u32 i, l, p;
	काष्ठा ddb_port *port;
	स्थिर काष्ठा ddb_info *info;
	स्थिर काष्ठा ddb_regmap *rm;

	क्रम (p = l = 0; l < DDB_MAX_LINK; l++) अणु
		info = dev->link[l].info;
		अगर (!info)
			जारी;
		rm = info->regmap;
		अगर (!rm)
			जारी;
		क्रम (i = 0; i < info->port_num; i++, p++) अणु
			port = &dev->port[p];
			port->dev = dev;
			port->nr = i;
			port->lnr = l;
			port->pnr = p;
			port->gap = 0xffffffff;
			port->obr = ci_bitrate;
			mutex_init(&port->i2c_gate_lock);

			अगर (!ddb_port_match_i2c(port)) अणु
				अगर (info->type == DDB_OCTOPUS_MAX)
					ddb_port_match_link_i2c(port);
			पूर्ण

			ddb_port_probe(port);

			port->dvb[0].adap = &dev->adap[2 * p];
			port->dvb[1].adap = &dev->adap[2 * p + 1];

			अगर (port->class == DDB_PORT_NONE && i && p &&
			    dev->port[p - 1].type == DDB_CI_EXTERNAL_XO2) अणु
				port->class = DDB_PORT_CI;
				port->type = DDB_CI_EXTERNAL_XO2_B;
				port->name = "DuoFlex CI_B";
				port->i2c = dev->port[p - 1].i2c;
			पूर्ण

			dev_info(dev->dev, "Port %u: Link %u, Link Port %u (TAB %u): %s\n",
				 port->pnr, port->lnr, port->nr, port->nr + 1,
				 port->name);

			अगर (port->class == DDB_PORT_CI &&
			    port->type == DDB_CI_EXTERNAL_XO2) अणु
				ddb_input_init(port, 2 * i, 0, 2 * i);
				ddb_output_init(port, i);
				जारी;
			पूर्ण

			अगर (port->class == DDB_PORT_CI &&
			    port->type == DDB_CI_EXTERNAL_XO2_B) अणु
				ddb_input_init(port, 2 * i - 1, 0, 2 * i - 1);
				ddb_output_init(port, i);
				जारी;
			पूर्ण

			अगर (port->class == DDB_PORT_NONE)
				जारी;

			चयन (dev->link[l].info->type) अणु
			हाल DDB_OCTOPUS_CI:
				अगर (i >= 2) अणु
					ddb_input_init(port, 2 + i, 0, 2 + i);
					ddb_input_init(port, 4 + i, 1, 4 + i);
					ddb_output_init(port, i);
					अवरोध;
				पूर्ण
				fallthrough;
			हाल DDB_OCTOPUS:
				ddb_input_init(port, 2 * i, 0, 2 * i);
				ddb_input_init(port, 2 * i + 1, 1, 2 * i + 1);
				ddb_output_init(port, i);
				अवरोध;
			हाल DDB_OCTOPUS_MAX:
			हाल DDB_OCTOPUS_MAX_CT:
			हाल DDB_OCTOPUS_MCI:
				ddb_input_init(port, 2 * i, 0, 2 * p);
				ddb_input_init(port, 2 * i + 1, 1, 2 * p + 1);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	dev->port_num = p;
पूर्ण

व्योम ddb_ports_release(काष्ठा ddb *dev)
अणु
	पूर्णांक i;
	काष्ठा ddb_port *port;

	क्रम (i = 0; i < dev->port_num; i++) अणु
		port = &dev->port[i];
		अगर (port->input[0] && port->input[0]->dma)
			cancel_work_sync(&port->input[0]->dma->work);
		अगर (port->input[1] && port->input[1]->dma)
			cancel_work_sync(&port->input[1]->dma->work);
		अगर (port->output && port->output->dma)
			cancel_work_sync(&port->output->dma->work);
	पूर्ण
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#घोषणा IRQ_HANDLE(_nr) \
	करो अणु अगर ((s & (1UL << ((_nr) & 0x1f))) && \
		 dev->link[0].irq[_nr].handler) \
		dev->link[0].irq[_nr].handler(dev->link[0].irq[_nr].data); पूर्ण \
	जबतक (0)

#घोषणा IRQ_HANDLE_NIBBLE(_shअगरt) अणु		     \
	अगर (s & (0x0000000f << ((_shअगरt) & 0x1f))) अणु \
		IRQ_HANDLE(0 + (_shअगरt));	     \
		IRQ_HANDLE(1 + (_shअगरt));	     \
		IRQ_HANDLE(2 + (_shअगरt));	     \
		IRQ_HANDLE(3 + (_shअगरt));	     \
	पूर्ण					     \
पूर्ण

#घोषणा IRQ_HANDLE_BYTE(_shअगरt) अणु		     \
	अगर (s & (0x000000ff << ((_shअगरt) & 0x1f))) अणु \
		IRQ_HANDLE(0 + (_shअगरt));	     \
		IRQ_HANDLE(1 + (_shअगरt));	     \
		IRQ_HANDLE(2 + (_shअगरt));	     \
		IRQ_HANDLE(3 + (_shअगरt));	     \
		IRQ_HANDLE(4 + (_shअगरt));	     \
		IRQ_HANDLE(5 + (_shअगरt));	     \
		IRQ_HANDLE(6 + (_shअगरt));	     \
		IRQ_HANDLE(7 + (_shअगरt));	     \
	पूर्ण					     \
पूर्ण

अटल व्योम irq_handle_msg(काष्ठा ddb *dev, u32 s)
अणु
	dev->i2c_irq++;
	IRQ_HANDLE_NIBBLE(0);
पूर्ण

अटल व्योम irq_handle_io(काष्ठा ddb *dev, u32 s)
अणु
	dev->ts_irq++;
	IRQ_HANDLE_NIBBLE(4);
	IRQ_HANDLE_BYTE(8);
	IRQ_HANDLE_BYTE(16);
	IRQ_HANDLE_BYTE(24);
पूर्ण

irqवापस_t ddb_irq_handler0(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ddb *dev = (काष्ठा ddb *)dev_id;
	u32 mask = 0x8fffff00;
	u32 s = mask & ddbपढ़ोl(dev, INTERRUPT_STATUS);

	अगर (!s)
		वापस IRQ_NONE;
	करो अणु
		अगर (s & 0x80000000)
			वापस IRQ_NONE;
		ddbग_लिखोl(dev, s, INTERRUPT_ACK);
		irq_handle_io(dev, s);
	पूर्ण जबतक ((s = mask & ddbपढ़ोl(dev, INTERRUPT_STATUS)));

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t ddb_irq_handler1(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ddb *dev = (काष्ठा ddb *)dev_id;
	u32 mask = 0x8000000f;
	u32 s = mask & ddbपढ़ोl(dev, INTERRUPT_STATUS);

	अगर (!s)
		वापस IRQ_NONE;
	करो अणु
		अगर (s & 0x80000000)
			वापस IRQ_NONE;
		ddbग_लिखोl(dev, s, INTERRUPT_ACK);
		irq_handle_msg(dev, s);
	पूर्ण जबतक ((s = mask & ddbपढ़ोl(dev, INTERRUPT_STATUS)));

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t ddb_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ddb *dev = (काष्ठा ddb *)dev_id;
	u32 s = ddbपढ़ोl(dev, INTERRUPT_STATUS);
	पूर्णांक ret = IRQ_HANDLED;

	अगर (!s)
		वापस IRQ_NONE;
	करो अणु
		अगर (s & 0x80000000)
			वापस IRQ_NONE;
		ddbग_लिखोl(dev, s, INTERRUPT_ACK);

		अगर (s & 0x0000000f)
			irq_handle_msg(dev, s);
		अगर (s & 0x0fffff00)
			irq_handle_io(dev, s);
	पूर्ण जबतक ((s = ddbपढ़ोl(dev, INTERRUPT_STATUS)));

	वापस ret;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक reg_रुको(काष्ठा ddb *dev, u32 reg, u32 bit)
अणु
	u32 count = 0;

	जबतक (safe_ddbपढ़ोl(dev, reg) & bit) अणु
		ndelay(10);
		अगर (++count == 100)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flashio(काष्ठा ddb *dev, u32 lnr, u8 *wbuf, u32 wlen, u8 *rbuf,
		   u32 rlen)
अणु
	u32 data, shअगरt;
	u32 tag = DDB_LINK_TAG(lnr);
	काष्ठा ddb_link *link = &dev->link[lnr];

	mutex_lock(&link->flash_mutex);
	अगर (wlen > 4)
		ddbग_लिखोl(dev, 1, tag | SPI_CONTROL);
	जबतक (wlen > 4) अणु
		/* FIXME: check क्रम big-endian */
		data = swab32(*(u32 *)wbuf);
		wbuf += 4;
		wlen -= 4;
		ddbग_लिखोl(dev, data, tag | SPI_DATA);
		अगर (reg_रुको(dev, tag | SPI_CONTROL, 4))
			जाओ fail;
	पूर्ण
	अगर (rlen)
		ddbग_लिखोl(dev, 0x0001 | ((wlen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTROL);
	अन्यथा
		ddbग_लिखोl(dev, 0x0003 | ((wlen << (8 + 3)) & 0x1f00),
			  tag | SPI_CONTROL);

	data = 0;
	shअगरt = ((4 - wlen) * 8);
	जबतक (wlen) अणु
		data <<= 8;
		data |= *wbuf;
		wlen--;
		wbuf++;
	पूर्ण
	अगर (shअगरt)
		data <<= shअगरt;
	ddbग_लिखोl(dev, data, tag | SPI_DATA);
	अगर (reg_रुको(dev, tag | SPI_CONTROL, 4))
		जाओ fail;

	अगर (!rlen) अणु
		ddbग_लिखोl(dev, 0, tag | SPI_CONTROL);
		जाओ निकास;
	पूर्ण
	अगर (rlen > 4)
		ddbग_लिखोl(dev, 1, tag | SPI_CONTROL);

	जबतक (rlen > 4) अणु
		ddbग_लिखोl(dev, 0xffffffff, tag | SPI_DATA);
		अगर (reg_रुको(dev, tag | SPI_CONTROL, 4))
			जाओ fail;
		data = ddbपढ़ोl(dev, tag | SPI_DATA);
		*(u32 *)rbuf = swab32(data);
		rbuf += 4;
		rlen -= 4;
	पूर्ण
	ddbग_लिखोl(dev, 0x0003 | ((rlen << (8 + 3)) & 0x1F00),
		  tag | SPI_CONTROL);
	ddbग_लिखोl(dev, 0xffffffff, tag | SPI_DATA);
	अगर (reg_रुको(dev, tag | SPI_CONTROL, 4))
		जाओ fail;

	data = ddbपढ़ोl(dev, tag | SPI_DATA);
	ddbग_लिखोl(dev, 0, tag | SPI_CONTROL);

	अगर (rlen < 4)
		data <<= ((4 - rlen) * 8);

	जबतक (rlen > 0) अणु
		*rbuf = ((data >> 24) & 0xff);
		data <<= 8;
		rbuf++;
		rlen--;
	पूर्ण
निकास:
	mutex_unlock(&link->flash_mutex);
	वापस 0;
fail:
	mutex_unlock(&link->flash_mutex);
	वापस -1;
पूर्ण

पूर्णांक ddbridge_flashपढ़ो(काष्ठा ddb *dev, u32 link, u8 *buf, u32 addr, u32 len)
अणु
	u8 cmd[4] = अणु0x03, (addr >> 16) & 0xff,
		     (addr >> 8) & 0xff, addr & 0xffपूर्ण;

	वापस flashio(dev, link, cmd, 4, buf, len);
पूर्ण

/*
 * TODO/FIXME: add/implement IOCTLs from upstream driver
 */

#घोषणा DDB_NAME "ddbridge"

अटल u32 ddb_num;
अटल पूर्णांक ddb_major;
अटल DEFINE_MUTEX(ddb_mutex);

अटल पूर्णांक ddb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ddb *dev = file->निजी_data;

	dev->ddb_dev_users--;
	वापस 0;
पूर्ण

अटल पूर्णांक ddb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ddb *dev = ddbs[iminor(inode)];

	अगर (dev->ddb_dev_users)
		वापस -EBUSY;
	dev->ddb_dev_users++;
	file->निजी_data = dev;
	वापस 0;
पूर्ण

अटल दीर्घ ddb_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ddb *dev = file->निजी_data;

	dev_warn(dev->dev, "DDB IOCTLs unsupported (cmd: %d, arg: %lu)\n",
		 cmd, arg);

	वापस -ENOTTY;
पूर्ण

अटल स्थिर काष्ठा file_operations ddb_fops = अणु
	.unlocked_ioctl = ddb_ioctl,
	.खोलो           = ddb_खोलो,
	.release        = ddb_release,
पूर्ण;

अटल अक्षर *ddb_devnode(काष्ठा device *device, umode_t *mode)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस kaप्र_लिखो(GFP_KERNEL, "ddbridge/card%d", dev->nr);
पूर्ण

#घोषणा __ATTR_MRO(_name, _show) अणु				\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0444 पूर्ण,	\
	.show	= _show,					\
पूर्ण

#घोषणा __ATTR_MWO(_name, _store) अणु				\
	.attr	= अणु .name = __stringअगरy(_name), .mode = 0222 पूर्ण,	\
	.store	= _store,					\
पूर्ण

अटल sमाप_प्रकार ports_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%d\n", dev->port_num);
पूर्ण

अटल sमाप_प्रकार ts_irq_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%d\n", dev->ts_irq);
पूर्ण

अटल sमाप_प्रकार i2c_irq_show(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%d\n", dev->i2c_irq);
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	u32 val;

	val = ddbपढ़ोl(dev, GPIO_OUTPUT) & 1;
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_store(काष्ठा device *device, काष्ठा device_attribute *d,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	u32 val;

	अगर (माला_पूछो(buf, "%u\n", &val) != 1)
		वापस -EINVAL;
	ddbग_लिखोl(dev, 1, GPIO_सूचीECTION);
	ddbग_लिखोl(dev, val & 1, GPIO_OUTPUT);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fanspeed_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[8] - 0x30;
	काष्ठा ddb_link *link = &dev->link[num];
	u32 spd;

	spd = ddblपढ़ोl(link, TEMPMON_FANCONTROL) & 0xff;
	वापस प्र_लिखो(buf, "%u\n", spd * 100);
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	काष्ठा ddb_link *link = &dev->link[0];
	काष्ठा i2c_adapter *adap;
	पूर्णांक temp, temp2;
	u8 पंचांगp[2];

	अगर (!link->info->temp_num)
		वापस प्र_लिखो(buf, "no sensor\n");
	adap = &dev->i2c[link->info->temp_bus].adap;
	अगर (i2c_पढ़ो_regs(adap, 0x48, 0, पंचांगp, 2) < 0)
		वापस प्र_लिखो(buf, "read_error\n");
	temp = (पंचांगp[0] << 3) | (पंचांगp[1] >> 5);
	temp *= 125;
	अगर (link->info->temp_num == 2) अणु
		अगर (i2c_पढ़ो_regs(adap, 0x49, 0, पंचांगp, 2) < 0)
			वापस प्र_लिखो(buf, "read_error\n");
		temp2 = (पंचांगp[0] << 3) | (पंचांगp[1] >> 5);
		temp2 *= 125;
		वापस प्र_लिखो(buf, "%d %d\n", temp, temp2);
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार ctemp_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	काष्ठा i2c_adapter *adap;
	पूर्णांक temp;
	u8 पंचांगp[2];
	पूर्णांक num = attr->attr.name[4] - 0x30;

	adap = &dev->i2c[num].adap;
	अगर (!adap)
		वापस 0;
	अगर (i2c_पढ़ो_regs(adap, 0x49, 0, पंचांगp, 2) < 0)
		अगर (i2c_पढ़ो_regs(adap, 0x4d, 0, पंचांगp, 2) < 0)
			वापस प्र_लिखो(buf, "no sensor\n");
	temp = पंचांगp[0] * 1000;
	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार led_show(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[3] - 0x30;

	वापस प्र_लिखो(buf, "%d\n", dev->leds & (1 << num) ? 1 : 0);
पूर्ण

अटल व्योम ddb_set_led(काष्ठा ddb *dev, पूर्णांक num, पूर्णांक val)
अणु
	अगर (!dev->link[0].info->led_num)
		वापस;
	चयन (dev->port[num].class) अणु
	हाल DDB_PORT_TUNER:
		चयन (dev->port[num].type) अणु
		हाल DDB_TUNER_DVBS_ST:
			i2c_ग_लिखो_reg16(&dev->i2c[num].adap,
					0x69, 0xf14c, val ? 2 : 0);
			अवरोध;
		हाल DDB_TUNER_DVBCT_ST:
			i2c_ग_लिखो_reg16(&dev->i2c[num].adap,
					0x1f, 0xf00e, 0);
			i2c_ग_लिखो_reg16(&dev->i2c[num].adap,
					0x1f, 0xf00f, val ? 1 : 0);
			अवरोध;
		हाल DDB_TUNER_XO2 ... DDB_TUNER_DVBC2T2I_SONY:
		अणु
			u8 v;

			i2c_पढ़ो_reg(&dev->i2c[num].adap, 0x10, 0x08, &v);
			v = (v & ~0x10) | (val ? 0x10 : 0);
			i2c_ग_लिखो_reg(&dev->i2c[num].adap, 0x10, 0x08, v);
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार led_store(काष्ठा device *device,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[3] - 0x30;
	u32 val;

	अगर (माला_पूछो(buf, "%u\n", &val) != 1)
		वापस -EINVAL;
	अगर (val)
		dev->leds |= (1 << num);
	अन्यथा
		dev->leds &= ~(1 << num);
	ddb_set_led(dev, num, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार snr_show(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	अक्षर snr[32];
	पूर्णांक num = attr->attr.name[3] - 0x30;

	अगर (dev->port[num].type >= DDB_TUNER_XO2) अणु
		अगर (i2c_पढ़ो_regs(&dev->i2c[num].adap, 0x10, 0x10, snr, 16) < 0)
			वापस प्र_लिखो(buf, "NO SNR\n");
		snr[16] = 0;
	पूर्ण अन्यथा अणु
		/* serial number at 0x100-0x11f */
		अगर (i2c_पढ़ो_regs16(&dev->i2c[num].adap,
				    0x57, 0x100, snr, 32) < 0)
			अगर (i2c_पढ़ो_regs16(&dev->i2c[num].adap,
					    0x50, 0x100, snr, 32) < 0)
				वापस प्र_लिखो(buf, "NO SNR\n");
		snr[31] = 0; /* in हाल it is not terminated on EEPROM */
	पूर्ण
	वापस प्र_लिखो(buf, "%s\n", snr);
पूर्ण

अटल sमाप_प्रकार bsnr_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	अक्षर snr[16];

	ddbridge_flashपढ़ो(dev, 0, snr, 0x10, 15);
	snr[15] = 0; /* in हाल it is not terminated on EEPROM */
	वापस प्र_लिखो(buf, "%s\n", snr);
पूर्ण

अटल sमाप_प्रकार bpsnr_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	अचिन्हित अक्षर snr[32];

	अगर (!dev->i2c_num)
		वापस 0;

	अगर (i2c_पढ़ो_regs16(&dev->i2c[0].adap,
			    0x50, 0x0000, snr, 32) < 0 ||
	    snr[0] == 0xff)
		वापस प्र_लिखो(buf, "NO SNR\n");
	snr[31] = 0; /* in हाल it is not terminated on EEPROM */
	वापस प्र_लिखो(buf, "%s\n", snr);
पूर्ण

अटल sमाप_प्रकार redirect_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार redirect_store(काष्ठा device *device,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक i, p;
	पूर्णांक res;

	अगर (माला_पूछो(buf, "%x %x\n", &i, &p) != 2)
		वापस -EINVAL;
	res = ddb_redirect(i, p);
	अगर (res < 0)
		वापस res;
	dev_info(device, "redirect: %02x, %02x\n", i, p);
	वापस count;
पूर्ण

अटल sमाप_प्रकार gap_show(काष्ठा device *device,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[3] - 0x30;

	वापस प्र_लिखो(buf, "%d\n", dev->port[num].gap);
पूर्ण

अटल sमाप_प्रकार gap_store(काष्ठा device *device, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[3] - 0x30;
	अचिन्हित पूर्णांक val;

	अगर (माला_पूछो(buf, "%u\n", &val) != 1)
		वापस -EINVAL;
	अगर (val > 128)
		वापस -EINVAL;
	अगर (val == 128)
		val = 0xffffffff;
	dev->port[num].gap = val;
	वापस count;
पूर्ण

अटल sमाप_प्रकार version_show(काष्ठा device *device,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%08x %08x\n",
		       dev->link[0].ids.hwid, dev->link[0].ids.regmapid);
पूर्ण

अटल sमाप_प्रकार hwid_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "0x%08X\n", dev->link[0].ids.hwid);
पूर्ण

अटल sमाप_प्रकार regmap_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "0x%08X\n", dev->link[0].ids.regmapid);
पूर्ण

अटल sमाप_प्रकार भ_शेषe_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक num = attr->attr.name[5] - 0x30;
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%u\n", dev->link[num].lnb.भ_शेषe);
पूर्ण

अटल sमाप_प्रकार devid_show(काष्ठा device *device,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक num = attr->attr.name[5] - 0x30;
	काष्ठा ddb *dev = dev_get_drvdata(device);

	वापस प्र_लिखो(buf, "%08x\n", dev->link[num].ids.devid);
पूर्ण

अटल sमाप_प्रकार भ_शेषe_store(काष्ठा device *device, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ddb *dev = dev_get_drvdata(device);
	पूर्णांक num = attr->attr.name[5] - 0x30;
	अचिन्हित पूर्णांक val;

	अगर (माला_पूछो(buf, "%u\n", &val) != 1)
		वापस -EINVAL;
	अगर (val > 3)
		वापस -EINVAL;
	ddb_lnb_init_भ_शेषe(dev, &dev->link[num], val);
	वापस count;
पूर्ण

अटल काष्ठा device_attribute ddb_attrs[] = अणु
	__ATTR_RO(version),
	__ATTR_RO(ports),
	__ATTR_RO(ts_irq),
	__ATTR_RO(i2c_irq),
	__ATTR(gap0, 0664, gap_show, gap_store),
	__ATTR(gap1, 0664, gap_show, gap_store),
	__ATTR(gap2, 0664, gap_show, gap_store),
	__ATTR(gap3, 0664, gap_show, gap_store),
	__ATTR(भ_शेषe0, 0664, भ_शेषe_show, भ_शेषe_store),
	__ATTR(भ_शेषe1, 0664, भ_शेषe_show, भ_शेषe_store),
	__ATTR(भ_शेषe2, 0664, भ_शेषe_show, भ_शेषe_store),
	__ATTR(भ_शेषe3, 0664, भ_शेषe_show, भ_शेषe_store),
	__ATTR_MRO(devid0, devid_show),
	__ATTR_MRO(devid1, devid_show),
	__ATTR_MRO(devid2, devid_show),
	__ATTR_MRO(devid3, devid_show),
	__ATTR_RO(hwid),
	__ATTR_RO(regmap),
	__ATTR(redirect, 0664, redirect_show, redirect_store),
	__ATTR_MRO(snr,  bsnr_show),
	__ATTR_RO(bpsnr),
	__ATTR_शून्य,
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_temp[] = अणु
	__ATTR_RO(temp),
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_fan[] = अणु
	__ATTR(fan, 0664, fan_show, fan_store),
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_snr[] = अणु
	__ATTR_MRO(snr0, snr_show),
	__ATTR_MRO(snr1, snr_show),
	__ATTR_MRO(snr2, snr_show),
	__ATTR_MRO(snr3, snr_show),
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_ctemp[] = अणु
	__ATTR_MRO(temp0, ctemp_show),
	__ATTR_MRO(temp1, ctemp_show),
	__ATTR_MRO(temp2, ctemp_show),
	__ATTR_MRO(temp3, ctemp_show),
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_led[] = अणु
	__ATTR(led0, 0664, led_show, led_store),
	__ATTR(led1, 0664, led_show, led_store),
	__ATTR(led2, 0664, led_show, led_store),
	__ATTR(led3, 0664, led_show, led_store),
पूर्ण;

अटल काष्ठा device_attribute ddb_attrs_fanspeed[] = अणु
	__ATTR_MRO(fanspeed0, fanspeed_show),
	__ATTR_MRO(fanspeed1, fanspeed_show),
	__ATTR_MRO(fanspeed2, fanspeed_show),
	__ATTR_MRO(fanspeed3, fanspeed_show),
पूर्ण;

अटल काष्ठा class ddb_class = अणु
	.name		= "ddbridge",
	.owner          = THIS_MODULE,
	.devnode        = ddb_devnode,
पूर्ण;

अटल पूर्णांक ddb_class_create(व्योम)
अणु
	ddb_major = रेजिस्टर_chrdev(0, DDB_NAME, &ddb_fops);
	अगर (ddb_major < 0)
		वापस ddb_major;
	अगर (class_रेजिस्टर(&ddb_class) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम ddb_class_destroy(व्योम)
अणु
	class_unरेजिस्टर(&ddb_class);
	unरेजिस्टर_chrdev(ddb_major, DDB_NAME);
पूर्ण

अटल व्योम ddb_device_attrs_del(काष्ठा ddb *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		अगर (dev->link[i].info && dev->link[i].info->tempmon_irq)
			device_हटाओ_file(dev->ddb_dev,
					   &ddb_attrs_fanspeed[i]);
	क्रम (i = 0; i < dev->link[0].info->temp_num; i++)
		device_हटाओ_file(dev->ddb_dev, &ddb_attrs_temp[i]);
	क्रम (i = 0; i < dev->link[0].info->fan_num; i++)
		device_हटाओ_file(dev->ddb_dev, &ddb_attrs_fan[i]);
	क्रम (i = 0; i < dev->i2c_num && i < 4; i++) अणु
		अगर (dev->link[0].info->led_num)
			device_हटाओ_file(dev->ddb_dev, &ddb_attrs_led[i]);
		device_हटाओ_file(dev->ddb_dev, &ddb_attrs_snr[i]);
		device_हटाओ_file(dev->ddb_dev, &ddb_attrs_ctemp[i]);
	पूर्ण
	क्रम (i = 0; ddb_attrs[i].attr.name; i++)
		device_हटाओ_file(dev->ddb_dev, &ddb_attrs[i]);
पूर्ण

अटल पूर्णांक ddb_device_attrs_add(काष्ठा ddb *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; ddb_attrs[i].attr.name; i++)
		अगर (device_create_file(dev->ddb_dev, &ddb_attrs[i]))
			जाओ fail;
	क्रम (i = 0; i < dev->link[0].info->temp_num; i++)
		अगर (device_create_file(dev->ddb_dev, &ddb_attrs_temp[i]))
			जाओ fail;
	क्रम (i = 0; i < dev->link[0].info->fan_num; i++)
		अगर (device_create_file(dev->ddb_dev, &ddb_attrs_fan[i]))
			जाओ fail;
	क्रम (i = 0; (i < dev->i2c_num) && (i < 4); i++) अणु
		अगर (device_create_file(dev->ddb_dev, &ddb_attrs_snr[i]))
			जाओ fail;
		अगर (device_create_file(dev->ddb_dev, &ddb_attrs_ctemp[i]))
			जाओ fail;
		अगर (dev->link[0].info->led_num)
			अगर (device_create_file(dev->ddb_dev,
					       &ddb_attrs_led[i]))
				जाओ fail;
	पूर्ण
	क्रम (i = 0; i < 4; i++)
		अगर (dev->link[i].info && dev->link[i].info->tempmon_irq)
			अगर (device_create_file(dev->ddb_dev,
					       &ddb_attrs_fanspeed[i]))
				जाओ fail;
	वापस 0;
fail:
	वापस -1;
पूर्ण

पूर्णांक ddb_device_create(काष्ठा ddb *dev)
अणु
	पूर्णांक res = 0;

	अगर (ddb_num == DDB_MAX_ADAPTER)
		वापस -ENOMEM;
	mutex_lock(&ddb_mutex);
	dev->nr = ddb_num;
	ddbs[dev->nr] = dev;
	dev->ddb_dev = device_create(&ddb_class, dev->dev,
				     MKDEV(ddb_major, dev->nr),
				     dev, "ddbridge%d", dev->nr);
	अगर (IS_ERR(dev->ddb_dev)) अणु
		res = PTR_ERR(dev->ddb_dev);
		dev_info(dev->dev, "Could not create ddbridge%d\n", dev->nr);
		जाओ fail;
	पूर्ण
	res = ddb_device_attrs_add(dev);
	अगर (res) अणु
		ddb_device_attrs_del(dev);
		device_destroy(&ddb_class, MKDEV(ddb_major, dev->nr));
		ddbs[dev->nr] = शून्य;
		dev->ddb_dev = ERR_PTR(-ENODEV);
	पूर्ण अन्यथा अणु
		ddb_num++;
	पूर्ण
fail:
	mutex_unlock(&ddb_mutex);
	वापस res;
पूर्ण

व्योम ddb_device_destroy(काष्ठा ddb *dev)
अणु
	अगर (IS_ERR(dev->ddb_dev))
		वापस;
	ddb_device_attrs_del(dev);
	device_destroy(&ddb_class, MKDEV(ddb_major, dev->nr));
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल व्योम tempmon_setfan(काष्ठा ddb_link *link)
अणु
	u32 temp, temp2, pwm;

	अगर ((ddblपढ़ोl(link, TEMPMON_CONTROL) &
	    TEMPMON_CONTROL_OVERTEMP) != 0) अणु
		dev_info(link->dev->dev, "Over temperature condition\n");
		link->overtemperature_error = 1;
	पूर्ण
	temp  = (ddblपढ़ोl(link, TEMPMON_SENSOR0) >> 8) & 0xFF;
	अगर (temp & 0x80)
		temp = 0;
	temp2  = (ddblपढ़ोl(link, TEMPMON_SENSOR1) >> 8) & 0xFF;
	अगर (temp2 & 0x80)
		temp2 = 0;
	अगर (temp2 > temp)
		temp = temp2;

	pwm = (ddblपढ़ोl(link, TEMPMON_FANCONTROL) >> 8) & 0x0F;
	अगर (pwm > 10)
		pwm = 10;

	अगर (temp >= link->temp_tab[pwm]) अणु
		जबतक (pwm < 10 && temp >= link->temp_tab[pwm + 1])
			pwm += 1;
	पूर्ण अन्यथा अणु
		जबतक (pwm > 1 && temp < link->temp_tab[pwm - 2])
			pwm -= 1;
	पूर्ण
	ddblग_लिखोl(link, (pwm << 8), TEMPMON_FANCONTROL);
पूर्ण

अटल व्योम temp_handler(व्योम *data)
अणु
	काष्ठा ddb_link *link = (काष्ठा ddb_link *)data;

	spin_lock(&link->temp_lock);
	tempmon_setfan(link);
	spin_unlock(&link->temp_lock);
पूर्ण

अटल पूर्णांक tempmon_init(काष्ठा ddb_link *link, पूर्णांक first_समय)
अणु
	काष्ठा ddb *dev = link->dev;
	पूर्णांक status = 0;
	u32 l = link->nr;

	spin_lock_irq(&link->temp_lock);
	अगर (first_समय) अणु
		अटल u8 temperature_table[11] = अणु
			30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80 पूर्ण;

		स_नकल(link->temp_tab, temperature_table,
		       माप(temperature_table));
	पूर्ण
	ddb_irq_set(dev, l, link->info->tempmon_irq, temp_handler, link);
	ddblग_लिखोl(link, (TEMPMON_CONTROL_OVERTEMP | TEMPMON_CONTROL_AUTOSCAN |
			  TEMPMON_CONTROL_INTENABLE),
		   TEMPMON_CONTROL);
	ddblग_लिखोl(link, (3 << 8), TEMPMON_FANCONTROL);

	link->overtemperature_error =
		((ddblपढ़ोl(link, TEMPMON_CONTROL) &
			TEMPMON_CONTROL_OVERTEMP) != 0);
	अगर (link->overtemperature_error) अणु
		dev_info(link->dev->dev, "Over temperature condition\n");
		status = -1;
	पूर्ण
	tempmon_setfan(link);
	spin_unlock_irq(&link->temp_lock);
	वापस status;
पूर्ण

अटल पूर्णांक ddb_init_tempmon(काष्ठा ddb_link *link)
अणु
	स्थिर काष्ठा ddb_info *info = link->info;

	अगर (!info->tempmon_irq)
		वापस 0;
	अगर (info->type == DDB_OCTOPUS_MAX_CT)
		अगर (link->ids.regmapid < 0x00010002)
			वापस 0;
	spin_lock_init(&link->temp_lock);
	dev_dbg(link->dev->dev, "init_tempmon\n");
	वापस tempmon_init(link, 1);
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक ddb_init_boards(काष्ठा ddb *dev)
अणु
	स्थिर काष्ठा ddb_info *info;
	काष्ठा ddb_link *link;
	u32 l;

	क्रम (l = 0; l < DDB_MAX_LINK; l++) अणु
		link = &dev->link[l];
		info = link->info;

		अगर (!info)
			जारी;
		अगर (info->board_control) अणु
			ddbग_लिखोl(dev, 0, DDB_LINK_TAG(l) | BOARD_CONTROL);
			msleep(100);
			ddbग_लिखोl(dev, info->board_control_2,
				  DDB_LINK_TAG(l) | BOARD_CONTROL);
			usleep_range(2000, 3000);
			ddbग_लिखोl(dev,
				  info->board_control_2 | info->board_control,
				  DDB_LINK_TAG(l) | BOARD_CONTROL);
			usleep_range(2000, 3000);
		पूर्ण
		ddb_init_tempmon(link);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ddb_init(काष्ठा ddb *dev)
अणु
	mutex_init(&dev->link[0].lnb.lock);
	mutex_init(&dev->link[0].flash_mutex);
	अगर (no_init) अणु
		ddb_device_create(dev);
		वापस 0;
	पूर्ण

	ddb_init_boards(dev);

	अगर (ddb_i2c_init(dev) < 0)
		जाओ fail1;
	ddb_ports_init(dev);
	अगर (ddb_buffers_alloc(dev) < 0) अणु
		dev_info(dev->dev, "Could not allocate buffer memory\n");
		जाओ fail2;
	पूर्ण
	अगर (ddb_ports_attach(dev) < 0)
		जाओ fail3;

	ddb_device_create(dev);

	अगर (dev->link[0].info->fan_num)	अणु
		ddbग_लिखोl(dev, 1, GPIO_सूचीECTION);
		ddbग_लिखोl(dev, 1, GPIO_OUTPUT);
	पूर्ण
	वापस 0;

fail3:
	dev_err(dev->dev, "fail3\n");
	ddb_ports_detach(dev);
	ddb_buffers_मुक्त(dev);
fail2:
	dev_err(dev->dev, "fail2\n");
	ddb_ports_release(dev);
	ddb_i2c_release(dev);
fail1:
	dev_err(dev->dev, "fail1\n");
	वापस -1;
पूर्ण

व्योम ddb_unmap(काष्ठा ddb *dev)
अणु
	अगर (dev->regs)
		iounmap(dev->regs);
	vमुक्त(dev);
पूर्ण

पूर्णांक ddb_निकास_ddbridge(पूर्णांक stage, पूर्णांक error)
अणु
	चयन (stage) अणु
	शेष:
	हाल 2:
		destroy_workqueue(ddb_wq);
		fallthrough;
	हाल 1:
		ddb_class_destroy();
		अवरोध;
	पूर्ण

	वापस error;
पूर्ण

पूर्णांक ddb_init_ddbridge(व्योम)
अणु
	अगर (dma_buf_num < 8)
		dma_buf_num = 8;
	अगर (dma_buf_num > 32)
		dma_buf_num = 32;
	अगर (dma_buf_size < 1)
		dma_buf_size = 1;
	अगर (dma_buf_size > 43)
		dma_buf_size = 43;

	अगर (ddb_class_create() < 0)
		वापस -1;
	ddb_wq = alloc_workqueue("ddbridge", 0, 0);
	अगर (!ddb_wq)
		वापस ddb_निकास_ddbridge(1, -1);

	वापस 0;
पूर्ण
