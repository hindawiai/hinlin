<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* -*-linux-c-*-

 * venकरोr-specअगरic code क्रम SCSI CD-ROM's goes here.
 *
 * This is needed becauce most of the new features (multisession and
 * the like) are too new to be included पूर्णांकo the SCSI-II standard (to
 * be exact: there is'nt anything in my draft copy).
 *
 * Aug 1997: Ha! Got a SCSI-3 cdrom spec across my fingers. SCSI-3 करोes
 *           multisession using the READ TOC command (like SONY).
 *
 *           Rearranged stuff here: SCSI-3 is included allways, support
 *           क्रम NEC/TOSHIBA/HP commands is optional.
 *
 *   Gerd Knorr <kraxel@cs.tu-berlin.de> 
 *
 * --------------------------------------------------------------------------
 *
 * support क्रम XA/multisession-CD's
 * 
 *   - NEC:     Detection and support of multisession CD's.
 *     
 *   - TOSHIBA: Detection and support of multisession CD's.
 *              Some XA-Sector tweaking, required क्रम older drives.
 *
 *   - SONY:    Detection and support of multisession CD's.
 *              added by Thomas Quinot <thomas@cuivre.मुक्तnix.fr>
 *
 *   - PIONEER, HITACHI, PLEXTOR, MATSHITA, TEAC, PHILIPS: known to
 *              work with SONY (SCSI3 now)  code.
 *
 *   - HP:      Much like SONY, but a little dअगरferent... (Thomas)
 *              HP-Writers only ??? Maybe other CD-Writers work with this too ?
 *              HP 6020 ग_लिखोrs now supported.
 */

#समावेश <linux/cdrom.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/bcd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>

#समावेश "sr.h"

#अगर 0
#घोषणा DEBUG
#पूर्ण_अगर

/* here are some स्थिरants to sort the venकरोrs पूर्णांकo groups */

#घोषणा VENDOR_SCSI3           1	/* शेष: scsi-3 mmc */

#घोषणा VENDOR_NEC             2
#घोषणा VENDOR_TOSHIBA         3
#घोषणा VENDOR_WRITER          4	/* pre-scsi3 ग_लिखोrs */
#घोषणा VENDOR_CYGNAL_85ED     5	/* CD-on-a-chip */

#घोषणा VENDOR_TIMEOUT	30*HZ

व्योम sr_venकरोr_init(Scsi_CD *cd)
अणु
	स्थिर अक्षर *venकरोr = cd->device->venकरोr;
	स्थिर अक्षर *model = cd->device->model;
	
	/* शेष */
	cd->venकरोr = VENDOR_SCSI3;
	अगर (cd->पढ़ोcd_known)
		/* this is true क्रम scsi3/mmc drives - no more checks */
		वापस;

	अगर (cd->device->type == TYPE_WORM) अणु
		cd->venकरोr = VENDOR_WRITER;

	पूर्ण अन्यथा अगर (!म_भेदन(venकरोr, "NEC", 3)) अणु
		cd->venकरोr = VENDOR_NEC;
		अगर (!म_भेदन(model, "CD-ROM DRIVE:25", 15) ||
		    !म_भेदन(model, "CD-ROM DRIVE:36", 15) ||
		    !म_भेदन(model, "CD-ROM DRIVE:83", 15) ||
		    !म_भेदन(model, "CD-ROM DRIVE:84 ", 16)
#अगर 0
		/* my NEC 3x वापसs the पढ़ो-raw data अगर a पढ़ो-raw
		   is followed by a पढ़ो क्रम the same sector - aeb */
		    || !म_भेदन(model, "CD-ROM DRIVE:500", 16)
#पूर्ण_अगर
		    )
			/* these can't handle multisession, may hang */
			cd->cdi.mask |= CDC_MULTI_SESSION;

	पूर्ण अन्यथा अगर (!म_भेदन(venकरोr, "TOSHIBA", 7)) अणु
		cd->venकरोr = VENDOR_TOSHIBA;

	पूर्ण अन्यथा अगर (!म_भेदन(venकरोr, "Beurer", 6) &&
		   !म_भेदन(model, "Gluco Memory", 12)) अणु
		/* The Beurer GL50 evo uses a Cygnal-manufactured CD-on-a-chip
		   that only accepts a subset of SCSI commands.  Most of the
		   not-implemented commands are fine to fail, but a few,
		   particularly around the MMC or Audio commands, will put the
		   device पूर्णांकo an unrecoverable state, so they need to be
		   aव्योमed at all costs.
		*/
		cd->venकरोr = VENDOR_CYGNAL_85ED;
		cd->cdi.mask |= (
			CDC_MULTI_SESSION |
			CDC_CLOSE_TRAY | CDC_OPEN_TRAY |
			CDC_LOCK |
			CDC_GENERIC_PACKET |
			CDC_PLAY_AUDIO
			);
	पूर्ण
पूर्ण


/* small handy function क्रम चयनing block length using MODE SELECT,
 * used by sr_पढ़ो_sector() */

पूर्णांक sr_set_blocklength(Scsi_CD *cd, पूर्णांक blocklength)
अणु
	अचिन्हित अक्षर *buffer;	/* the buffer क्रम the ioctl */
	काष्ठा packet_command cgc;
	काष्ठा ccs_modesel_head *modesel;
	पूर्णांक rc, density = 0;

	अगर (cd->venकरोr == VENDOR_TOSHIBA)
		density = (blocklength > 2048) ? 0x81 : 0x83;

	buffer = kदो_स्मृति(512, GFP_KERNEL | GFP_DMA);
	अगर (!buffer)
		वापस -ENOMEM;

#अगर_घोषित DEBUG
	sr_prपूर्णांकk(KERN_INFO, cd, "MODE SELECT 0x%x/%d\n", density, blocklength);
#पूर्ण_अगर
	स_रखो(&cgc, 0, माप(काष्ठा packet_command));
	cgc.cmd[0] = MODE_SELECT;
	cgc.cmd[1] = (1 << 4);
	cgc.cmd[4] = 12;
	modesel = (काष्ठा ccs_modesel_head *) buffer;
	स_रखो(modesel, 0, माप(*modesel));
	modesel->block_desc_length = 0x08;
	modesel->density = density;
	modesel->block_length_med = (blocklength >> 8) & 0xff;
	modesel->block_length_lo = blocklength & 0xff;
	cgc.buffer = buffer;
	cgc.buflen = माप(*modesel);
	cgc.data_direction = DMA_TO_DEVICE;
	cgc.समयout = VENDOR_TIMEOUT;
	अगर (0 == (rc = sr_करो_ioctl(cd, &cgc))) अणु
		cd->device->sector_size = blocklength;
	पूर्ण
#अगर_घोषित DEBUG
	अन्यथा
		sr_prपूर्णांकk(KERN_INFO, cd,
			  "switching blocklength to %d bytes failed\n",
			  blocklength);
#पूर्ण_अगर
	kमुक्त(buffer);
	वापस rc;
पूर्ण

/* This function माला_लो called after a media change. Checks अगर the CD is
   multisession, asks क्रम offset etc. */

पूर्णांक sr_cd_check(काष्ठा cdrom_device_info *cdi)
अणु
	Scsi_CD *cd = cdi->handle;
	अचिन्हित दीर्घ sector;
	अचिन्हित अक्षर *buffer;	/* the buffer क्रम the ioctl */
	काष्ठा packet_command cgc;
	पूर्णांक rc, no_multi;

	अगर (cd->cdi.mask & CDC_MULTI_SESSION)
		वापस 0;

	buffer = kदो_स्मृति(512, GFP_KERNEL | GFP_DMA);
	अगर (!buffer)
		वापस -ENOMEM;

	sector = 0;		/* the multisession sector offset goes here  */
	no_multi = 0;		/* flag: the drive can't handle multisession */
	rc = 0;

	स_रखो(&cgc, 0, माप(काष्ठा packet_command));

	चयन (cd->venकरोr) अणु

	हाल VENDOR_SCSI3:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 12;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.समयout = VENDOR_TIMEOUT;
		rc = sr_करो_ioctl(cd, &cgc);
		अगर (rc != 0)
			अवरोध;
		अगर ((buffer[0] << 8) + buffer[1] < 0x0a) अणु
			sr_prपूर्णांकk(KERN_INFO, cd, "Hmm, seems the drive "
			   "doesn't support multisession CD's\n");
			no_multi = 1;
			अवरोध;
		पूर्ण
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		अगर (buffer[6] <= 1) अणु
			/* ignore sector offsets from first track */
			sector = 0;
		पूर्ण
		अवरोध;

	हाल VENDOR_NEC:अणु
			अचिन्हित दीर्घ min, sec, frame;
			cgc.cmd[0] = 0xde;
			cgc.cmd[1] = 0x03;
			cgc.cmd[2] = 0xb0;
			cgc.buffer = buffer;
			cgc.buflen = 0x16;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.समयout = VENDOR_TIMEOUT;
			rc = sr_करो_ioctl(cd, &cgc);
			अगर (rc != 0)
				अवरोध;
			अगर (buffer[14] != 0 && buffer[14] != 0xb0) अणु
				sr_prपूर्णांकk(KERN_INFO, cd, "Hmm, seems the cdrom "
					  "doesn't support multisession CD's\n");

				no_multi = 1;
				अवरोध;
			पूर्ण
			min = bcd2bin(buffer[15]);
			sec = bcd2bin(buffer[16]);
			frame = bcd2bin(buffer[17]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			अवरोध;
		पूर्ण

	हाल VENDOR_TOSHIBA:अणु
			अचिन्हित दीर्घ min, sec, frame;

			/* we request some disc inक्रमmation (is it a XA-CD ?,
			 * where starts the last session ?) */
			cgc.cmd[0] = 0xc7;
			cgc.cmd[1] = 0x03;
			cgc.buffer = buffer;
			cgc.buflen = 4;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.समयout = VENDOR_TIMEOUT;
			rc = sr_करो_ioctl(cd, &cgc);
			अगर (rc == -EINVAL) अणु
				sr_prपूर्णांकk(KERN_INFO, cd, "Hmm, seems the drive "
					  "doesn't support multisession CD's\n");
				no_multi = 1;
				अवरोध;
			पूर्ण
			अगर (rc != 0)
				अवरोध;
			min = bcd2bin(buffer[1]);
			sec = bcd2bin(buffer[2]);
			frame = bcd2bin(buffer[3]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			अगर (sector)
				sector -= CD_MSF_OFFSET;
			sr_set_blocklength(cd, 2048);
			अवरोध;
		पूर्ण

	हाल VENDOR_WRITER:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 0x04;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 0x04;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.समयout = VENDOR_TIMEOUT;
		rc = sr_करो_ioctl(cd, &cgc);
		अगर (rc != 0) अणु
			अवरोध;
		पूर्ण
		अगर ((rc = buffer[2]) == 0) अणु
			sr_prपूर्णांकk(KERN_WARNING, cd,
				  "No finished session\n");
			अवरोध;
		पूर्ण
		cgc.cmd[0] = READ_TOC;	/* Read TOC */
		cgc.cmd[6] = rc & 0x7f;	/* number of last session */
		cgc.cmd[8] = 0x0c;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.समयout = VENDOR_TIMEOUT;
		rc = sr_करो_ioctl(cd, &cgc);
		अगर (rc != 0) अणु
			अवरोध;
		पूर्ण
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		अवरोध;

	शेष:
		/* should not happen */
		sr_prपूर्णांकk(KERN_WARNING, cd,
			  "unknown vendor code (%i), not initialized ?\n",
			  cd->venकरोr);
		sector = 0;
		no_multi = 1;
		अवरोध;
	पूर्ण
	cd->ms_offset = sector;
	cd->xa_flag = 0;
	अगर (CDS_AUDIO != sr_disk_status(cdi) && 1 == sr_is_xa(cd))
		cd->xa_flag = 1;

	अगर (2048 != cd->device->sector_size) अणु
		sr_set_blocklength(cd, 2048);
	पूर्ण
	अगर (no_multi)
		cdi->mask |= CDC_MULTI_SESSION;

#अगर_घोषित DEBUG
	अगर (sector)
		sr_prपूर्णांकk(KERN_DEBUG, cd, "multisession offset=%lu\n",
			  sector);
#पूर्ण_अगर
	kमुक्त(buffer);
	वापस rc;
पूर्ण
