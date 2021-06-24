<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *  Copyright (c) 2007-2008 Bartlomiej Zolnierkiewicz
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>
#समावेश <linux/module.h>

/*
 * PIO 0-5, MWDMA 0-2 and UDMA 0-6 timings (in nanoseconds).
 * These were taken from ATA/ATAPI-6 standard, rev 0a, except
 * क्रम PIO 5, which is a nonstandard extension and UDMA6, which
 * is currently supported only by Maxtor drives.
 */

अटल काष्ठा ide_timing ide_timing[] = अणु

	अणु XFER_UDMA_6,     0,   0,   0,   0,   0,   0,   0,  15 पूर्ण,
	अणु XFER_UDMA_5,     0,   0,   0,   0,   0,   0,   0,  20 पूर्ण,
	अणु XFER_UDMA_4,     0,   0,   0,   0,   0,   0,   0,  30 पूर्ण,
	अणु XFER_UDMA_3,     0,   0,   0,   0,   0,   0,   0,  45 पूर्ण,

	अणु XFER_UDMA_2,     0,   0,   0,   0,   0,   0,   0,  60 पूर्ण,
	अणु XFER_UDMA_1,     0,   0,   0,   0,   0,   0,   0,  80 पूर्ण,
	अणु XFER_UDMA_0,     0,   0,   0,   0,   0,   0,   0, 120 पूर्ण,

	अणु XFER_MW_DMA_4,  25,   0,   0,   0,  55,  20,  80,   0 पूर्ण,
	अणु XFER_MW_DMA_3,  25,   0,   0,   0,  65,  25, 100,   0 पूर्ण,
	अणु XFER_MW_DMA_2,  25,   0,   0,   0,  70,  25, 120,   0 पूर्ण,
	अणु XFER_MW_DMA_1,  45,   0,   0,   0,  80,  50, 150,   0 पूर्ण,
	अणु XFER_MW_DMA_0,  60,   0,   0,   0, 215, 215, 480,   0 पूर्ण,

	अणु XFER_SW_DMA_2,  60,   0,   0,   0, 120, 120, 240,   0 पूर्ण,
	अणु XFER_SW_DMA_1,  90,   0,   0,   0, 240, 240, 480,   0 पूर्ण,
	अणु XFER_SW_DMA_0, 120,   0,   0,   0, 480, 480, 960,   0 पूर्ण,

	अणु XFER_PIO_6,     10,  55,  20,  80,  55,  20,  80,   0 पूर्ण,
	अणु XFER_PIO_5,     15,  65,  25, 100,  65,  25, 100,   0 पूर्ण,
	अणु XFER_PIO_4,     25,  70,  25, 120,  70,  25, 120,   0 पूर्ण,
	अणु XFER_PIO_3,     30,  80,  70, 180,  80,  70, 180,   0 पूर्ण,

	अणु XFER_PIO_2,     30, 290,  40, 330, 100,  90, 240,   0 पूर्ण,
	अणु XFER_PIO_1,     50, 290,  93, 383, 125, 100, 383,   0 पूर्ण,
	अणु XFER_PIO_0,     70, 290, 240, 600, 165, 150, 600,   0 पूर्ण,

	अणु XFER_PIO_SLOW, 120, 290, 240, 960, 290, 240, 960,   0 पूर्ण,

	अणु 0xff पूर्ण
पूर्ण;

काष्ठा ide_timing *ide_timing_find_mode(u8 speed)
अणु
	काष्ठा ide_timing *t;

	क्रम (t = ide_timing; t->mode != speed; t++)
		अगर (t->mode == 0xff)
			वापस शून्य;
	वापस t;
पूर्ण
EXPORT_SYMBOL_GPL(ide_timing_find_mode);

