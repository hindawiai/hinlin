<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Helper library क्रम PATA timings
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>

/*
 * This mode timing computation functionality is ported over from
 * drivers/ide/ide-timing.h and was originally written by Vojtech Pavlik
 */
/*
 * PIO 0-4, MWDMA 0-2 and UDMA 0-6 timings (in nanoseconds).
 * These were taken from ATA/ATAPI-6 standard, rev 0a, except
 * क्रम UDMA6, which is currently supported only by Maxtor drives.
 *
 * For PIO 5/6 MWDMA 3/4 see the CFA specअगरication 3.0.
 */

अटल स्थिर काष्ठा ata_timing ata_timing[] = अणु
/*	अणु XFER_PIO_SLOW, 120, 290, 240, 960, 290, 240, 0,  960,   0 पूर्ण, */
	अणु XFER_PIO_0,     70, 290, 240, 600, 165, 150, 0,  600,   0 पूर्ण,
	अणु XFER_PIO_1,     50, 290,  93, 383, 125, 100, 0,  383,   0 पूर्ण,
	अणु XFER_PIO_2,     30, 290,  40, 330, 100,  90, 0,  240,   0 पूर्ण,
	अणु XFER_PIO_3,     30,  80,  70, 180,  80,  70, 0,  180,   0 पूर्ण,
	अणु XFER_PIO_4,     25,  70,  25, 120,  70,  25, 0,  120,   0 पूर्ण,
	अणु XFER_PIO_5,     15,  65,  25, 100,  65,  25, 0,  100,   0 पूर्ण,
	अणु XFER_PIO_6,     10,  55,  20,  80,  55,  20, 0,   80,   0 पूर्ण,

	अणु XFER_SW_DMA_0, 120,   0,   0,   0, 480, 480, 50, 960,   0 पूर्ण,
	अणु XFER_SW_DMA_1,  90,   0,   0,   0, 240, 240, 30, 480,   0 पूर्ण,
	अणु XFER_SW_DMA_2,  60,   0,   0,   0, 120, 120, 20, 240,   0 पूर्ण,

	अणु XFER_MW_DMA_0,  60,   0,   0,   0, 215, 215, 20, 480,   0 पूर्ण,
	अणु XFER_MW_DMA_1,  45,   0,   0,   0,  80,  50, 5,  150,   0 पूर्ण,
	अणु XFER_MW_DMA_2,  25,   0,   0,   0,  70,  25, 5,  120,   0 पूर्ण,
	अणु XFER_MW_DMA_3,  25,   0,   0,   0,  65,  25, 5,  100,   0 पूर्ण,
	अणु XFER_MW_DMA_4,  25,   0,   0,   0,  55,  20, 5,   80,   0 पूर्ण,

/*	अणु XFER_UDMA_SLOW,  0,   0,   0,   0,   0,   0, 0,    0, 150 पूर्ण, */
	अणु XFER_UDMA_0,     0,   0,   0,   0,   0,   0, 0,    0, 120 पूर्ण,
	अणु XFER_UDMA_1,     0,   0,   0,   0,   0,   0, 0,    0,  80 पूर्ण,
	अणु XFER_UDMA_2,     0,   0,   0,   0,   0,   0, 0,    0,  60 पूर्ण,
	अणु XFER_UDMA_3,     0,   0,   0,   0,   0,   0, 0,    0,  45 पूर्ण,
	अणु XFER_UDMA_4,     0,   0,   0,   0,   0,   0, 0,    0,  30 पूर्ण,
	अणु XFER_UDMA_5,     0,   0,   0,   0,   0,   0, 0,    0,  20 पूर्ण,
	अणु XFER_UDMA_6,     0,   0,   0,   0,   0,   0, 0,    0,  15 पूर्ण,

	अणु 0xFF पूर्ण
पूर्ण;

#घोषणा ENOUGH(v, unit)		(((v)-1)/(unit)+1)
#घोषणा EZ(v, unit)		((v)?ENOUGH(((v) * 1000), unit):0)

अटल व्योम ata_timing_quantize(स्थिर काष्ठा ata_timing *t,
				काष्ठा ata_timing *q, पूर्णांक T, पूर्णांक UT)
अणु
	q->setup	= EZ(t->setup,       T);
	q->act8b	= EZ(t->act8b,       T);
	q->rec8b	= EZ(t->rec8b,       T);
	q->cyc8b	= EZ(t->cyc8b,       T);
	q->active	= EZ(t->active,      T);
	q->recover	= EZ(t->recover,     T);
	q->dmack_hold	= EZ(t->dmack_hold,  T);
	q->cycle	= EZ(t->cycle,       T);
	q->udma		= EZ(t->udma,       UT);
पूर्ण