u16 ide_pio_cycle_समय(ide_drive_t *drive, u8 pio)
अणु
	u16 *id = drive->id;
	काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);
	u16 cycle = 0;

	अगर (id[ATA_ID_FIELD_VALID] & 2) अणु
		अगर (ata_id_has_iordy(drive->id))
			cycle = id[ATA_ID_EIDE_PIO_IORDY];
		अन्यथा
			cycle = id[ATA_ID_EIDE_PIO];

		/* conservative "downgrade" क्रम all pre-ATA2 drives */
		अगर (pio < 3 && cycle < t->cycle)
			cycle = 0; /* use standard timing */

		/* Use the standard timing क्रम the CF specअगरic modes too */
		अगर (pio > 4 && ata_id_is_cfa(id))
			cycle = 0;
	पूर्ण

	वापस cycle ? cycle : t->cycle;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pio_cycle_समय);

#घोषणा ENOUGH(v, unit)		(((v) - 1) / (unit) + 1)
#घोषणा EZ(v, unit)		((v) ? ENOUGH((v) * 1000, unit) : 0)

अटल व्योम ide_timing_quantize(काष्ठा ide_timing *t, काष्ठा ide_timing *q,
				पूर्णांक T, पूर्णांक UT)
अणु
	q->setup   = EZ(t->setup,   T);
	q->act8b   = EZ(t->act8b,   T);
	q->rec8b   = EZ(t->rec8b,   T);
	q->cyc8b   = EZ(t->cyc8b,   T);
	q->active  = EZ(t->active,  T);
	q->recover = EZ(t->recover, T);
	q->cycle   = EZ(t->cycle,   T);
	q->udma    = EZ(t->udma,    UT);
पूर्ण

व्योम ide_timing_merge(काष्ठा ide_timing *a, काष्ठा ide_timing *b,
		      काष्ठा ide_timing *m, अचिन्हित पूर्णांक what)
अणु
	अगर (what & IDE_TIMING_SETUP)
		m->setup   = max(a->setup,   b->setup);
	अगर (what & IDE_TIMING_ACT8B)
		m->act8b   = max(a->act8b,   b->act8b);
	अगर (what & IDE_TIMING_REC8B)
		m->rec8b   = max(a->rec8b,   b->rec8b);
	अगर (what & IDE_TIMING_CYC8B)
		m->cyc8b   = max(a->cyc8b,   b->cyc8b);
	अगर (what & IDE_TIMING_ACTIVE)
		m->active  = max(a->active,  b->active);
	अगर (what & IDE_TIMING_RECOVER)
		m->recover = max(a->recover, b->recover);
	अगर (what & IDE_TIMING_CYCLE)
		m->cycle   = max(a->cycle,   b->cycle);
	अगर (what & IDE_TIMING_UDMA)
		m->udma    = max(a->udma,    b->udma);
पूर्ण
EXPORT_SYMBOL_GPL(ide_timing_merge);

पूर्णांक ide_timing_compute(ide_drive_t *drive, u8 speed,
		       काष्ठा ide_timing *t, पूर्णांक T, पूर्णांक UT)
अणु
	u16 *id = drive->id;
	काष्ठा ide_timing *s, p;

	/*
	 * Find the mode.
	 */
	s = ide_timing_find_mode(speed);
	अगर (s == शून्य)
		वापस -EINVAL;

	/*
	 * Copy the timing from the table.
	 */
	*t = *s;

	/*
	 * If the drive is an EIDE drive, it can tell us it needs extended
	 * PIO/MWDMA cycle timing.
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

		ide_timing_merge(&p, t, t, IDE_TIMING_CYCLE | IDE_TIMING_CYC8B);
	पूर्ण

	/*
	 * Convert the timing to bus घड़ी counts.
	 */
	ide_timing_quantize(t, t, T, UT);

	/*
	 * Even in DMA/UDMA modes we still use PIO access क्रम IDENTIFY,
	 * S.M.A.R.T and some other commands. We have to ensure that the
	 * DMA cycle timing is slower/equal than the current PIO timing.
	 */
	अगर (speed >= XFER_SW_DMA_0) अणु
		ide_timing_compute(drive, drive->pio_mode, &p, T, UT);
		ide_timing_merge(&p, t, t, IDE_TIMING_ALL);
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

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_timing_compute);