व्योम ata_timing_merge(स्थिर काष्ठा ata_timing *a, स्थिर काष्ठा ata_timing *b,
		      काष्ठा ata_timing *m, अचिन्हित पूर्णांक what)
अणु
	अगर (what & ATA_TIMING_SETUP)
		m->setup = max(a->setup, b->setup);
	अगर (what & ATA_TIMING_ACT8B)
		m->act8b = max(a->act8b, b->act8b);
	अगर (what & ATA_TIMING_REC8B)
		m->rec8b = max(a->rec8b, b->rec8b);
	अगर (what & ATA_TIMING_CYC8B)
		m->cyc8b = max(a->cyc8b, b->cyc8b);
	अगर (what & ATA_TIMING_ACTIVE)
		m->active = max(a->active, b->active);
	अगर (what & ATA_TIMING_RECOVER)
		m->recover = max(a->recover, b->recover);
	अगर (what & ATA_TIMING_DMACK_HOLD)
		m->dmack_hold = max(a->dmack_hold, b->dmack_hold);
	अगर (what & ATA_TIMING_CYCLE)
		m->cycle = max(a->cycle, b->cycle);
	अगर (what & ATA_TIMING_UDMA)
		m->udma = max(a->udma, b->udma);
पूर्ण
EXPORT_SYMBOL_GPL(ata_timing_merge);

स्थिर काष्ठा ata_timing *ata_timing_find_mode(u8 xfer_mode)
अणु
	स्थिर काष्ठा ata_timing *t = ata_timing;

	जबतक (xfer_mode > t->mode)
		t++;

	अगर (xfer_mode == t->mode)
		वापस t;

	WARN_ONCE(true, "%s: unable to find timing for xfer_mode 0x%x\n",
			__func__, xfer_mode);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ata_timing_find_mode);

पूर्णांक ata_timing_compute(काष्ठा ata_device *adev, अचिन्हित लघु speed,
		       काष्ठा ata_timing *t, पूर्णांक T, पूर्णांक UT)
अणु
	स्थिर u16 *id = adev->id;
	स्थिर काष्ठा ata_timing *s;
	काष्ठा ata_timing p;

	/*
	 * Find the mode.
	 */
	s = ata_timing_find_mode(speed);
	अगर (!s)
		वापस -EINVAL;

	स_नकल(t, s, माप(*s));

	/*
	 * If the drive is an EIDE drive, it can tell us it needs extended
	 * PIO/MW_DMA cycle timing.
	 */

	अगर (id[ATA_ID_FIELD_VALID] & 2) अणु	/* EIDE drive */
		स_रखो(&p, 0, माप(p));

		अगर (speed >= XFER_PIO_0 && speed < XFER_SW_DMA_0) अणु
			अगर (speed <= XFER_PIO_2)
				p.cycle = p.cyc8b = id[ATA_ID_EIDE_PIO];
			अन्यथा अगर ((speed <= XFER_PIO_4) ||
				 (speed == XFER_PIO_5 && !ata_id_is_cfa(id)))
				p.cycle = p.cyc8b = id[ATA_ID_EIDE_PIO_IORDY];
		पूर्ण अन्यथा अगर (speed >= XFER_MW_DMA_0 && speed <= XFER_MW_DMA_2)
			p.cycle = id[ATA_ID_EIDE_DMA_MIN];

		ata_timing_merge(&p, t, t, ATA_TIMING_CYCLE | ATA_TIMING_CYC8B);
	पूर्ण

	/*
	 * Convert the timing to bus घड़ी counts.
	 */

	ata_timing_quantize(t, t, T, UT);

	/*
	 * Even in DMA/UDMA modes we still use PIO access क्रम IDENTIFY,
	 * S.M.A.R.T * and some other commands. We have to ensure that the
	 * DMA cycle timing is slower/equal than the fastest PIO timing.
	 */

	अगर (speed > XFER_PIO_6) अणु
		ata_timing_compute(adev, adev->pio_mode, &p, T, UT);
		ata_timing_merge(&p, t, t, ATA_TIMING_ALL);
	पूर्ण

	/*
	 * Lengthen active & recovery समय so that cycle समय is correct.
	 */

	अगर (t->act8b + t->rec8b < t->cyc8b) अणु
		t->act8b += (t->cyc8b - (t->act8b + t->rec8b)) / 2;
		t->rec8b = t->cyc8b - t->act8b;
	पूर्ण

	अगर (t->active + t->recover < t->cycle) अणु
		t->active += (t->cycle - (t->active + t->recover)) / 2;
		t->recover = t->cycle - t->active;
	पूर्ण

	/*
	 * In a few हालs quantisation may produce enough errors to
	 * leave t->cycle too low क्रम the sum of active and recovery
	 * अगर so we must correct this.
	 */
	अगर (t->active + t->recover > t->cycle)
		t->cycle = t->active + t->recover;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ata_timing_compute);
