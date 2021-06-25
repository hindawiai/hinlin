<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2009
 * EMC Symmetrix ioctl Copyright EMC Corporation, 2008
 * Author.........: Nigel Hislop <hislop_nigel@emc.com>
 */

#घोषणा KMSG_COMPONENT "dasd-eckd"

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>	/* HDIO_GETGEO			    */
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/compat.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/css_अक्षरs.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/itcw.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/chpid.h>

#समावेश "dasd_int.h"
#समावेश "dasd_eckd.h"

#अगर_घोषित PRINTK_HEADER
#अघोषित PRINTK_HEADER
#पूर्ण_अगर				/* PRINTK_HEADER */
#घोषणा PRINTK_HEADER "dasd(eckd):"

/*
 * raw track access always map to 64k in memory
 * so it maps to 16 blocks of 4k per track
 */
#घोषणा DASD_RAW_BLOCK_PER_TRACK 16
#घोषणा DASD_RAW_BLOCKSIZE 4096
/* 64k are 128 x 512 byte sectors  */
#घोषणा DASD_RAW_SECTORS_PER_TRACK 128

MODULE_LICENSE("GPL");

अटल काष्ठा dasd_discipline dasd_eckd_discipline;

/* The ccw bus type uses this table to find devices that it sends to
 * dasd_eckd_probe */
अटल काष्ठा ccw_device_id dasd_eckd_ids[] = अणु
	अणु CCW_DEVICE_DEVTYPE (0x3990, 0, 0x3390, 0), .driver_info = 0x1पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x2105, 0, 0x3390, 0), .driver_info = 0x2पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x3880, 0, 0x3380, 0), .driver_info = 0x3पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x3990, 0, 0x3380, 0), .driver_info = 0x4पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x2105, 0, 0x3380, 0), .driver_info = 0x5पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x9343, 0, 0x9345, 0), .driver_info = 0x6पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x2107, 0, 0x3390, 0), .driver_info = 0x7पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x2107, 0, 0x3380, 0), .driver_info = 0x8पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x1750, 0, 0x3390, 0), .driver_info = 0x9पूर्ण,
	अणु CCW_DEVICE_DEVTYPE (0x1750, 0, 0x3380, 0), .driver_info = 0xaपूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(ccw, dasd_eckd_ids);

अटल काष्ठा ccw_driver dasd_eckd_driver; /* see below */

अटल व्योम *rawpadpage;

#घोषणा INIT_CQR_OK 0
#घोषणा INIT_CQR_UNFORMATTED 1
#घोषणा INIT_CQR_ERROR 2

/* emergency request क्रम reserve/release */
अटल काष्ठा अणु
	काष्ठा dasd_ccw_req cqr;
	काष्ठा ccw1 ccw;
	अक्षर data[32];
पूर्ण *dasd_reserve_req;
अटल DEFINE_MUTEX(dasd_reserve_mutex);

अटल काष्ठा अणु
	काष्ठा dasd_ccw_req cqr;
	काष्ठा ccw1 ccw[2];
	अक्षर data[40];
पूर्ण *dasd_vol_info_req;
अटल DEFINE_MUTEX(dasd_vol_info_mutex);

काष्ठा ext_pool_exhaust_work_data अणु
	काष्ठा work_काष्ठा worker;
	काष्ठा dasd_device *device;
	काष्ठा dasd_device *base;
पूर्ण;

/* definitions क्रम the path verअगरication worker */
काष्ठा pe_handler_work_data अणु
	काष्ठा work_काष्ठा worker;
	काष्ठा dasd_device *device;
	काष्ठा dasd_ccw_req cqr;
	काष्ठा ccw1 ccw;
	__u8 rcd_buffer[DASD_ECKD_RCD_DATA_SIZE];
	पूर्णांक isglobal;
	__u8 tbvpm;
	__u8 fcsecpm;
पूर्ण;
अटल काष्ठा pe_handler_work_data *pe_handler_worker;
अटल DEFINE_MUTEX(dasd_pe_handler_mutex);

काष्ठा check_attention_work_data अणु
	काष्ठा work_काष्ठा worker;
	काष्ठा dasd_device *device;
	__u8 lpum;
पूर्ण;

अटल पूर्णांक dasd_eckd_ext_pool_id(काष्ठा dasd_device *);
अटल पूर्णांक prepare_itcw(काष्ठा itcw *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, पूर्णांक,
			काष्ठा dasd_device *, काष्ठा dasd_device *,
			अचिन्हित पूर्णांक, पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
			अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

/* initial attempt at a probe function. this can be simplअगरied once
 * the other detection code is gone */
अटल पूर्णांक
dasd_eckd_probe (काष्ठा ccw_device *cdev)
अणु
	पूर्णांक ret;

	/* set ECKD specअगरic ccw-device options */
	ret = ccw_device_set_options(cdev, CCWDEV_ALLOW_FORCE |
				     CCWDEV_DO_PATHGROUP | CCWDEV_DO_MULTIPATH);
	अगर (ret) अणु
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s",
				"dasd_eckd_probe: could not set "
				"ccw-device options");
		वापस ret;
	पूर्ण
	ret = dasd_generic_probe(cdev);
	वापस ret;
पूर्ण

अटल पूर्णांक
dasd_eckd_set_online(काष्ठा ccw_device *cdev)
अणु
	वापस dasd_generic_set_online(cdev, &dasd_eckd_discipline);
पूर्ण

अटल स्थिर पूर्णांक sizes_trk0[] = अणु 28, 148, 84 पूर्ण;
#घोषणा LABEL_SIZE 140

/* head and record addresses of count_area पढ़ो in analysis ccw */
अटल स्थिर पूर्णांक count_area_head[] = अणु 0, 0, 0, 0, 1 पूर्ण;
अटल स्थिर पूर्णांक count_area_rec[] = अणु 1, 2, 3, 4, 1 पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
उच्चमान_quot(अचिन्हित पूर्णांक d1, अचिन्हित पूर्णांक d2)
अणु
	वापस (d1 + (d2 - 1)) / d2;
पूर्ण

अटल अचिन्हित पूर्णांक
recs_per_track(काष्ठा dasd_eckd_अक्षरacteristics * rdc,
	       अचिन्हित पूर्णांक kl, अचिन्हित पूर्णांक dl)
अणु
	पूर्णांक dn, kn;

	चयन (rdc->dev_type) अणु
	हाल 0x3380:
		अगर (kl)
			वापस 1499 / (15 + 7 + उच्चमान_quot(kl + 12, 32) +
				       उच्चमान_quot(dl + 12, 32));
		अन्यथा
			वापस 1499 / (15 + उच्चमान_quot(dl + 12, 32));
	हाल 0x3390:
		dn = उच्चमान_quot(dl + 6, 232) + 1;
		अगर (kl) अणु
			kn = उच्चमान_quot(kl + 6, 232) + 1;
			वापस 1729 / (10 + 9 + उच्चमान_quot(kl + 6 * kn, 34) +
				       9 + उच्चमान_quot(dl + 6 * dn, 34));
		पूर्ण अन्यथा
			वापस 1729 / (10 + 9 + उच्चमान_quot(dl + 6 * dn, 34));
	हाल 0x9345:
		dn = उच्चमान_quot(dl + 6, 232) + 1;
		अगर (kl) अणु
			kn = उच्चमान_quot(kl + 6, 232) + 1;
			वापस 1420 / (18 + 7 + उच्चमान_quot(kl + 6 * kn, 34) +
				       उच्चमान_quot(dl + 6 * dn, 34));
		पूर्ण अन्यथा
			वापस 1420 / (18 + 7 + उच्चमान_quot(dl + 6 * dn, 34));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम set_ch_t(काष्ठा ch_t *geo, __u32 cyl, __u8 head)
अणु
	geo->cyl = (__u16) cyl;
	geo->head = cyl >> 16;
	geo->head <<= 4;
	geo->head |= head;
पूर्ण

/*
 * calculate failing track from sense data depending अगर
 * it is an EAV device or not
 */
अटल पूर्णांक dasd_eckd_track_from_irb(काष्ठा irb *irb, काष्ठा dasd_device *device,
				    sector_t *track)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	u8 *sense = शून्य;
	u32 cyl;
	u8 head;

	sense = dasd_get_sense(irb);
	अगर (!sense) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "ESE error no sense data\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!(sense[27] & DASD_SENSE_BIT_2)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "ESE error no valid track data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sense[27] & DASD_SENSE_BIT_3) अणु
		/* enhanced addressing */
		cyl = sense[30] << 20;
		cyl |= (sense[31] & 0xF0) << 12;
		cyl |= sense[28] << 8;
		cyl |= sense[29];
	पूर्ण अन्यथा अणु
		cyl = sense[29] << 8;
		cyl |= sense[30];
	पूर्ण
	head = sense[31] & 0x0F;
	*track = cyl * निजी->rdc_data.trk_per_cyl + head;
	वापस 0;
पूर्ण

अटल पूर्णांक set_बारtamp(काष्ठा ccw1 *ccw, काष्ठा DE_eckd_data *data,
		     काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक rc;

	rc = get_phys_घड़ी(&data->ep_sys_समय);
	/*
	 * Ignore वापस code अगर XRC is not supported or
	 * sync घड़ी is चयनed off
	 */
	अगर ((rc && !निजी->rdc_data.facilities.XRC_supported) ||
	    rc == -EOPNOTSUPP || rc == -EACCES)
		वापस 0;

	/* चयन on System Time Stamp - needed क्रम XRC Support */
	data->ga_extended |= 0x08; /* चयन on 'Time Stamp Valid'   */
	data->ga_extended |= 0x02; /* चयन on 'Extended Parameter' */

	अगर (ccw) अणु
		ccw->count = माप(काष्ठा DE_eckd_data);
		ccw->flags |= CCW_FLAG_SLI;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
define_extent(काष्ठा ccw1 *ccw, काष्ठा DE_eckd_data *data, अचिन्हित पूर्णांक trk,
	      अचिन्हित पूर्णांक totrk, पूर्णांक cmd, काष्ठा dasd_device *device,
	      पूर्णांक blksize)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	u16 heads, beghead, endhead;
	u32 begcyl, endcyl;
	पूर्णांक rc = 0;

	अगर (ccw) अणु
		ccw->cmd_code = DASD_ECKD_CCW_DEFINE_EXTENT;
		ccw->flags = 0;
		ccw->count = 16;
		ccw->cda = (__u32)__pa(data);
	पूर्ण

	स_रखो(data, 0, माप(काष्ठा DE_eckd_data));
	चयन (cmd) अणु
	हाल DASD_ECKD_CCW_READ_HOME_ADDRESS:
	हाल DASD_ECKD_CCW_READ_RECORD_ZERO:
	हाल DASD_ECKD_CCW_READ:
	हाल DASD_ECKD_CCW_READ_MT:
	हाल DASD_ECKD_CCW_READ_CKD:
	हाल DASD_ECKD_CCW_READ_CKD_MT:
	हाल DASD_ECKD_CCW_READ_KD:
	हाल DASD_ECKD_CCW_READ_KD_MT:
		data->mask.perm = 0x1;
		data->attributes.operation = निजी->attrib.operation;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_COUNT:
		data->mask.perm = 0x1;
		data->attributes.operation = DASD_BYPASS_CACHE;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_TRACK:
	हाल DASD_ECKD_CCW_READ_TRACK_DATA:
		data->mask.perm = 0x1;
		data->attributes.operation = निजी->attrib.operation;
		data->blk_size = 0;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE:
	हाल DASD_ECKD_CCW_WRITE_MT:
	हाल DASD_ECKD_CCW_WRITE_KD:
	हाल DASD_ECKD_CCW_WRITE_KD_MT:
		data->mask.perm = 0x02;
		data->attributes.operation = निजी->attrib.operation;
		rc = set_बारtamp(ccw, data, device);
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_CKD:
	हाल DASD_ECKD_CCW_WRITE_CKD_MT:
		data->attributes.operation = DASD_BYPASS_CACHE;
		rc = set_बारtamp(ccw, data, device);
		अवरोध;
	हाल DASD_ECKD_CCW_ERASE:
	हाल DASD_ECKD_CCW_WRITE_HOME_ADDRESS:
	हाल DASD_ECKD_CCW_WRITE_RECORD_ZERO:
		data->mask.perm = 0x3;
		data->mask.auth = 0x1;
		data->attributes.operation = DASD_BYPASS_CACHE;
		rc = set_बारtamp(ccw, data, device);
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_FULL_TRACK:
		data->mask.perm = 0x03;
		data->attributes.operation = निजी->attrib.operation;
		data->blk_size = 0;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_TRACK_DATA:
		data->mask.perm = 0x02;
		data->attributes.operation = निजी->attrib.operation;
		data->blk_size = blksize;
		rc = set_बारtamp(ccw, data, device);
		अवरोध;
	शेष:
		dev_err(&device->cdev->dev,
			"0x%x is not a known command\n", cmd);
		अवरोध;
	पूर्ण

	data->attributes.mode = 0x3;	/* ECKD */

	अगर ((निजी->rdc_data.cu_type == 0x2105 ||
	     निजी->rdc_data.cu_type == 0x2107 ||
	     निजी->rdc_data.cu_type == 0x1750)
	    && !(निजी->uses_cdl && trk < 2))
		data->ga_extended |= 0x40; /* Regular Data Format Mode */

	heads = निजी->rdc_data.trk_per_cyl;
	begcyl = trk / heads;
	beghead = trk % heads;
	endcyl = totrk / heads;
	endhead = totrk % heads;

	/* check क्रम sequential prestage - enhance cylinder range */
	अगर (data->attributes.operation == DASD_SEQ_PRESTAGE ||
	    data->attributes.operation == DASD_SEQ_ACCESS) अणु

		अगर (endcyl + निजी->attrib.nr_cyl < निजी->real_cyl)
			endcyl += निजी->attrib.nr_cyl;
		अन्यथा
			endcyl = (निजी->real_cyl - 1);
	पूर्ण

	set_ch_t(&data->beg_ext, begcyl, beghead);
	set_ch_t(&data->end_ext, endcyl, endhead);
	वापस rc;
पूर्ण


अटल व्योम locate_record_ext(काष्ठा ccw1 *ccw, काष्ठा LRE_eckd_data *data,
			      अचिन्हित पूर्णांक trk, अचिन्हित पूर्णांक rec_on_trk,
			      पूर्णांक count, पूर्णांक cmd, काष्ठा dasd_device *device,
			      अचिन्हित पूर्णांक reclen, अचिन्हित पूर्णांक tlf)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक sector;
	पूर्णांक dn, d;

	अगर (ccw) अणु
		ccw->cmd_code = DASD_ECKD_CCW_LOCATE_RECORD_EXT;
		ccw->flags = 0;
		अगर (cmd == DASD_ECKD_CCW_WRITE_FULL_TRACK)
			ccw->count = 22;
		अन्यथा
			ccw->count = 20;
		ccw->cda = (__u32)__pa(data);
	पूर्ण

	स_रखो(data, 0, माप(*data));
	sector = 0;
	अगर (rec_on_trk) अणु
		चयन (निजी->rdc_data.dev_type) अणु
		हाल 0x3390:
			dn = उच्चमान_quot(reclen + 6, 232);
			d = 9 + उच्चमान_quot(reclen + 6 * (dn + 1), 34);
			sector = (49 + (rec_on_trk - 1) * (10 + d)) / 8;
			अवरोध;
		हाल 0x3380:
			d = 7 + उच्चमान_quot(reclen + 12, 32);
			sector = (39 + (rec_on_trk - 1) * (8 + d)) / 7;
			अवरोध;
		पूर्ण
	पूर्ण
	data->sector = sector;
	/* note: meaning of count depends on the operation
	 *	 क्रम record based I/O it's the number of records, but क्रम
	 *	 track based I/O it's the number of tracks
	 */
	data->count = count;
	चयन (cmd) अणु
	हाल DASD_ECKD_CCW_WRITE_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x03;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_RECORD_ZERO:
		data->operation.orientation = 0x1;
		data->operation.operation = 0x03;
		data->count++;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_RECORD_ZERO:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		data->count++;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE:
	हाल DASD_ECKD_CCW_WRITE_MT:
	हाल DASD_ECKD_CCW_WRITE_KD:
	हाल DASD_ECKD_CCW_WRITE_KD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x01;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_CKD:
	हाल DASD_ECKD_CCW_WRITE_CKD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x03;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_FULL_TRACK:
		data->operation.orientation = 0x0;
		data->operation.operation = 0x3F;
		data->extended_operation = 0x11;
		data->length = 0;
		data->extended_parameter_length = 0x02;
		अगर (data->count > 8) अणु
			data->extended_parameter[0] = 0xFF;
			data->extended_parameter[1] = 0xFF;
			data->extended_parameter[1] <<= (16 - count);
		पूर्ण अन्यथा अणु
			data->extended_parameter[0] = 0xFF;
			data->extended_parameter[0] <<= (8 - count);
			data->extended_parameter[1] = 0x00;
		पूर्ण
		data->sector = 0xFF;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_TRACK_DATA:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;	/* not tlf, as one might think */
		data->operation.operation = 0x3F;
		data->extended_operation = 0x23;
		अवरोध;
	हाल DASD_ECKD_CCW_READ:
	हाल DASD_ECKD_CCW_READ_MT:
	हाल DASD_ECKD_CCW_READ_KD:
	हाल DASD_ECKD_CCW_READ_KD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x06;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_CKD:
	हाल DASD_ECKD_CCW_READ_CKD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x16;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_COUNT:
		data->operation.operation = 0x06;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_TRACK:
		data->operation.orientation = 0x1;
		data->operation.operation = 0x0C;
		data->extended_parameter_length = 0;
		data->sector = 0xFF;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_TRACK_DATA:
		data->auxiliary.length_valid = 0x1;
		data->length = tlf;
		data->operation.operation = 0x0C;
		अवरोध;
	हाल DASD_ECKD_CCW_ERASE:
		data->length = reclen;
		data->auxiliary.length_valid = 0x1;
		data->operation.operation = 0x0b;
		अवरोध;
	शेष:
		DBF_DEV_EVENT(DBF_ERR, device,
			    "fill LRE unknown opcode 0x%x", cmd);
		BUG();
	पूर्ण
	set_ch_t(&data->seek_addr,
		 trk / निजी->rdc_data.trk_per_cyl,
		 trk % निजी->rdc_data.trk_per_cyl);
	data->search_arg.cyl = data->seek_addr.cyl;
	data->search_arg.head = data->seek_addr.head;
	data->search_arg.record = rec_on_trk;
पूर्ण

अटल पूर्णांक prefix_LRE(काष्ठा ccw1 *ccw, काष्ठा PFX_eckd_data *pfxdata,
		      अचिन्हित पूर्णांक trk, अचिन्हित पूर्णांक totrk, पूर्णांक cmd,
		      काष्ठा dasd_device *basedev, काष्ठा dasd_device *startdev,
		      अचिन्हित पूर्णांक क्रमmat, अचिन्हित पूर्णांक rec_on_trk, पूर्णांक count,
		      अचिन्हित पूर्णांक blksize, अचिन्हित पूर्णांक tlf)
अणु
	काष्ठा dasd_eckd_निजी *basepriv, *startpriv;
	काष्ठा LRE_eckd_data *lredata;
	काष्ठा DE_eckd_data *dedata;
	पूर्णांक rc = 0;

	basepriv = basedev->निजी;
	startpriv = startdev->निजी;
	dedata = &pfxdata->define_extent;
	lredata = &pfxdata->locate_record;

	ccw->cmd_code = DASD_ECKD_CCW_PFX;
	ccw->flags = 0;
	अगर (cmd == DASD_ECKD_CCW_WRITE_FULL_TRACK) अणु
		ccw->count = माप(*pfxdata) + 2;
		ccw->cda = (__u32) __pa(pfxdata);
		स_रखो(pfxdata, 0, माप(*pfxdata) + 2);
	पूर्ण अन्यथा अणु
		ccw->count = माप(*pfxdata);
		ccw->cda = (__u32) __pa(pfxdata);
		स_रखो(pfxdata, 0, माप(*pfxdata));
	पूर्ण

	/* prefix data */
	अगर (क्रमmat > 1) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "PFX LRE unknown format 0x%x", क्रमmat);
		BUG();
		वापस -EINVAL;
	पूर्ण
	pfxdata->क्रमmat = क्रमmat;
	pfxdata->base_address = basepriv->ned->unit_addr;
	pfxdata->base_lss = basepriv->ned->ID;
	pfxdata->validity.define_extent = 1;

	/* निजी uid is kept up to date, conf_data may be outdated */
	अगर (startpriv->uid.type == UA_BASE_PAV_ALIAS)
		pfxdata->validity.verअगरy_base = 1;

	अगर (startpriv->uid.type == UA_HYPER_PAV_ALIAS) अणु
		pfxdata->validity.verअगरy_base = 1;
		pfxdata->validity.hyper_pav = 1;
	पूर्ण

	rc = define_extent(शून्य, dedata, trk, totrk, cmd, basedev, blksize);

	/*
	 * For some commands the System Time Stamp is set in the define extent
	 * data when XRC is supported. The validity of the समय stamp must be
	 * reflected in the prefix data as well.
	 */
	अगर (dedata->ga_extended & 0x08 && dedata->ga_extended & 0x02)
		pfxdata->validity.समय_stamp = 1; /* 'Time Stamp Valid'   */

	अगर (क्रमmat == 1) अणु
		locate_record_ext(शून्य, lredata, trk, rec_on_trk, count, cmd,
				  basedev, blksize, tlf);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक prefix(काष्ठा ccw1 *ccw, काष्ठा PFX_eckd_data *pfxdata,
		  अचिन्हित पूर्णांक trk, अचिन्हित पूर्णांक totrk, पूर्णांक cmd,
		  काष्ठा dasd_device *basedev, काष्ठा dasd_device *startdev)
अणु
	वापस prefix_LRE(ccw, pfxdata, trk, totrk, cmd, basedev, startdev,
			  0, 0, 0, 0, 0);
पूर्ण

अटल व्योम
locate_record(काष्ठा ccw1 *ccw, काष्ठा LO_eckd_data *data, अचिन्हित पूर्णांक trk,
	      अचिन्हित पूर्णांक rec_on_trk, पूर्णांक no_rec, पूर्णांक cmd,
	      काष्ठा dasd_device * device, पूर्णांक reclen)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक sector;
	पूर्णांक dn, d;

	DBF_DEV_EVENT(DBF_INFO, device,
		  "Locate: trk %d, rec %d, no_rec %d, cmd %d, reclen %d",
		  trk, rec_on_trk, no_rec, cmd, reclen);

	ccw->cmd_code = DASD_ECKD_CCW_LOCATE_RECORD;
	ccw->flags = 0;
	ccw->count = 16;
	ccw->cda = (__u32) __pa(data);

	स_रखो(data, 0, माप(काष्ठा LO_eckd_data));
	sector = 0;
	अगर (rec_on_trk) अणु
		चयन (निजी->rdc_data.dev_type) अणु
		हाल 0x3390:
			dn = उच्चमान_quot(reclen + 6, 232);
			d = 9 + उच्चमान_quot(reclen + 6 * (dn + 1), 34);
			sector = (49 + (rec_on_trk - 1) * (10 + d)) / 8;
			अवरोध;
		हाल 0x3380:
			d = 7 + उच्चमान_quot(reclen + 12, 32);
			sector = (39 + (rec_on_trk - 1) * (8 + d)) / 7;
			अवरोध;
		पूर्ण
	पूर्ण
	data->sector = sector;
	data->count = no_rec;
	चयन (cmd) अणु
	हाल DASD_ECKD_CCW_WRITE_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x03;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_RECORD_ZERO:
		data->operation.orientation = 0x1;
		data->operation.operation = 0x03;
		data->count++;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_RECORD_ZERO:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		data->count++;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE:
	हाल DASD_ECKD_CCW_WRITE_MT:
	हाल DASD_ECKD_CCW_WRITE_KD:
	हाल DASD_ECKD_CCW_WRITE_KD_MT:
		data->auxiliary.last_bytes_used = 0x1;
		data->length = reclen;
		data->operation.operation = 0x01;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_CKD:
	हाल DASD_ECKD_CCW_WRITE_CKD_MT:
		data->auxiliary.last_bytes_used = 0x1;
		data->length = reclen;
		data->operation.operation = 0x03;
		अवरोध;
	हाल DASD_ECKD_CCW_READ:
	हाल DASD_ECKD_CCW_READ_MT:
	हाल DASD_ECKD_CCW_READ_KD:
	हाल DASD_ECKD_CCW_READ_KD_MT:
		data->auxiliary.last_bytes_used = 0x1;
		data->length = reclen;
		data->operation.operation = 0x06;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_CKD:
	हाल DASD_ECKD_CCW_READ_CKD_MT:
		data->auxiliary.last_bytes_used = 0x1;
		data->length = reclen;
		data->operation.operation = 0x16;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_COUNT:
		data->operation.operation = 0x06;
		अवरोध;
	हाल DASD_ECKD_CCW_ERASE:
		data->length = reclen;
		data->auxiliary.last_bytes_used = 0x1;
		data->operation.operation = 0x0b;
		अवरोध;
	शेष:
		DBF_DEV_EVENT(DBF_ERR, device, "unknown locate record "
			      "opcode 0x%x", cmd);
	पूर्ण
	set_ch_t(&data->seek_addr,
		 trk / निजी->rdc_data.trk_per_cyl,
		 trk % निजी->rdc_data.trk_per_cyl);
	data->search_arg.cyl = data->seek_addr.cyl;
	data->search_arg.head = data->seek_addr.head;
	data->search_arg.record = rec_on_trk;
पूर्ण

/*
 * Returns 1 अगर the block is one of the special blocks that needs
 * to get पढ़ो/written with the KD variant of the command.
 * That is DASD_ECKD_READ_KD_MT instead of DASD_ECKD_READ_MT and
 * DASD_ECKD_WRITE_KD_MT instead of DASD_ECKD_WRITE_MT.
 * Luckily the KD variants dअगरfer only by one bit (0x08) from the
 * normal variant. So करोn't wonder about code like:
 * अगर (dasd_eckd_cdl_special(blk_per_trk, recid))
 *         ccw->cmd_code |= 0x8;
 */
अटल अंतरभूत पूर्णांक
dasd_eckd_cdl_special(पूर्णांक blk_per_trk, पूर्णांक recid)
अणु
	अगर (recid < 3)
		वापस 1;
	अगर (recid < blk_per_trk)
		वापस 0;
	अगर (recid < 2 * blk_per_trk)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Returns the record size क्रम the special blocks of the cdl क्रमmat.
 * Only वापसs something useful अगर dasd_eckd_cdl_special is true
 * क्रम the recid.
 */
अटल अंतरभूत पूर्णांक
dasd_eckd_cdl_reclen(पूर्णांक recid)
अणु
	अगर (recid < 3)
		वापस sizes_trk0[recid];
	वापस LABEL_SIZE;
पूर्ण
/* create unique id from निजी काष्ठाure. */
अटल व्योम create_uid(काष्ठा dasd_eckd_निजी *निजी)
अणु
	पूर्णांक count;
	काष्ठा dasd_uid *uid;

	uid = &निजी->uid;
	स_रखो(uid, 0, माप(काष्ठा dasd_uid));
	स_नकल(uid->venकरोr, निजी->ned->HDA_manufacturer,
	       माप(uid->venकरोr) - 1);
	EBCASC(uid->venकरोr, माप(uid->venकरोr) - 1);
	स_नकल(uid->serial, निजी->ned->HDA_location,
	       माप(uid->serial) - 1);
	EBCASC(uid->serial, माप(uid->serial) - 1);
	uid->ssid = निजी->gneq->subप्रणालीID;
	uid->real_unit_addr = निजी->ned->unit_addr;
	अगर (निजी->sneq) अणु
		uid->type = निजी->sneq->sua_flags;
		अगर (uid->type == UA_BASE_PAV_ALIAS)
			uid->base_unit_addr = निजी->sneq->base_unit_addr;
	पूर्ण अन्यथा अणु
		uid->type = UA_BASE_DEVICE;
	पूर्ण
	अगर (निजी->vdsneq) अणु
		क्रम (count = 0; count < 16; count++) अणु
			प्र_लिखो(uid->vduit+2*count, "%02x",
				निजी->vdsneq->uit[count]);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Generate device unique id that specअगरies the physical device.
 */
अटल पूर्णांक dasd_eckd_generate_uid(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित दीर्घ flags;

	अगर (!निजी)
		वापस -ENODEV;
	अगर (!निजी->ned || !निजी->gneq)
		वापस -ENODEV;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	create_uid(निजी);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_eckd_get_uid(काष्ठा dasd_device *device, काष्ठा dasd_uid *uid)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित दीर्घ flags;

	अगर (निजी) अणु
		spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
		*uid = निजी->uid;
		spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * compare device UID with data of a given dasd_eckd_निजी काष्ठाure
 * वापस 0 क्रम match
 */
अटल पूर्णांक dasd_eckd_compare_path_uid(काष्ठा dasd_device *device,
				      काष्ठा dasd_eckd_निजी *निजी)
अणु
	काष्ठा dasd_uid device_uid;

	create_uid(निजी);
	dasd_eckd_get_uid(device, &device_uid);

	वापस स_भेद(&device_uid, &निजी->uid, माप(काष्ठा dasd_uid));
पूर्ण

अटल व्योम dasd_eckd_fill_rcd_cqr(काष्ठा dasd_device *device,
				   काष्ठा dasd_ccw_req *cqr,
				   __u8 *rcd_buffer,
				   __u8 lpm)
अणु
	काष्ठा ccw1 *ccw;
	/*
	 * buffer has to start with EBCDIC "V1.0" to show
	 * support क्रम भव device SNEQ
	 */
	rcd_buffer[0] = 0xE5;
	rcd_buffer[1] = 0xF1;
	rcd_buffer[2] = 0x4B;
	rcd_buffer[3] = 0xF0;

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_RCD;
	ccw->flags = 0;
	ccw->cda = (__u32)(addr_t)rcd_buffer;
	ccw->count = DASD_ECKD_RCD_DATA_SIZE;
	cqr->magic = DASD_ECKD_MAGIC;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->expires = 10*HZ;
	cqr->lpm = lpm;
	cqr->retries = 256;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	set_bit(DASD_CQR_VERIFY_PATH, &cqr->flags);
पूर्ण

/*
 * Wakeup helper क्रम पढ़ो_conf
 * अगर the cqr is not करोne and needs some error recovery
 * the buffer has to be re-initialized with the EBCDIC "V1.0"
 * to show support क्रम भव device SNEQ
 */
अटल व्योम पढ़ो_conf_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	काष्ठा ccw1 *ccw;
	__u8 *rcd_buffer;

	अगर (cqr->status !=  DASD_CQR_DONE) अणु
		ccw = cqr->cpaddr;
		rcd_buffer = (__u8 *)((addr_t) ccw->cda);
		स_रखो(rcd_buffer, 0, माप(*rcd_buffer));

		rcd_buffer[0] = 0xE5;
		rcd_buffer[1] = 0xF1;
		rcd_buffer[2] = 0x4B;
		rcd_buffer[3] = 0xF0;
	पूर्ण
	dasd_wakeup_cb(cqr, data);
पूर्ण

अटल पूर्णांक dasd_eckd_पढ़ो_conf_immediately(काष्ठा dasd_device *device,
					   काष्ठा dasd_ccw_req *cqr,
					   __u8 *rcd_buffer,
					   __u8 lpm)
अणु
	काष्ठा ciw *ciw;
	पूर्णांक rc;
	/*
	 * sanity check: scan क्रम RCD command in extended SenseID data
	 * some devices करो not support RCD
	 */
	ciw = ccw_device_get_ciw(device->cdev, CIW_TYPE_RCD);
	अगर (!ciw || ciw->cmd != DASD_ECKD_CCW_RCD)
		वापस -EOPNOTSUPP;

	dasd_eckd_fill_rcd_cqr(device, cqr, rcd_buffer, lpm);
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags);
	cqr->retries = 5;
	cqr->callback = पढ़ो_conf_cb;
	rc = dasd_sleep_on_immediatly(cqr);
	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_पढ़ो_conf_lpm(काष्ठा dasd_device *device,
				   व्योम **rcd_buffer,
				   पूर्णांक *rcd_buffer_size, __u8 lpm)
अणु
	काष्ठा ciw *ciw;
	अक्षर *rcd_buf = शून्य;
	पूर्णांक ret;
	काष्ठा dasd_ccw_req *cqr;

	/*
	 * sanity check: scan क्रम RCD command in extended SenseID data
	 * some devices करो not support RCD
	 */
	ciw = ccw_device_get_ciw(device->cdev, CIW_TYPE_RCD);
	अगर (!ciw || ciw->cmd != DASD_ECKD_CCW_RCD) अणु
		ret = -EOPNOTSUPP;
		जाओ out_error;
	पूर्ण
	rcd_buf = kzalloc(DASD_ECKD_RCD_DATA_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!rcd_buf) अणु
		ret = -ENOMEM;
		जाओ out_error;
	पूर्ण
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* RCD */,
				   0, /* use rcd_buf as data ara */
				   device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "Could not allocate RCD request");
		ret = -ENOMEM;
		जाओ out_error;
	पूर्ण
	dasd_eckd_fill_rcd_cqr(device, cqr, rcd_buf, lpm);
	cqr->callback = पढ़ो_conf_cb;
	ret = dasd_sleep_on(cqr);
	/*
	 * on success we update the user input parms
	 */
	dasd_sमुक्त_request(cqr, cqr->memdev);
	अगर (ret)
		जाओ out_error;

	*rcd_buffer_size = DASD_ECKD_RCD_DATA_SIZE;
	*rcd_buffer = rcd_buf;
	वापस 0;
out_error:
	kमुक्त(rcd_buf);
	*rcd_buffer = शून्य;
	*rcd_buffer_size = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक dasd_eckd_identअगरy_conf_parts(काष्ठा dasd_eckd_निजी *निजी)
अणु

	काष्ठा dasd_sneq *sneq;
	पूर्णांक i, count;

	निजी->ned = शून्य;
	निजी->sneq = शून्य;
	निजी->vdsneq = शून्य;
	निजी->gneq = शून्य;
	count = निजी->conf_len / माप(काष्ठा dasd_sneq);
	sneq = (काष्ठा dasd_sneq *)निजी->conf_data;
	क्रम (i = 0; i < count; ++i) अणु
		अगर (sneq->flags.identअगरier == 1 && sneq->क्रमmat == 1)
			निजी->sneq = sneq;
		अन्यथा अगर (sneq->flags.identअगरier == 1 && sneq->क्रमmat == 4)
			निजी->vdsneq = (काष्ठा vd_sneq *)sneq;
		अन्यथा अगर (sneq->flags.identअगरier == 2)
			निजी->gneq = (काष्ठा dasd_gneq *)sneq;
		अन्यथा अगर (sneq->flags.identअगरier == 3 && sneq->res1 == 1)
			निजी->ned = (काष्ठा dasd_ned *)sneq;
		sneq++;
	पूर्ण
	अगर (!निजी->ned || !निजी->gneq) अणु
		निजी->ned = शून्य;
		निजी->sneq = शून्य;
		निजी->vdsneq = शून्य;
		निजी->gneq = शून्य;
		वापस -EINVAL;
	पूर्ण
	वापस 0;

पूर्ण;

अटल अचिन्हित अक्षर dasd_eckd_path_access(व्योम *conf_data, पूर्णांक conf_len)
अणु
	काष्ठा dasd_gneq *gneq;
	पूर्णांक i, count, found;

	count = conf_len / माप(*gneq);
	gneq = (काष्ठा dasd_gneq *)conf_data;
	found = 0;
	क्रम (i = 0; i < count; ++i) अणु
		अगर (gneq->flags.identअगरier == 2) अणु
			found = 1;
			अवरोध;
		पूर्ण
		gneq++;
	पूर्ण
	अगर (found)
		वापस ((अक्षर *)gneq)[18] & 0x07;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम dasd_eckd_store_conf_data(काष्ठा dasd_device *device,
				      काष्ठा dasd_conf_data *conf_data, पूर्णांक chp)
अणु
	काष्ठा channel_path_desc_fmt0 *chp_desc;
	काष्ठा subchannel_id sch_id;

	ccw_device_get_schid(device->cdev, &sch_id);
	/*
	 * path handling and पढ़ो_conf allocate data
	 * मुक्त it beक्रमe replacing the poपूर्णांकer
	 */
	kमुक्त(device->path[chp].conf_data);
	device->path[chp].conf_data = conf_data;
	device->path[chp].cssid = sch_id.cssid;
	device->path[chp].ssid = sch_id.ssid;
	chp_desc = ccw_device_get_chp_desc(device->cdev, chp);
	अगर (chp_desc)
		device->path[chp].chpid = chp_desc->chpid;
	kमुक्त(chp_desc);
पूर्ण

अटल व्योम dasd_eckd_clear_conf_data(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक i;

	निजी->conf_data = शून्य;
	निजी->conf_len = 0;
	क्रम (i = 0; i < 8; i++) अणु
		kमुक्त(device->path[i].conf_data);
		device->path[i].conf_data = शून्य;
		device->path[i].cssid = 0;
		device->path[i].ssid = 0;
		device->path[i].chpid = 0;
		dasd_path_notoper(device, i);
	पूर्ण
पूर्ण

अटल व्योम dasd_eckd_पढ़ो_fc_security(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	u8 esm_valid;
	u8 esm[8];
	पूर्णांक chp;
	पूर्णांक rc;

	rc = chsc_scud(निजी->uid.ssid, (u64 *)esm, &esm_valid);
	अगर (rc) अणु
		क्रम (chp = 0; chp < 8; chp++)
			device->path[chp].fc_security = 0;
		वापस;
	पूर्ण

	क्रम (chp = 0; chp < 8; chp++) अणु
		अगर (esm_valid & (0x80 >> chp))
			device->path[chp].fc_security = esm[chp];
		अन्यथा
			device->path[chp].fc_security = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dasd_eckd_पढ़ो_conf(काष्ठा dasd_device *device)
अणु
	व्योम *conf_data;
	पूर्णांक conf_len, conf_data_saved;
	पूर्णांक rc, path_err, pos;
	__u8 lpm, opm;
	काष्ठा dasd_eckd_निजी *निजी, path_निजी;
	काष्ठा dasd_uid *uid;
	अक्षर prपूर्णांक_path_uid[60], prपूर्णांक_device_uid[60];

	निजी = device->निजी;
	opm = ccw_device_get_path_mask(device->cdev);
	conf_data_saved = 0;
	path_err = 0;
	/* get configuration data per operational path */
	क्रम (lpm = 0x80; lpm; lpm>>= 1) अणु
		अगर (!(lpm & opm))
			जारी;
		rc = dasd_eckd_पढ़ो_conf_lpm(device, &conf_data,
					     &conf_len, lpm);
		अगर (rc && rc != -EOPNOTSUPP) अणु	/* -EOPNOTSUPP is ok */
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
					"Read configuration data returned "
					"error %d", rc);
			वापस rc;
		पूर्ण
		अगर (conf_data == शून्य) अणु
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
					"No configuration data "
					"retrieved");
			/* no further analysis possible */
			dasd_path_add_opm(device, opm);
			जारी;	/* no error */
		पूर्ण
		/* save first valid configuration data */
		अगर (!conf_data_saved) अणु
			/* initially clear previously stored conf_data */
			dasd_eckd_clear_conf_data(device);
			निजी->conf_data = conf_data;
			निजी->conf_len = conf_len;
			अगर (dasd_eckd_identअगरy_conf_parts(निजी)) अणु
				निजी->conf_data = शून्य;
				निजी->conf_len = 0;
				kमुक्त(conf_data);
				जारी;
			पूर्ण
			/*
			 * build device UID that other path data
			 * can be compared to it
			 */
			dasd_eckd_generate_uid(device);
			conf_data_saved++;
		पूर्ण अन्यथा अणु
			path_निजी.conf_data = conf_data;
			path_निजी.conf_len = DASD_ECKD_RCD_DATA_SIZE;
			अगर (dasd_eckd_identअगरy_conf_parts(
				    &path_निजी)) अणु
				path_निजी.conf_data = शून्य;
				path_निजी.conf_len = 0;
				kमुक्त(conf_data);
				जारी;
			पूर्ण
			अगर (dasd_eckd_compare_path_uid(
				    device, &path_निजी)) अणु
				uid = &path_निजी.uid;
				अगर (म_माप(uid->vduit) > 0)
					snम_लिखो(prपूर्णांक_path_uid,
						 माप(prपूर्णांक_path_uid),
						 "%s.%s.%04x.%02x.%s",
						 uid->venकरोr, uid->serial,
						 uid->ssid, uid->real_unit_addr,
						 uid->vduit);
				अन्यथा
					snम_लिखो(prपूर्णांक_path_uid,
						 माप(prपूर्णांक_path_uid),
						 "%s.%s.%04x.%02x",
						 uid->venकरोr, uid->serial,
						 uid->ssid,
						 uid->real_unit_addr);
				uid = &निजी->uid;
				अगर (म_माप(uid->vduit) > 0)
					snम_लिखो(prपूर्णांक_device_uid,
						 माप(prपूर्णांक_device_uid),
						 "%s.%s.%04x.%02x.%s",
						 uid->venकरोr, uid->serial,
						 uid->ssid, uid->real_unit_addr,
						 uid->vduit);
				अन्यथा
					snम_लिखो(prपूर्णांक_device_uid,
						 माप(prपूर्णांक_device_uid),
						 "%s.%s.%04x.%02x",
						 uid->venकरोr, uid->serial,
						 uid->ssid,
						 uid->real_unit_addr);
				dev_err(&device->cdev->dev,
					"Not all channel paths lead to "
					"the same device, path %02X leads to "
					"device %s instead of %s\n", lpm,
					prपूर्णांक_path_uid, prपूर्णांक_device_uid);
				path_err = -EINVAL;
				dasd_path_add_cablepm(device, lpm);
				जारी;
			पूर्ण
			path_निजी.conf_data = शून्य;
			path_निजी.conf_len = 0;
		पूर्ण

		pos = pathmask_to_pos(lpm);
		dasd_eckd_store_conf_data(device, conf_data, pos);

		चयन (dasd_eckd_path_access(conf_data, conf_len)) अणु
		हाल 0x02:
			dasd_path_add_nppm(device, lpm);
			अवरोध;
		हाल 0x03:
			dasd_path_add_ppm(device, lpm);
			अवरोध;
		पूर्ण
		अगर (!dasd_path_get_opm(device)) अणु
			dasd_path_set_opm(device, lpm);
			dasd_generic_path_operational(device);
		पूर्ण अन्यथा अणु
			dasd_path_add_opm(device, lpm);
		पूर्ण
	पूर्ण

	dasd_eckd_पढ़ो_fc_security(device);

	वापस path_err;
पूर्ण

अटल u32 get_fcx_max_data(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक fcx_in_css, fcx_in_gneq, fcx_in_features;
	अचिन्हित पूर्णांक mdc;
	पूर्णांक tpm;

	अगर (dasd_nofcx)
		वापस 0;
	/* is transport mode supported? */
	fcx_in_css = css_general_अक्षरacteristics.fcx;
	fcx_in_gneq = निजी->gneq->reserved2[7] & 0x04;
	fcx_in_features = निजी->features.feature[40] & 0x80;
	tpm = fcx_in_css && fcx_in_gneq && fcx_in_features;

	अगर (!tpm)
		वापस 0;

	mdc = ccw_device_get_mdc(device->cdev, 0);
	अगर (mdc == 0) अणु
		dev_warn(&device->cdev->dev, "Detecting the maximum supported data size for zHPF requests failed\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस (u32)mdc * FCX_MAX_DATA_FACTOR;
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_fcx_max_data(काष्ठा dasd_device *device, __u8 lpm)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित पूर्णांक mdc;
	u32 fcx_max_data;

	अगर (निजी->fcx_max_data) अणु
		mdc = ccw_device_get_mdc(device->cdev, lpm);
		अगर (mdc == 0) अणु
			dev_warn(&device->cdev->dev,
				 "Detecting the maximum data size for zHPF "
				 "requests failed (rc=%d) for a new path %x\n",
				 mdc, lpm);
			वापस mdc;
		पूर्ण
		fcx_max_data = (u32)mdc * FCX_MAX_DATA_FACTOR;
		अगर (fcx_max_data < निजी->fcx_max_data) अणु
			dev_warn(&device->cdev->dev,
				 "The maximum data size for zHPF requests %u "
				 "on a new path %x is below the active maximum "
				 "%u\n", fcx_max_data, lpm,
				 निजी->fcx_max_data);
			वापस -EACCES;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rebuild_device_uid(काष्ठा dasd_device *device,
			      काष्ठा pe_handler_work_data *data)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	__u8 lpm, opm = dasd_path_get_opm(device);
	पूर्णांक rc = -ENODEV;

	क्रम (lpm = 0x80; lpm; lpm >>= 1) अणु
		अगर (!(lpm & opm))
			जारी;
		स_रखो(&data->rcd_buffer, 0, माप(data->rcd_buffer));
		स_रखो(&data->cqr, 0, माप(data->cqr));
		data->cqr.cpaddr = &data->ccw;
		rc = dasd_eckd_पढ़ो_conf_immediately(device, &data->cqr,
						     data->rcd_buffer,
						     lpm);

		अगर (rc) अणु
			अगर (rc == -EOPNOTSUPP) /* -EOPNOTSUPP is ok */
				जारी;
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
					"Read configuration data "
					"returned error %d", rc);
			अवरोध;
		पूर्ण
		स_नकल(निजी->conf_data, data->rcd_buffer,
		       DASD_ECKD_RCD_DATA_SIZE);
		अगर (dasd_eckd_identअगरy_conf_parts(निजी)) अणु
			rc = -ENODEV;
		पूर्ण अन्यथा /* first valid path is enough */
			अवरोध;
	पूर्ण

	अगर (!rc)
		rc = dasd_eckd_generate_uid(device);

	वापस rc;
पूर्ण

अटल व्योम dasd_eckd_path_available_action(काष्ठा dasd_device *device,
					    काष्ठा pe_handler_work_data *data)
अणु
	काष्ठा dasd_eckd_निजी path_निजी;
	काष्ठा dasd_uid *uid;
	__u8 path_rcd_buf[DASD_ECKD_RCD_DATA_SIZE];
	__u8 lpm, opm, npm, ppm, epm, hpfpm, cablepm;
	काष्ठा dasd_conf_data *conf_data;
	अचिन्हित दीर्घ flags;
	अक्षर prपूर्णांक_uid[60];
	पूर्णांक rc, pos;

	opm = 0;
	npm = 0;
	ppm = 0;
	epm = 0;
	hpfpm = 0;
	cablepm = 0;

	क्रम (lpm = 0x80; lpm; lpm >>= 1) अणु
		अगर (!(lpm & data->tbvpm))
			जारी;
		स_रखो(&data->rcd_buffer, 0, माप(data->rcd_buffer));
		स_रखो(&data->cqr, 0, माप(data->cqr));
		data->cqr.cpaddr = &data->ccw;
		rc = dasd_eckd_पढ़ो_conf_immediately(device, &data->cqr,
						     data->rcd_buffer,
						     lpm);
		अगर (!rc) अणु
			चयन (dasd_eckd_path_access(data->rcd_buffer,
						      DASD_ECKD_RCD_DATA_SIZE)
				) अणु
			हाल 0x02:
				npm |= lpm;
				अवरोध;
			हाल 0x03:
				ppm |= lpm;
				अवरोध;
			पूर्ण
			opm |= lpm;
		पूर्ण अन्यथा अगर (rc == -EOPNOTSUPP) अणु
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
					"path verification: No configuration "
					"data retrieved");
			opm |= lpm;
		पूर्ण अन्यथा अगर (rc == -EAGAIN) अणु
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
					"path verification: device is stopped,"
					" try again later");
			epm |= lpm;
		पूर्ण अन्यथा अणु
			dev_warn(&device->cdev->dev,
				 "Reading device feature codes failed "
				 "(rc=%d) for new path %x\n", rc, lpm);
			जारी;
		पूर्ण
		अगर (verअगरy_fcx_max_data(device, lpm)) अणु
			opm &= ~lpm;
			npm &= ~lpm;
			ppm &= ~lpm;
			hpfpm |= lpm;
			जारी;
		पूर्ण

		/*
		 * save conf_data क्रम comparison after
		 * rebuild_device_uid may have changed
		 * the original data
		 */
		स_नकल(&path_rcd_buf, data->rcd_buffer,
		       DASD_ECKD_RCD_DATA_SIZE);
		path_निजी.conf_data = (व्योम *) &path_rcd_buf;
		path_निजी.conf_len = DASD_ECKD_RCD_DATA_SIZE;
		अगर (dasd_eckd_identअगरy_conf_parts(&path_निजी)) अणु
			path_निजी.conf_data = शून्य;
			path_निजी.conf_len = 0;
			जारी;
		पूर्ण

		/*
		 * compare path UID with device UID only अगर at least
		 * one valid path is left
		 * in other हाल the device UID may have changed and
		 * the first working path UID will be used as device UID
		 */
		अगर (dasd_path_get_opm(device) &&
		    dasd_eckd_compare_path_uid(device, &path_निजी)) अणु
			/*
			 * the comparison was not successful
			 * rebuild the device UID with at least one
			 * known path in हाल a z/VM hyperswap command
			 * has changed the device
			 *
			 * after this compare again
			 *
			 * अगर either the rebuild or the recompare fails
			 * the path can not be used
			 */
			अगर (rebuild_device_uid(device, data) ||
			    dasd_eckd_compare_path_uid(
				    device, &path_निजी)) अणु
				uid = &path_निजी.uid;
				अगर (म_माप(uid->vduit) > 0)
					snम_लिखो(prपूर्णांक_uid, माप(prपूर्णांक_uid),
						 "%s.%s.%04x.%02x.%s",
						 uid->venकरोr, uid->serial,
						 uid->ssid, uid->real_unit_addr,
						 uid->vduit);
				अन्यथा
					snम_लिखो(prपूर्णांक_uid, माप(prपूर्णांक_uid),
						 "%s.%s.%04x.%02x",
						 uid->venकरोr, uid->serial,
						 uid->ssid,
						 uid->real_unit_addr);
				dev_err(&device->cdev->dev,
					"The newly added channel path %02X "
					"will not be used because it leads "
					"to a different device %s\n",
					lpm, prपूर्णांक_uid);
				opm &= ~lpm;
				npm &= ~lpm;
				ppm &= ~lpm;
				cablepm |= lpm;
				जारी;
			पूर्ण
		पूर्ण

		conf_data = kzalloc(DASD_ECKD_RCD_DATA_SIZE, GFP_KERNEL);
		अगर (conf_data) अणु
			स_नकल(conf_data, data->rcd_buffer,
			       DASD_ECKD_RCD_DATA_SIZE);
		पूर्ण
		pos = pathmask_to_pos(lpm);
		dasd_eckd_store_conf_data(device, conf_data, pos);

		/*
		 * There is a small chance that a path is lost again between
		 * above path verअगरication and the following modअगरication of
		 * the device opm mask. We could aव्योम that race here by using
		 * yet another path mask, but we rather deal with this unlikely
		 * situation in dasd_start_IO.
		 */
		spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
		अगर (!dasd_path_get_opm(device) && opm) अणु
			dasd_path_set_opm(device, opm);
			dasd_generic_path_operational(device);
		पूर्ण अन्यथा अणु
			dasd_path_add_opm(device, opm);
		पूर्ण
		dasd_path_add_nppm(device, npm);
		dasd_path_add_ppm(device, ppm);
		dasd_path_add_tbvpm(device, epm);
		dasd_path_add_cablepm(device, cablepm);
		dasd_path_add_nohpfpm(device, hpfpm);
		spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

		dasd_path_create_kobj(device, pos);
	पूर्ण
पूर्ण

अटल व्योम करो_pe_handler_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pe_handler_work_data *data;
	काष्ठा dasd_device *device;

	data = container_of(work, काष्ठा pe_handler_work_data, worker);
	device = data->device;

	/* delay path verअगरication until device was resumed */
	अगर (test_bit(DASD_FLAG_SUSPENDED, &device->flags)) अणु
		schedule_work(work);
		वापस;
	पूर्ण
	/* check अगर path verअगरication alपढ़ोy running and delay अगर so */
	अगर (test_and_set_bit(DASD_FLAG_PATH_VERIFY, &device->flags)) अणु
		schedule_work(work);
		वापस;
	पूर्ण

	अगर (data->tbvpm)
		dasd_eckd_path_available_action(device, data);
	अगर (data->fcsecpm)
		dasd_eckd_पढ़ो_fc_security(device);

	clear_bit(DASD_FLAG_PATH_VERIFY, &device->flags);
	dasd_put_device(device);
	अगर (data->isglobal)
		mutex_unlock(&dasd_pe_handler_mutex);
	अन्यथा
		kमुक्त(data);
पूर्ण

अटल पूर्णांक dasd_eckd_pe_handler(काष्ठा dasd_device *device,
				__u8 tbvpm, __u8 fcsecpm)
अणु
	काष्ठा pe_handler_work_data *data;

	data = kदो_स्मृति(माप(*data), GFP_ATOMIC | GFP_DMA);
	अगर (!data) अणु
		अगर (mutex_trylock(&dasd_pe_handler_mutex)) अणु
			data = pe_handler_worker;
			data->isglobal = 1;
		पूर्ण अन्यथा अणु
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(data, 0, माप(*data));
		data->isglobal = 0;
	पूर्ण
	INIT_WORK(&data->worker, करो_pe_handler_work);
	dasd_get_device(device);
	data->device = device;
	data->tbvpm = tbvpm;
	data->fcsecpm = fcsecpm;
	schedule_work(&data->worker);
	वापस 0;
पूर्ण

अटल व्योम dasd_eckd_reset_path(काष्ठा dasd_device *device, __u8 pm)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित दीर्घ flags;

	अगर (!निजी->fcx_max_data)
		निजी->fcx_max_data = get_fcx_max_data(device);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dasd_path_set_tbvpm(device, pm ? : dasd_path_get_notoperpm(device));
	dasd_schedule_device_bh(device);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
पूर्ण

अटल पूर्णांक dasd_eckd_पढ़ो_features(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_rssd_features *features;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	स_रखो(&निजी->features, 0, माप(काष्ठा dasd_rssd_features));
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   (माप(काष्ठा dasd_psf_prssd_data) +
				    माप(काष्ठा dasd_rssd_features)),
				   device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s", "Could not "
				"allocate initialization request");
		वापस PTR_ERR(cqr);
	पूर्ण
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = 10 * HZ;

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
	स_रखो(prssdp, 0, माप(काष्ठा dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x41;	/* Read Feature Codes */
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(काष्ठा dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subप्रणाली Data - feature codes */
	features = (काष्ठा dasd_rssd_features *) (prssdp + 1);
	स_रखो(features, 0, माप(काष्ठा dasd_rssd_features));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(काष्ठा dasd_rssd_features);
	ccw->cda = (__u32)(addr_t) features;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	rc = dasd_sleep_on(cqr);
	अगर (rc == 0) अणु
		prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
		features = (काष्ठा dasd_rssd_features *) (prssdp + 1);
		स_नकल(&निजी->features, features,
		       माप(काष्ठा dasd_rssd_features));
	पूर्ण अन्यथा
		dev_warn(&device->cdev->dev, "Reading device feature codes"
			 " failed with rc=%d\n", rc);
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/* Read Volume Inक्रमmation - Volume Storage Query */
अटल पूर्णांक dasd_eckd_पढ़ो_vol_info(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_rssd_vsq *vsq;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक useglobal;
	पूर्णांक rc;

	/* This command cannot be executed on an alias device */
	अगर (निजी->uid.type == UA_BASE_PAV_ALIAS ||
	    निजी->uid.type == UA_HYPER_PAV_ALIAS)
		वापस 0;

	useglobal = 0;
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 2 /* PSF + RSSD */,
				   माप(*prssdp) + माप(*vsq), device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate initialization request");
		mutex_lock(&dasd_vol_info_mutex);
		useglobal = 1;
		cqr = &dasd_vol_info_req->cqr;
		स_रखो(cqr, 0, माप(*cqr));
		स_रखो(dasd_vol_info_req, 0, माप(*dasd_vol_info_req));
		cqr->cpaddr = &dasd_vol_info_req->ccw;
		cqr->data = &dasd_vol_info_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	पूर्ण

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = cqr->data;
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = PSF_SUBORDER_VSQ;	/* Volume Storage Query */
	prssdp->lss = निजी->ned->ID;
	prssdp->volume = निजी->ned->unit_addr;

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(*prssdp);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t)prssdp;

	/* Read Subप्रणाली Data - Volume Storage Query */
	vsq = (काष्ठा dasd_rssd_vsq *)(prssdp + 1);
	स_रखो(vsq, 0, माप(*vsq));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(*vsq);
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t)vsq;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = device->शेष_expires * HZ;
	/* The command might not be supported. Suppress the error output */
	__set_bit(DASD_CQR_SUPPRESS_CR, &cqr->flags);

	rc = dasd_sleep_on_पूर्णांकerruptible(cqr);
	अगर (rc == 0) अणु
		स_नकल(&निजी->vsq, vsq, माप(*vsq));
	पूर्ण अन्यथा अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Reading the volume storage information failed with rc=%d", rc);
	पूर्ण

	अगर (useglobal)
		mutex_unlock(&dasd_vol_info_mutex);
	अन्यथा
		dasd_sमुक्त_request(cqr, cqr->memdev);

	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_is_ese(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->vsq.vol_info.ese;
पूर्ण

अटल पूर्णांक dasd_eckd_ext_pool_id(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->vsq.extent_pool_id;
पूर्ण

/*
 * This value represents the total amount of available space. As more space is
 * allocated by ESE volumes, this value will decrease.
 * The data क्रम this value is thereक्रमe updated on any call.
 */
अटल पूर्णांक dasd_eckd_space_configured(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक rc;

	rc = dasd_eckd_पढ़ो_vol_info(device);

	वापस rc ? : निजी->vsq.space_configured;
पूर्ण

/*
 * The value of space allocated by an ESE volume may have changed and is
 * thereक्रमe updated on any call.
 */
अटल पूर्णांक dasd_eckd_space_allocated(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक rc;

	rc = dasd_eckd_पढ़ो_vol_info(device);

	वापस rc ? : निजी->vsq.space_allocated;
पूर्ण

अटल पूर्णांक dasd_eckd_logical_capacity(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->vsq.logical_capacity;
पूर्ण

अटल व्योम dasd_eckd_ext_pool_exhaust_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ext_pool_exhaust_work_data *data;
	काष्ठा dasd_device *device;
	काष्ठा dasd_device *base;

	data = container_of(work, काष्ठा ext_pool_exhaust_work_data, worker);
	device = data->device;
	base = data->base;

	अगर (!base)
		base = device;
	अगर (dasd_eckd_space_configured(base) != 0) अणु
		dasd_generic_space_avail(device);
	पूर्ण अन्यथा अणु
		dev_warn(&device->cdev->dev, "No space left in the extent pool\n");
		DBF_DEV_EVENT(DBF_WARNING, device, "%s", "out of space");
	पूर्ण

	dasd_put_device(device);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक dasd_eckd_ext_pool_exhaust(काष्ठा dasd_device *device,
				      काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा ext_pool_exhaust_work_data *data;

	data = kzalloc(माप(*data), GFP_ATOMIC);
	अगर (!data)
		वापस -ENOMEM;
	INIT_WORK(&data->worker, dasd_eckd_ext_pool_exhaust_work);
	dasd_get_device(device);
	data->device = device;

	अगर (cqr->block)
		data->base = cqr->block->base;
	अन्यथा अगर (cqr->basedev)
		data->base = cqr->basedev;
	अन्यथा
		data->base = शून्य;

	schedule_work(&data->worker);

	वापस 0;
पूर्ण

अटल व्योम dasd_eckd_cpy_ext_pool_data(काष्ठा dasd_device *device,
					काष्ठा dasd_rssd_lcq *lcq)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक pool_id = dasd_eckd_ext_pool_id(device);
	काष्ठा dasd_ext_pool_sum eps;
	पूर्णांक i;

	क्रम (i = 0; i < lcq->pool_count; i++) अणु
		eps = lcq->ext_pool_sum[i];
		अगर (eps.pool_id == pool_id) अणु
			स_नकल(&निजी->eps, &eps,
			       माप(काष्ठा dasd_ext_pool_sum));
		पूर्ण
	पूर्ण
पूर्ण

/* Read Extent Pool Inक्रमmation - Logical Configuration Query */
अटल पूर्णांक dasd_eckd_पढ़ो_ext_pool_info(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_rssd_lcq *lcq;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	/* This command cannot be executed on an alias device */
	अगर (निजी->uid.type == UA_BASE_PAV_ALIAS ||
	    निजी->uid.type == UA_HYPER_PAV_ALIAS)
		वापस 0;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 2 /* PSF + RSSD */,
				   माप(*prssdp) + माप(*lcq), device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate initialization request");
		वापस PTR_ERR(cqr);
	पूर्ण

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = cqr->data;
	स_रखो(prssdp, 0, माप(*prssdp));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = PSF_SUBORDER_LCQ;	/* Logical Configuration Query */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(*prssdp);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t)prssdp;

	lcq = (काष्ठा dasd_rssd_lcq *)(prssdp + 1);
	स_रखो(lcq, 0, माप(*lcq));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(*lcq);
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t)lcq;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = device->शेष_expires * HZ;
	/* The command might not be supported. Suppress the error output */
	__set_bit(DASD_CQR_SUPPRESS_CR, &cqr->flags);

	rc = dasd_sleep_on_पूर्णांकerruptible(cqr);
	अगर (rc == 0) अणु
		dasd_eckd_cpy_ext_pool_data(device, lcq);
	पूर्ण अन्यथा अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Reading the logical configuration failed with rc=%d", rc);
	पूर्ण

	dasd_sमुक्त_request(cqr, cqr->memdev);

	वापस rc;
पूर्ण

/*
 * Depending on the device type, the extent size is specअगरied either as
 * cylinders per extent (CKD) or size per extent (FBA)
 * A 1GB size corresponds to 1113cyl, and 16MB to 21cyl.
 */
अटल पूर्णांक dasd_eckd_ext_size(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_ext_pool_sum eps = निजी->eps;

	अगर (!eps.flags.extent_size_valid)
		वापस 0;
	अगर (eps.extent_size.size_1G)
		वापस 1113;
	अगर (eps.extent_size.size_16M)
		वापस 21;

	वापस 0;
पूर्ण

अटल पूर्णांक dasd_eckd_ext_pool_warn_thrshld(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->eps.warn_thrshld;
पूर्ण

अटल पूर्णांक dasd_eckd_ext_pool_cap_at_warnlevel(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->eps.flags.capacity_at_warnlevel;
पूर्ण

/*
 * Extent Pool out of space
 */
अटल पूर्णांक dasd_eckd_ext_pool_oos(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->eps.flags.pool_oos;
पूर्ण

/*
 * Build CP क्रम Perक्रमm Subप्रणाली Function - SSC.
 */
अटल काष्ठा dasd_ccw_req *dasd_eckd_build_psf_ssc(काष्ठा dasd_device *device,
						    पूर्णांक enable_pav)
अणु
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_psf_ssc_data *psf_ssc_data;
	काष्ठा ccw1 *ccw;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */ ,
				  माप(काष्ठा dasd_psf_ssc_data),
				   device, शून्य);

	अगर (IS_ERR(cqr)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			   "Could not allocate PSF-SSC request");
		वापस cqr;
	पूर्ण
	psf_ssc_data = (काष्ठा dasd_psf_ssc_data *)cqr->data;
	psf_ssc_data->order = PSF_ORDER_SSC;
	psf_ssc_data->suborder = 0xc0;
	अगर (enable_pav) अणु
		psf_ssc_data->suborder |= 0x08;
		psf_ssc_data->reserved[0] = 0x88;
	पूर्ण
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->cda = (__u32)(addr_t)psf_ssc_data;
	ccw->count = 66;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = 10*HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	वापस cqr;
पूर्ण

/*
 * Perक्रमm Subप्रणाली Function.
 * It is necessary to trigger CIO क्रम channel revalidation since this
 * call might change behaviour of DASD devices.
 */
अटल पूर्णांक
dasd_eckd_psf_ssc(काष्ठा dasd_device *device, पूर्णांक enable_pav,
		  अचिन्हित दीर्घ flags)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;

	cqr = dasd_eckd_build_psf_ssc(device, enable_pav);
	अगर (IS_ERR(cqr))
		वापस PTR_ERR(cqr);

	/*
	 * set flags e.g. turn on failfast, to prevent blocking
	 * the calling function should handle failed requests
	 */
	cqr->flags |= flags;

	rc = dasd_sleep_on(cqr);
	अगर (!rc)
		/* trigger CIO to reprobe devices */
		css_schedule_reprobe();
	अन्यथा अगर (cqr->पूर्णांकrc == -EAGAIN)
		rc = -EAGAIN;

	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * Valide storage server of current device.
 */
अटल पूर्णांक dasd_eckd_validate_server(काष्ठा dasd_device *device,
				     अचिन्हित दीर्घ flags)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक enable_pav, rc;

	अगर (निजी->uid.type == UA_BASE_PAV_ALIAS ||
	    निजी->uid.type == UA_HYPER_PAV_ALIAS)
		वापस 0;
	अगर (dasd_nopav || MACHINE_IS_VM)
		enable_pav = 0;
	अन्यथा
		enable_pav = 1;
	rc = dasd_eckd_psf_ssc(device, enable_pav, flags);

	/* may be requested feature is not available on server,
	 * thereक्रमe just report error and go ahead */
	DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "PSF-SSC for SSID %04x "
			"returned rc=%d", निजी->uid.ssid, rc);
	वापस rc;
पूर्ण

/*
 * worker to करो a validate server in हाल of a lost pathgroup
 */
अटल व्योम dasd_eckd_करो_validate_server(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dasd_device *device = container_of(work, काष्ठा dasd_device,
						  kick_validate);
	अचिन्हित दीर्घ flags = 0;

	set_bit(DASD_CQR_FLAGS_FAILFAST, &flags);
	अगर (dasd_eckd_validate_server(device, flags)
	    == -EAGAIN) अणु
		/* schedule worker again अगर failed */
		schedule_work(&device->kick_validate);
		वापस;
	पूर्ण

	dasd_put_device(device);
पूर्ण

अटल व्योम dasd_eckd_kick_validate_server(काष्ठा dasd_device *device)
अणु
	dasd_get_device(device);
	/* निकास अगर device not online or in offline processing */
	अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags) ||
	   device->state < DASD_STATE_ONLINE) अणु
		dasd_put_device(device);
		वापस;
	पूर्ण
	/* queue call to करो_validate_server to the kernel event daemon. */
	अगर (!schedule_work(&device->kick_validate))
		dasd_put_device(device);
पूर्ण

/*
 * Check device अक्षरacteristics.
 * If the device is accessible using ECKD discipline, the device is enabled.
 */
अटल पूर्णांक
dasd_eckd_check_अक्षरacteristics(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_block *block;
	काष्ठा dasd_uid temp_uid;
	पूर्णांक rc, i;
	पूर्णांक पढ़ोonly;
	अचिन्हित दीर्घ value;

	/* setup work queue क्रम validate server*/
	INIT_WORK(&device->kick_validate, dasd_eckd_करो_validate_server);
	/* setup work queue क्रम summary unit check */
	INIT_WORK(&device->suc_work, dasd_alias_handle_summary_unit_check);

	अगर (!ccw_device_is_pathgroup(device->cdev)) अणु
		dev_warn(&device->cdev->dev,
			 "A channel path group could not be established\n");
		वापस -EIO;
	पूर्ण
	अगर (!ccw_device_is_multipath(device->cdev)) अणु
		dev_info(&device->cdev->dev,
			 "The DASD is not operating in multipath mode\n");
	पूर्ण
	अगर (!निजी) अणु
		निजी = kzalloc(माप(*निजी), GFP_KERNEL | GFP_DMA);
		अगर (!निजी) अणु
			dev_warn(&device->cdev->dev,
				 "Allocating memory for private DASD data "
				 "failed\n");
			वापस -ENOMEM;
		पूर्ण
		device->निजी = निजी;
	पूर्ण अन्यथा अणु
		स_रखो(निजी, 0, माप(*निजी));
	पूर्ण
	/* Invalidate status of initial analysis. */
	निजी->init_cqr_status = -1;
	/* Set शेष cache operations. */
	निजी->attrib.operation = DASD_NORMAL_CACHE;
	निजी->attrib.nr_cyl = 0;

	/* Read Configuration Data */
	rc = dasd_eckd_पढ़ो_conf(device);
	अगर (rc)
		जाओ out_err1;

	/* set some शेष values */
	device->शेष_expires = DASD_EXPIRES;
	device->शेष_retries = DASD_RETRIES;
	device->path_thrhld = DASD_ECKD_PATH_THRHLD;
	device->path_पूर्णांकerval = DASD_ECKD_PATH_INTERVAL;

	अगर (निजी->gneq) अणु
		value = 1;
		क्रम (i = 0; i < निजी->gneq->समयout.value; i++)
			value = 10 * value;
		value = value * निजी->gneq->समयout.number;
		/* करो not accept useless values */
		अगर (value != 0 && value <= DASD_EXPIRES_MAX)
			device->शेष_expires = value;
	पूर्ण

	dasd_eckd_get_uid(device, &temp_uid);
	अगर (temp_uid.type == UA_BASE_DEVICE) अणु
		block = dasd_alloc_block();
		अगर (IS_ERR(block)) अणु
			DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
					"could not allocate dasd "
					"block structure");
			rc = PTR_ERR(block);
			जाओ out_err1;
		पूर्ण
		device->block = block;
		block->base = device;
	पूर्ण

	/* रेजिस्टर lcu with alias handling, enable PAV */
	rc = dasd_alias_make_device_known_to_lcu(device);
	अगर (rc)
		जाओ out_err2;

	dasd_eckd_validate_server(device, 0);

	/* device may report dअगरferent configuration data after LCU setup */
	rc = dasd_eckd_पढ़ो_conf(device);
	अगर (rc)
		जाओ out_err3;

	dasd_path_create_kobjects(device);

	/* Read Feature Codes */
	dasd_eckd_पढ़ो_features(device);

	/* Read Volume Inक्रमmation */
	dasd_eckd_पढ़ो_vol_info(device);

	/* Read Extent Pool Inक्रमmation */
	dasd_eckd_पढ़ो_ext_pool_info(device);

	/* Read Device Characteristics */
	rc = dasd_generic_पढ़ो_dev_अक्षरs(device, DASD_ECKD_MAGIC,
					 &निजी->rdc_data, 64);
	अगर (rc) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Read device characteristic failed, rc=%d", rc);
		जाओ out_err3;
	पूर्ण

	अगर ((device->features & DASD_FEATURE_USERAW) &&
	    !(निजी->rdc_data.facilities.RT_in_LR)) अणु
		dev_err(&device->cdev->dev, "The storage server does not "
			"support raw-track access\n");
		rc = -EINVAL;
		जाओ out_err3;
	पूर्ण

	/* find the valid cylinder size */
	अगर (निजी->rdc_data.no_cyl == LV_COMPAT_CYL &&
	    निजी->rdc_data.दीर्घ_no_cyl)
		निजी->real_cyl = निजी->rdc_data.दीर्घ_no_cyl;
	अन्यथा
		निजी->real_cyl = निजी->rdc_data.no_cyl;

	निजी->fcx_max_data = get_fcx_max_data(device);

	पढ़ोonly = dasd_device_is_ro(device);
	अगर (पढ़ोonly)
		set_bit(DASD_FLAG_DEVICE_RO, &device->flags);

	dev_info(&device->cdev->dev, "New DASD %04X/%02X (CU %04X/%02X) "
		 "with %d cylinders, %d heads, %d sectors%s\n",
		 निजी->rdc_data.dev_type,
		 निजी->rdc_data.dev_model,
		 निजी->rdc_data.cu_type,
		 निजी->rdc_data.cu_model.model,
		 निजी->real_cyl,
		 निजी->rdc_data.trk_per_cyl,
		 निजी->rdc_data.sec_per_trk,
		 पढ़ोonly ? ", read-only device" : "");
	वापस 0;

out_err3:
	dasd_alias_disconnect_device_from_lcu(device);
out_err2:
	dasd_मुक्त_block(device->block);
	device->block = शून्य;
out_err1:
	dasd_eckd_clear_conf_data(device);
	dasd_path_हटाओ_kobjects(device);
	kमुक्त(device->निजी);
	device->निजी = शून्य;
	वापस rc;
पूर्ण

अटल व्योम dasd_eckd_uncheck_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	अगर (!निजी)
		वापस;

	dasd_alias_disconnect_device_from_lcu(device);
	निजी->ned = शून्य;
	निजी->sneq = शून्य;
	निजी->vdsneq = शून्य;
	निजी->gneq = शून्य;
	dasd_eckd_clear_conf_data(device);
	dasd_path_हटाओ_kobjects(device);
पूर्ण

अटल काष्ठा dasd_ccw_req *
dasd_eckd_analysis_ccw(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा eckd_count *count_data;
	काष्ठा LO_eckd_data *LO_data;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक cplength, datasize;
	पूर्णांक i;

	cplength = 8;
	datasize = माप(काष्ठा DE_eckd_data) + 2*माप(काष्ठा LO_eckd_data);
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, cplength, datasize, device,
				   शून्य);
	अगर (IS_ERR(cqr))
		वापस cqr;
	ccw = cqr->cpaddr;
	/* Define extent क्रम the first 2 tracks. */
	define_extent(ccw++, cqr->data, 0, 1,
		      DASD_ECKD_CCW_READ_COUNT, device, 0);
	LO_data = cqr->data + माप(काष्ठा DE_eckd_data);
	/* Locate record क्रम the first 4 records on track 0. */
	ccw[-1].flags |= CCW_FLAG_CC;
	locate_record(ccw++, LO_data++, 0, 0, 4,
		      DASD_ECKD_CCW_READ_COUNT, device, 0);

	count_data = निजी->count_area;
	क्रम (i = 0; i < 4; i++) अणु
		ccw[-1].flags |= CCW_FLAG_CC;
		ccw->cmd_code = DASD_ECKD_CCW_READ_COUNT;
		ccw->flags = 0;
		ccw->count = 8;
		ccw->cda = (__u32)(addr_t) count_data;
		ccw++;
		count_data++;
	पूर्ण

	/* Locate record क्रम the first record on track 1. */
	ccw[-1].flags |= CCW_FLAG_CC;
	locate_record(ccw++, LO_data++, 1, 0, 1,
		      DASD_ECKD_CCW_READ_COUNT, device, 0);
	/* Read count ccw. */
	ccw[-1].flags |= CCW_FLAG_CC;
	ccw->cmd_code = DASD_ECKD_CCW_READ_COUNT;
	ccw->flags = 0;
	ccw->count = 8;
	ccw->cda = (__u32)(addr_t) count_data;

	cqr->block = शून्य;
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->retries = 255;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	/* Set flags to suppress output क्रम expected errors */
	set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);

	वापस cqr;
पूर्ण

/* dअगरferentiate between 'no record found' and any other error */
अटल पूर्णांक dasd_eckd_analysis_evaluation(काष्ठा dasd_ccw_req *init_cqr)
अणु
	अक्षर *sense;
	अगर (init_cqr->status == DASD_CQR_DONE)
		वापस INIT_CQR_OK;
	अन्यथा अगर (init_cqr->status == DASD_CQR_NEED_ERP ||
		 init_cqr->status == DASD_CQR_FAILED) अणु
		sense = dasd_get_sense(&init_cqr->irb);
		अगर (sense && (sense[1] & SNS1_NO_REC_FOUND))
			वापस INIT_CQR_UNFORMATTED;
		अन्यथा
			वापस INIT_CQR_ERROR;
	पूर्ण अन्यथा
		वापस INIT_CQR_ERROR;
पूर्ण

/*
 * This is the callback function क्रम the init_analysis cqr. It saves
 * the status of the initial analysis ccw beक्रमe it मुक्तs it and kicks
 * the device to जारी the startup sequence. This will call
 * dasd_eckd_करो_analysis again (अगर the devices has not been marked
 * क्रम deletion in the meanसमय).
 */
अटल व्योम dasd_eckd_analysis_callback(काष्ठा dasd_ccw_req *init_cqr,
					व्योम *data)
अणु
	काष्ठा dasd_device *device = init_cqr->startdev;
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	निजी->init_cqr_status = dasd_eckd_analysis_evaluation(init_cqr);
	dasd_sमुक्त_request(init_cqr, device);
	dasd_kick_device(device);
पूर्ण

अटल पूर्णांक dasd_eckd_start_analysis(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_ccw_req *init_cqr;

	init_cqr = dasd_eckd_analysis_ccw(block->base);
	अगर (IS_ERR(init_cqr))
		वापस PTR_ERR(init_cqr);
	init_cqr->callback = dasd_eckd_analysis_callback;
	init_cqr->callback_data = शून्य;
	init_cqr->expires = 5*HZ;
	/* first try without ERP, so we can later handle unक्रमmatted
	 * devices as special हाल
	 */
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &init_cqr->flags);
	init_cqr->retries = 0;
	dasd_add_request_head(init_cqr);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक dasd_eckd_end_analysis(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_device *device = block->base;
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा eckd_count *count_area;
	अचिन्हित पूर्णांक sb, blk_per_trk;
	पूर्णांक status, i;
	काष्ठा dasd_ccw_req *init_cqr;

	status = निजी->init_cqr_status;
	निजी->init_cqr_status = -1;
	अगर (status == INIT_CQR_ERROR) अणु
		/* try again, this समय with full ERP */
		init_cqr = dasd_eckd_analysis_ccw(device);
		dasd_sleep_on(init_cqr);
		status = dasd_eckd_analysis_evaluation(init_cqr);
		dasd_sमुक्त_request(init_cqr, device);
	पूर्ण

	अगर (device->features & DASD_FEATURE_USERAW) अणु
		block->bp_block = DASD_RAW_BLOCKSIZE;
		blk_per_trk = DASD_RAW_BLOCK_PER_TRACK;
		block->s2b_shअगरt = 3;
		जाओ raw;
	पूर्ण

	अगर (status == INIT_CQR_UNFORMATTED) अणु
		dev_warn(&device->cdev->dev, "The DASD is not formatted\n");
		वापस -EMEDIUMTYPE;
	पूर्ण अन्यथा अगर (status == INIT_CQR_ERROR) अणु
		dev_err(&device->cdev->dev,
			"Detecting the DASD disk layout failed because "
			"of an I/O error\n");
		वापस -EIO;
	पूर्ण

	निजी->uses_cdl = 1;
	/* Check Track 0 क्रम Compatible Disk Layout */
	count_area = शून्य;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (निजी->count_area[i].kl != 4 ||
		    निजी->count_area[i].dl != dasd_eckd_cdl_reclen(i) - 4 ||
		    निजी->count_area[i].cyl != 0 ||
		    निजी->count_area[i].head != count_area_head[i] ||
		    निजी->count_area[i].record != count_area_rec[i]) अणु
			निजी->uses_cdl = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == 3)
		count_area = &निजी->count_area[3];

	अगर (निजी->uses_cdl == 0) अणु
		क्रम (i = 0; i < 5; i++) अणु
			अगर ((निजी->count_area[i].kl != 0) ||
			    (निजी->count_area[i].dl !=
			     निजी->count_area[0].dl) ||
			    निजी->count_area[i].cyl !=  0 ||
			    निजी->count_area[i].head != count_area_head[i] ||
			    निजी->count_area[i].record != count_area_rec[i])
				अवरोध;
		पूर्ण
		अगर (i == 5)
			count_area = &निजी->count_area[0];
	पूर्ण अन्यथा अणु
		अगर (निजी->count_area[3].record == 1)
			dev_warn(&device->cdev->dev,
				 "Track 0 has no records following the VTOC\n");
	पूर्ण

	अगर (count_area != शून्य && count_area->kl == 0) अणु
		/* we found notthing violating our disk layout */
		अगर (dasd_check_blocksize(count_area->dl) == 0)
			block->bp_block = count_area->dl;
	पूर्ण
	अगर (block->bp_block == 0) अणु
		dev_warn(&device->cdev->dev,
			 "The disk layout of the DASD is not supported\n");
		वापस -EMEDIUMTYPE;
	पूर्ण
	block->s2b_shअगरt = 0;	/* bits to shअगरt 512 to get a block */
	क्रम (sb = 512; sb < block->bp_block; sb = sb << 1)
		block->s2b_shअगरt++;

	blk_per_trk = recs_per_track(&निजी->rdc_data, 0, block->bp_block);

raw:
	block->blocks = ((अचिन्हित दीर्घ) निजी->real_cyl *
			  निजी->rdc_data.trk_per_cyl *
			  blk_per_trk);

	dev_info(&device->cdev->dev,
		 "DASD with %u KB/block, %lu KB total size, %u KB/track, "
		 "%s\n", (block->bp_block >> 10),
		 (((अचिन्हित दीर्घ) निजी->real_cyl *
		   निजी->rdc_data.trk_per_cyl *
		   blk_per_trk * (block->bp_block >> 9)) >> 1),
		 ((blk_per_trk * block->bp_block) >> 10),
		 निजी->uses_cdl ?
		 "compatible disk layout" : "linux disk layout");

	वापस 0;
पूर्ण

अटल पूर्णांक dasd_eckd_करो_analysis(काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_eckd_निजी *निजी = block->base->निजी;

	अगर (निजी->init_cqr_status < 0)
		वापस dasd_eckd_start_analysis(block);
	अन्यथा
		वापस dasd_eckd_end_analysis(block);
पूर्ण

अटल पूर्णांक dasd_eckd_basic_to_पढ़ोy(काष्ठा dasd_device *device)
अणु
	वापस dasd_alias_add_device(device);
पूर्ण;

अटल पूर्णांक dasd_eckd_online_to_पढ़ोy(काष्ठा dasd_device *device)
अणु
	अगर (cancel_work_sync(&device->reload_device))
		dasd_put_device(device);
	अगर (cancel_work_sync(&device->kick_validate))
		dasd_put_device(device);

	वापस 0;
पूर्ण;

अटल पूर्णांक dasd_eckd_basic_to_known(काष्ठा dasd_device *device)
अणु
	वापस dasd_alias_हटाओ_device(device);
पूर्ण;

अटल पूर्णांक
dasd_eckd_fill_geometry(काष्ठा dasd_block *block, काष्ठा hd_geometry *geo)
अणु
	काष्ठा dasd_eckd_निजी *निजी = block->base->निजी;

	अगर (dasd_check_blocksize(block->bp_block) == 0) अणु
		geo->sectors = recs_per_track(&निजी->rdc_data,
					      0, block->bp_block);
	पूर्ण
	geo->cylinders = निजी->rdc_data.no_cyl;
	geo->heads = निजी->rdc_data.trk_per_cyl;
	वापस 0;
पूर्ण

/*
 * Build the TCW request क्रम the क्रमmat check
 */
अटल काष्ठा dasd_ccw_req *
dasd_eckd_build_check_tcw(काष्ठा dasd_device *base, काष्ठा क्रमmat_data_t *fdata,
			  पूर्णांक enable_pav, काष्ठा eckd_count *fmt_buffer,
			  पूर्णांक rpt)
अणु
	काष्ठा dasd_eckd_निजी *start_priv;
	काष्ठा dasd_device *startdev = शून्य;
	काष्ठा tidaw *last_tidaw = शून्य;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा itcw *itcw;
	पूर्णांक itcw_size;
	पूर्णांक count;
	पूर्णांक rc;
	पूर्णांक i;

	अगर (enable_pav)
		startdev = dasd_alias_get_start_dev(base);

	अगर (!startdev)
		startdev = base;

	start_priv = startdev->निजी;

	count = rpt * (fdata->stop_unit - fdata->start_unit + 1);

	/*
	 * we're adding 'count' amount of tidaw to the itcw.
	 * calculate the corresponding itcw_size
	 */
	itcw_size = itcw_calc_size(0, count, 0);

	cqr = dasd_fदो_स्मृति_request(DASD_ECKD_MAGIC, 0, itcw_size, startdev);
	अगर (IS_ERR(cqr))
		वापस cqr;

	start_priv->count++;

	itcw = itcw_init(cqr->data, itcw_size, ITCW_OP_READ, 0, count, 0);
	अगर (IS_ERR(itcw)) अणु
		rc = -EINVAL;
		जाओ out_err;
	पूर्ण

	cqr->cpaddr = itcw_get_tcw(itcw);
	rc = prepare_itcw(itcw, fdata->start_unit, fdata->stop_unit,
			  DASD_ECKD_CCW_READ_COUNT_MT, base, startdev, 0, count,
			  माप(काष्ठा eckd_count),
			  count * माप(काष्ठा eckd_count), 0, rpt);
	अगर (rc)
		जाओ out_err;

	क्रम (i = 0; i < count; i++) अणु
		last_tidaw = itcw_add_tidaw(itcw, 0, fmt_buffer++,
					    माप(काष्ठा eckd_count));
		अगर (IS_ERR(last_tidaw)) अणु
			rc = -EINVAL;
			जाओ out_err;
		पूर्ण
	पूर्ण

	last_tidaw->flags |= TIDAW_FLAGS_LAST;
	itcw_finalize(itcw);

	cqr->cpmode = 1;
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->basedev = base;
	cqr->retries = startdev->शेष_retries;
	cqr->expires = startdev->शेष_expires * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	/* Set flags to suppress output क्रम expected errors */
	set_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags);
	set_bit(DASD_CQR_SUPPRESS_IL, &cqr->flags);

	वापस cqr;

out_err:
	dasd_sमुक्त_request(cqr, startdev);

	वापस ERR_PTR(rc);
पूर्ण

/*
 * Build the CCW request क्रम the क्रमmat check
 */
अटल काष्ठा dasd_ccw_req *
dasd_eckd_build_check(काष्ठा dasd_device *base, काष्ठा क्रमmat_data_t *fdata,
		      पूर्णांक enable_pav, काष्ठा eckd_count *fmt_buffer, पूर्णांक rpt)
अणु
	काष्ठा dasd_eckd_निजी *start_priv;
	काष्ठा dasd_eckd_निजी *base_priv;
	काष्ठा dasd_device *startdev = शून्य;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	व्योम *data;
	पूर्णांक cplength, datasize;
	पूर्णांक use_prefix;
	पूर्णांक count;
	पूर्णांक i;

	अगर (enable_pav)
		startdev = dasd_alias_get_start_dev(base);

	अगर (!startdev)
		startdev = base;

	start_priv = startdev->निजी;
	base_priv = base->निजी;

	count = rpt * (fdata->stop_unit - fdata->start_unit + 1);

	use_prefix = base_priv->features.feature[8] & 0x01;

	अगर (use_prefix) अणु
		cplength = 1;
		datasize = माप(काष्ठा PFX_eckd_data);
	पूर्ण अन्यथा अणु
		cplength = 2;
		datasize = माप(काष्ठा DE_eckd_data) +
			माप(काष्ठा LO_eckd_data);
	पूर्ण
	cplength += count;

	cqr = dasd_fदो_स्मृति_request(DASD_ECKD_MAGIC, cplength, datasize, startdev);
	अगर (IS_ERR(cqr))
		वापस cqr;

	start_priv->count++;
	data = cqr->data;
	ccw = cqr->cpaddr;

	अगर (use_prefix) अणु
		prefix_LRE(ccw++, data, fdata->start_unit, fdata->stop_unit,
			   DASD_ECKD_CCW_READ_COUNT, base, startdev, 1, 0,
			   count, 0, 0);
	पूर्ण अन्यथा अणु
		define_extent(ccw++, data, fdata->start_unit, fdata->stop_unit,
			      DASD_ECKD_CCW_READ_COUNT, startdev, 0);

		data += माप(काष्ठा DE_eckd_data);
		ccw[-1].flags |= CCW_FLAG_CC;

		locate_record(ccw++, data, fdata->start_unit, 0, count,
			      DASD_ECKD_CCW_READ_COUNT, base, 0);
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		ccw[-1].flags |= CCW_FLAG_CC;
		ccw->cmd_code = DASD_ECKD_CCW_READ_COUNT;
		ccw->flags = CCW_FLAG_SLI;
		ccw->count = 8;
		ccw->cda = (__u32)(addr_t) fmt_buffer;
		ccw++;
		fmt_buffer++;
	पूर्ण

	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->basedev = base;
	cqr->retries = DASD_RETRIES;
	cqr->expires = startdev->शेष_expires * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	/* Set flags to suppress output क्रम expected errors */
	set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);

	वापस cqr;
पूर्ण

अटल काष्ठा dasd_ccw_req *
dasd_eckd_build_क्रमmat(काष्ठा dasd_device *base, काष्ठा dasd_device *startdev,
		       काष्ठा क्रमmat_data_t *fdata, पूर्णांक enable_pav)
अणु
	काष्ठा dasd_eckd_निजी *base_priv;
	काष्ठा dasd_eckd_निजी *start_priv;
	काष्ठा dasd_ccw_req *fcp;
	काष्ठा eckd_count *ect;
	काष्ठा ch_t address;
	काष्ठा ccw1 *ccw;
	व्योम *data;
	पूर्णांक rpt;
	पूर्णांक cplength, datasize;
	पूर्णांक i, j;
	पूर्णांक पूर्णांकensity = 0;
	पूर्णांक r0_perm;
	पूर्णांक nr_tracks;
	पूर्णांक use_prefix;

	अगर (enable_pav)
		startdev = dasd_alias_get_start_dev(base);

	अगर (!startdev)
		startdev = base;

	start_priv = startdev->निजी;
	base_priv = base->निजी;

	rpt = recs_per_track(&base_priv->rdc_data, 0, fdata->blksize);

	nr_tracks = fdata->stop_unit - fdata->start_unit + 1;

	/*
	 * fdata->पूर्णांकensity is a bit string that tells us what to करो:
	 *   Bit 0: ग_लिखो record zero
	 *   Bit 1: ग_लिखो home address, currently not supported
	 *   Bit 2: invalidate tracks
	 *   Bit 3: use OS/390 compatible disk layout (cdl)
	 *   Bit 4: करो not allow storage subप्रणाली to modअगरy record zero
	 * Only some bit combinations करो make sense.
	 */
	अगर (fdata->पूर्णांकensity & 0x10) अणु
		r0_perm = 0;
		पूर्णांकensity = fdata->पूर्णांकensity & ~0x10;
	पूर्ण अन्यथा अणु
		r0_perm = 1;
		पूर्णांकensity = fdata->पूर्णांकensity;
	पूर्ण

	use_prefix = base_priv->features.feature[8] & 0x01;

	चयन (पूर्णांकensity) अणु
	हाल 0x00:	/* Normal क्रमmat */
	हाल 0x08:	/* Normal क्रमmat, use cdl. */
		cplength = 2 + (rpt*nr_tracks);
		अगर (use_prefix)
			datasize = माप(काष्ठा PFX_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				rpt * nr_tracks * माप(काष्ठा eckd_count);
		अन्यथा
			datasize = माप(काष्ठा DE_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				rpt * nr_tracks * माप(काष्ठा eckd_count);
		अवरोध;
	हाल 0x01:	/* Write record zero and क्रमmat track. */
	हाल 0x09:	/* Write record zero and क्रमmat track, use cdl. */
		cplength = 2 + rpt * nr_tracks;
		अगर (use_prefix)
			datasize = माप(काष्ठा PFX_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				माप(काष्ठा eckd_count) +
				rpt * nr_tracks * माप(काष्ठा eckd_count);
		अन्यथा
			datasize = माप(काष्ठा DE_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				माप(काष्ठा eckd_count) +
				rpt * nr_tracks * माप(काष्ठा eckd_count);
		अवरोध;
	हाल 0x04:	/* Invalidate track. */
	हाल 0x0c:	/* Invalidate track, use cdl. */
		cplength = 3;
		अगर (use_prefix)
			datasize = माप(काष्ठा PFX_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				माप(काष्ठा eckd_count);
		अन्यथा
			datasize = माप(काष्ठा DE_eckd_data) +
				माप(काष्ठा LO_eckd_data) +
				माप(काष्ठा eckd_count);
		अवरोध;
	शेष:
		dev_warn(&startdev->cdev->dev,
			 "An I/O control call used incorrect flags 0x%x\n",
			 fdata->पूर्णांकensity);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	fcp = dasd_fदो_स्मृति_request(DASD_ECKD_MAGIC, cplength, datasize, startdev);
	अगर (IS_ERR(fcp))
		वापस fcp;

	start_priv->count++;
	data = fcp->data;
	ccw = fcp->cpaddr;

	चयन (पूर्णांकensity & ~0x08) अणु
	हाल 0x00: /* Normal क्रमmat. */
		अगर (use_prefix) अणु
			prefix(ccw++, (काष्ठा PFX_eckd_data *) data,
			       fdata->start_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WRITE_CKD, base, startdev);
			/* grant subप्रणाली permission to क्रमmat R0 */
			अगर (r0_perm)
				((काष्ठा PFX_eckd_data *)data)
					->define_extent.ga_extended |= 0x04;
			data += माप(काष्ठा PFX_eckd_data);
		पूर्ण अन्यथा अणु
			define_extent(ccw++, (काष्ठा DE_eckd_data *) data,
				      fdata->start_unit, fdata->stop_unit,
				      DASD_ECKD_CCW_WRITE_CKD, startdev, 0);
			/* grant subप्रणाली permission to क्रमmat R0 */
			अगर (r0_perm)
				((काष्ठा DE_eckd_data *) data)
					->ga_extended |= 0x04;
			data += माप(काष्ठा DE_eckd_data);
		पूर्ण
		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, (काष्ठा LO_eckd_data *) data,
			      fdata->start_unit, 0, rpt*nr_tracks,
			      DASD_ECKD_CCW_WRITE_CKD, base,
			      fdata->blksize);
		data += माप(काष्ठा LO_eckd_data);
		अवरोध;
	हाल 0x01: /* Write record zero + क्रमmat track. */
		अगर (use_prefix) अणु
			prefix(ccw++, (काष्ठा PFX_eckd_data *) data,
			       fdata->start_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WRITE_RECORD_ZERO,
			       base, startdev);
			data += माप(काष्ठा PFX_eckd_data);
		पूर्ण अन्यथा अणु
			define_extent(ccw++, (काष्ठा DE_eckd_data *) data,
			       fdata->start_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WRITE_RECORD_ZERO, startdev, 0);
			data += माप(काष्ठा DE_eckd_data);
		पूर्ण
		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, (काष्ठा LO_eckd_data *) data,
			      fdata->start_unit, 0, rpt * nr_tracks + 1,
			      DASD_ECKD_CCW_WRITE_RECORD_ZERO, base,
			      base->block->bp_block);
		data += माप(काष्ठा LO_eckd_data);
		अवरोध;
	हाल 0x04: /* Invalidate track. */
		अगर (use_prefix) अणु
			prefix(ccw++, (काष्ठा PFX_eckd_data *) data,
			       fdata->start_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WRITE_CKD, base, startdev);
			data += माप(काष्ठा PFX_eckd_data);
		पूर्ण अन्यथा अणु
			define_extent(ccw++, (काष्ठा DE_eckd_data *) data,
			       fdata->start_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WRITE_CKD, startdev, 0);
			data += माप(काष्ठा DE_eckd_data);
		पूर्ण
		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, (काष्ठा LO_eckd_data *) data,
			      fdata->start_unit, 0, 1,
			      DASD_ECKD_CCW_WRITE_CKD, base, 8);
		data += माप(काष्ठा LO_eckd_data);
		अवरोध;
	पूर्ण

	क्रम (j = 0; j < nr_tracks; j++) अणु
		/* calculate cylinder and head क्रम the current track */
		set_ch_t(&address,
			 (fdata->start_unit + j) /
			 base_priv->rdc_data.trk_per_cyl,
			 (fdata->start_unit + j) %
			 base_priv->rdc_data.trk_per_cyl);
		अगर (पूर्णांकensity & 0x01) अणु	/* ग_लिखो record zero */
			ect = (काष्ठा eckd_count *) data;
			data += माप(काष्ठा eckd_count);
			ect->cyl = address.cyl;
			ect->head = address.head;
			ect->record = 0;
			ect->kl = 0;
			ect->dl = 8;
			ccw[-1].flags |= CCW_FLAG_CC;
			ccw->cmd_code = DASD_ECKD_CCW_WRITE_RECORD_ZERO;
			ccw->flags = CCW_FLAG_SLI;
			ccw->count = 8;
			ccw->cda = (__u32)(addr_t) ect;
			ccw++;
		पूर्ण
		अगर ((पूर्णांकensity & ~0x08) & 0x04) अणु	/* erase track */
			ect = (काष्ठा eckd_count *) data;
			data += माप(काष्ठा eckd_count);
			ect->cyl = address.cyl;
			ect->head = address.head;
			ect->record = 1;
			ect->kl = 0;
			ect->dl = 0;
			ccw[-1].flags |= CCW_FLAG_CC;
			ccw->cmd_code = DASD_ECKD_CCW_WRITE_CKD;
			ccw->flags = CCW_FLAG_SLI;
			ccw->count = 8;
			ccw->cda = (__u32)(addr_t) ect;
		पूर्ण अन्यथा अणु		/* ग_लिखो reमुख्यing records */
			क्रम (i = 0; i < rpt; i++) अणु
				ect = (काष्ठा eckd_count *) data;
				data += माप(काष्ठा eckd_count);
				ect->cyl = address.cyl;
				ect->head = address.head;
				ect->record = i + 1;
				ect->kl = 0;
				ect->dl = fdata->blksize;
				/*
				 * Check क्रम special tracks 0-1
				 * when क्रमmatting CDL
				 */
				अगर ((पूर्णांकensity & 0x08) &&
				    address.cyl == 0 && address.head == 0) अणु
					अगर (i < 3) अणु
						ect->kl = 4;
						ect->dl = sizes_trk0[i] - 4;
					पूर्ण
				पूर्ण
				अगर ((पूर्णांकensity & 0x08) &&
				    address.cyl == 0 && address.head == 1) अणु
					ect->kl = 44;
					ect->dl = LABEL_SIZE - 44;
				पूर्ण
				ccw[-1].flags |= CCW_FLAG_CC;
				अगर (i != 0 || j == 0)
					ccw->cmd_code =
						DASD_ECKD_CCW_WRITE_CKD;
				अन्यथा
					ccw->cmd_code =
						DASD_ECKD_CCW_WRITE_CKD_MT;
				ccw->flags = CCW_FLAG_SLI;
				ccw->count = 8;
				ccw->cda = (__u32)(addr_t) ect;
				ccw++;
			पूर्ण
		पूर्ण
	पूर्ण

	fcp->startdev = startdev;
	fcp->memdev = startdev;
	fcp->basedev = base;
	fcp->retries = 256;
	fcp->expires = startdev->शेष_expires * HZ;
	fcp->buildclk = get_tod_घड़ी();
	fcp->status = DASD_CQR_FILLED;

	वापस fcp;
पूर्ण

/*
 * Wrapper function to build a CCW request depending on input data
 */
अटल काष्ठा dasd_ccw_req *
dasd_eckd_क्रमmat_build_ccw_req(काष्ठा dasd_device *base,
			       काष्ठा क्रमmat_data_t *fdata, पूर्णांक enable_pav,
			       पूर्णांक tpm, काष्ठा eckd_count *fmt_buffer, पूर्णांक rpt)
अणु
	काष्ठा dasd_ccw_req *ccw_req;

	अगर (!fmt_buffer) अणु
		ccw_req = dasd_eckd_build_क्रमmat(base, शून्य, fdata, enable_pav);
	पूर्ण अन्यथा अणु
		अगर (tpm)
			ccw_req = dasd_eckd_build_check_tcw(base, fdata,
							    enable_pav,
							    fmt_buffer, rpt);
		अन्यथा
			ccw_req = dasd_eckd_build_check(base, fdata, enable_pav,
							fmt_buffer, rpt);
	पूर्ण

	वापस ccw_req;
पूर्ण

/*
 * Sanity checks on क्रमmat_data
 */
अटल पूर्णांक dasd_eckd_क्रमmat_sanity_checks(काष्ठा dasd_device *base,
					  काष्ठा क्रमmat_data_t *fdata)
अणु
	काष्ठा dasd_eckd_निजी *निजी = base->निजी;

	अगर (fdata->start_unit >=
	    (निजी->real_cyl * निजी->rdc_data.trk_per_cyl)) अणु
		dev_warn(&base->cdev->dev,
			 "Start track number %u used in formatting is too big\n",
			 fdata->start_unit);
		वापस -EINVAL;
	पूर्ण
	अगर (fdata->stop_unit >=
	    (निजी->real_cyl * निजी->rdc_data.trk_per_cyl)) अणु
		dev_warn(&base->cdev->dev,
			 "Stop track number %u used in formatting is too big\n",
			 fdata->stop_unit);
		वापस -EINVAL;
	पूर्ण
	अगर (fdata->start_unit > fdata->stop_unit) अणु
		dev_warn(&base->cdev->dev,
			 "Start track %u used in formatting exceeds end track\n",
			 fdata->start_unit);
		वापस -EINVAL;
	पूर्ण
	अगर (dasd_check_blocksize(fdata->blksize) != 0) अणु
		dev_warn(&base->cdev->dev,
			 "The DASD cannot be formatted with block size %u\n",
			 fdata->blksize);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function will process क्रमmat_data originally coming from an IOCTL
 */
अटल पूर्णांक dasd_eckd_क्रमmat_process_data(काष्ठा dasd_device *base,
					 काष्ठा क्रमmat_data_t *fdata,
					 पूर्णांक enable_pav, पूर्णांक tpm,
					 काष्ठा eckd_count *fmt_buffer, पूर्णांक rpt,
					 काष्ठा irb *irb)
अणु
	काष्ठा dasd_eckd_निजी *निजी = base->निजी;
	काष्ठा dasd_ccw_req *cqr, *n;
	काष्ठा list_head क्रमmat_queue;
	काष्ठा dasd_device *device;
	अक्षर *sense = शून्य;
	पूर्णांक old_start, old_stop, क्रमmat_step;
	पूर्णांक step, retry;
	पूर्णांक rc;

	rc = dasd_eckd_क्रमmat_sanity_checks(base, fdata);
	अगर (rc)
		वापस rc;

	INIT_LIST_HEAD(&क्रमmat_queue);

	old_start = fdata->start_unit;
	old_stop = fdata->stop_unit;

	अगर (!tpm && fmt_buffer != शून्य) अणु
		/* Command Mode / Format Check */
		क्रमmat_step = 1;
	पूर्ण अन्यथा अगर (tpm && fmt_buffer != शून्य) अणु
		/* Transport Mode / Format Check */
		क्रमmat_step = DASD_CQR_MAX_CCW / rpt;
	पूर्ण अन्यथा अणु
		/* Normal Formatting */
		क्रमmat_step = DASD_CQR_MAX_CCW /
			recs_per_track(&निजी->rdc_data, 0, fdata->blksize);
	पूर्ण

	करो अणु
		retry = 0;
		जबतक (fdata->start_unit <= old_stop) अणु
			step = fdata->stop_unit - fdata->start_unit + 1;
			अगर (step > क्रमmat_step) अणु
				fdata->stop_unit =
					fdata->start_unit + क्रमmat_step - 1;
			पूर्ण

			cqr = dasd_eckd_क्रमmat_build_ccw_req(base, fdata,
							     enable_pav, tpm,
							     fmt_buffer, rpt);
			अगर (IS_ERR(cqr)) अणु
				rc = PTR_ERR(cqr);
				अगर (rc == -ENOMEM) अणु
					अगर (list_empty(&क्रमmat_queue))
						जाओ out;
					/*
					 * not enough memory available, start
					 * requests retry after first requests
					 * were finished
					 */
					retry = 1;
					अवरोध;
				पूर्ण
				जाओ out_err;
			पूर्ण
			list_add_tail(&cqr->blocklist, &क्रमmat_queue);

			अगर (fmt_buffer) अणु
				step = fdata->stop_unit - fdata->start_unit + 1;
				fmt_buffer += rpt * step;
			पूर्ण
			fdata->start_unit = fdata->stop_unit + 1;
			fdata->stop_unit = old_stop;
		पूर्ण

		rc = dasd_sleep_on_queue(&क्रमmat_queue);

out_err:
		list_क्रम_each_entry_safe(cqr, n, &क्रमmat_queue, blocklist) अणु
			device = cqr->startdev;
			निजी = device->निजी;

			अगर (cqr->status == DASD_CQR_FAILED) अणु
				/*
				 * Only get sense data अगर called by क्रमmat
				 * check
				 */
				अगर (fmt_buffer && irb) अणु
					sense = dasd_get_sense(&cqr->irb);
					स_नकल(irb, &cqr->irb, माप(*irb));
				पूर्ण
				rc = -EIO;
			पूर्ण
			list_del_init(&cqr->blocklist);
			dasd_fमुक्त_request(cqr, device);
			निजी->count--;
		पूर्ण

		अगर (rc && rc != -EIO)
			जाओ out;
		अगर (rc == -EIO) अणु
			/*
			 * In हाल fewer than the expected records are on the
			 * track, we will most likely get a 'No Record Found'
			 * error (in command mode) or a 'File Protected' error
			 * (in transport mode). Those particular हालs shouldn't
			 * pass the -EIO to the IOCTL, thereक्रमe reset the rc
			 * and जारी.
			 */
			अगर (sense &&
			    (sense[1] & SNS1_NO_REC_FOUND ||
			     sense[1] & SNS1_खाता_PROTECTED))
				retry = 1;
			अन्यथा
				जाओ out;
		पूर्ण

	पूर्ण जबतक (retry);

out:
	fdata->start_unit = old_start;
	fdata->stop_unit = old_stop;

	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_क्रमmat_device(काष्ठा dasd_device *base,
				   काष्ठा क्रमmat_data_t *fdata, पूर्णांक enable_pav)
अणु
	वापस dasd_eckd_क्रमmat_process_data(base, fdata, enable_pav, 0, शून्य,
					     0, शून्य);
पूर्ण

अटल bool test_and_set_क्रमmat_track(काष्ठा dasd_क्रमmat_entry *to_क्रमmat,
				      काष्ठा dasd_block *block)
अणु
	काष्ठा dasd_क्रमmat_entry *क्रमmat;
	अचिन्हित दीर्घ flags;
	bool rc = false;

	spin_lock_irqsave(&block->क्रमmat_lock, flags);
	list_क्रम_each_entry(क्रमmat, &block->क्रमmat_list, list) अणु
		अगर (क्रमmat->track == to_क्रमmat->track) अणु
			rc = true;
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_tail(&to_क्रमmat->list, &block->क्रमmat_list);

out:
	spin_unlock_irqrestore(&block->क्रमmat_lock, flags);
	वापस rc;
पूर्ण

अटल व्योम clear_क्रमmat_track(काष्ठा dasd_क्रमmat_entry *क्रमmat,
			      काष्ठा dasd_block *block)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&block->क्रमmat_lock, flags);
	list_del_init(&क्रमmat->list);
	spin_unlock_irqrestore(&block->क्रमmat_lock, flags);
पूर्ण

/*
 * Callback function to मुक्त ESE क्रमmat requests.
 */
अटल व्योम dasd_eckd_ese_क्रमmat_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	काष्ठा dasd_device *device = cqr->startdev;
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_क्रमmat_entry *क्रमmat = data;

	clear_क्रमmat_track(क्रमmat, cqr->basedev->block);
	निजी->count--;
	dasd_fमुक्त_request(cqr, device);
पूर्ण

अटल काष्ठा dasd_ccw_req *
dasd_eckd_ese_क्रमmat(काष्ठा dasd_device *startdev, काष्ठा dasd_ccw_req *cqr,
		     काष्ठा irb *irb)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	काष्ठा dasd_क्रमmat_entry *क्रमmat;
	काष्ठा क्रमmat_data_t fdata;
	अचिन्हित पूर्णांक recs_per_trk;
	काष्ठा dasd_ccw_req *fcqr;
	काष्ठा dasd_device *base;
	काष्ठा dasd_block *block;
	अचिन्हित पूर्णांक blksize;
	काष्ठा request *req;
	sector_t first_trk;
	sector_t last_trk;
	sector_t curr_trk;
	पूर्णांक rc;

	req = cqr->callback_data;
	block = cqr->block;
	base = block->base;
	निजी = base->निजी;
	blksize = block->bp_block;
	recs_per_trk = recs_per_track(&निजी->rdc_data, 0, blksize);
	क्रमmat = &startdev->क्रमmat_entry;

	first_trk = blk_rq_pos(req) >> block->s2b_shअगरt;
	sector_भाग(first_trk, recs_per_trk);
	last_trk =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	sector_भाग(last_trk, recs_per_trk);
	rc = dasd_eckd_track_from_irb(irb, base, &curr_trk);
	अगर (rc)
		वापस ERR_PTR(rc);

	अगर (curr_trk < first_trk || curr_trk > last_trk) अणु
		DBF_DEV_EVENT(DBF_WARNING, startdev,
			      "ESE error track %llu not within range %llu - %llu\n",
			      curr_trk, first_trk, last_trk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	क्रमmat->track = curr_trk;
	/* test अगर track is alपढ़ोy in क्रमmatting by another thपढ़ो */
	अगर (test_and_set_क्रमmat_track(क्रमmat, block))
		वापस ERR_PTR(-EEXIST);

	fdata.start_unit = curr_trk;
	fdata.stop_unit = curr_trk;
	fdata.blksize = blksize;
	fdata.पूर्णांकensity = निजी->uses_cdl ? DASD_FMT_INT_COMPAT : 0;

	rc = dasd_eckd_क्रमmat_sanity_checks(base, &fdata);
	अगर (rc)
		वापस ERR_PTR(-EINVAL);

	/*
	 * We're building the request with PAV disabled as we're reusing
	 * the क्रमmer startdev.
	 */
	fcqr = dasd_eckd_build_क्रमmat(base, startdev, &fdata, 0);
	अगर (IS_ERR(fcqr))
		वापस fcqr;

	fcqr->callback = dasd_eckd_ese_क्रमmat_cb;
	fcqr->callback_data = (व्योम *) क्रमmat;

	वापस fcqr;
पूर्ण

/*
 * When data is पढ़ो from an unक्रमmatted area of an ESE volume, this function
 * वापसs zeroed data and thereby mimics a पढ़ो of zero data.
 *
 * The first unक्रमmatted track is the one that got the NRF error, the address is
 * encoded in the sense data.
 *
 * All tracks beक्रमe have वापसed valid data and should not be touched.
 * All tracks after the unक्रमmatted track might be क्रमmatted or not. This is
 * currently not known, remember the processed data and वापस the reमुख्यder of
 * the request to the blocklayer in __dasd_cleanup_cqr().
 */
अटल पूर्णांक dasd_eckd_ese_पढ़ो(काष्ठा dasd_ccw_req *cqr, काष्ठा irb *irb)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	sector_t first_trk, last_trk;
	sector_t first_blk, last_blk;
	अचिन्हित पूर्णांक blksize, off;
	अचिन्हित पूर्णांक recs_per_trk;
	काष्ठा dasd_device *base;
	काष्ठा req_iterator iter;
	काष्ठा dasd_block *block;
	अचिन्हित पूर्णांक skip_block;
	अचिन्हित पूर्णांक blk_count;
	काष्ठा request *req;
	काष्ठा bio_vec bv;
	sector_t curr_trk;
	sector_t end_blk;
	अक्षर *dst;
	पूर्णांक rc;

	req = (काष्ठा request *) cqr->callback_data;
	base = cqr->block->base;
	blksize = base->block->bp_block;
	block =  cqr->block;
	निजी = base->निजी;
	skip_block = 0;
	blk_count = 0;

	recs_per_trk = recs_per_track(&निजी->rdc_data, 0, blksize);
	first_trk = first_blk = blk_rq_pos(req) >> block->s2b_shअगरt;
	sector_भाग(first_trk, recs_per_trk);
	last_trk = last_blk =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	sector_भाग(last_trk, recs_per_trk);
	rc = dasd_eckd_track_from_irb(irb, base, &curr_trk);
	अगर (rc)
		वापस rc;

	/* sanity check अगर the current track from sense data is valid */
	अगर (curr_trk < first_trk || curr_trk > last_trk) अणु
		DBF_DEV_EVENT(DBF_WARNING, base,
			      "ESE error track %llu not within range %llu - %llu\n",
			      curr_trk, first_trk, last_trk);
		वापस -EINVAL;
	पूर्ण

	/*
	 * अगर not the first track got the NRF error we have to skip over valid
	 * blocks
	 */
	अगर (curr_trk != first_trk)
		skip_block = curr_trk * recs_per_trk - first_blk;

	/* we have no inक्रमmation beyond the current track */
	end_blk = (curr_trk + 1) * recs_per_trk;

	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			अगर (first_blk + blk_count >= end_blk) अणु
				cqr->proc_bytes = blk_count * blksize;
				वापस 0;
			पूर्ण
			अगर (dst && !skip_block) अणु
				dst += off;
				स_रखो(dst, 0, blksize);
			पूर्ण अन्यथा अणु
				skip_block--;
			पूर्ण
			blk_count++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Helper function to count consecutive records of a single track.
 */
अटल पूर्णांक dasd_eckd_count_records(काष्ठा eckd_count *fmt_buffer, पूर्णांक start,
				   पूर्णांक max)
अणु
	पूर्णांक head;
	पूर्णांक i;

	head = fmt_buffer[start].head;

	/*
	 * There are 3 conditions where we stop counting:
	 * - अगर data reoccurs (same head and record may reoccur), which may
	 *   happen due to the way DASD_ECKD_CCW_READ_COUNT works
	 * - when the head changes, because we're iterating over several tracks
	 *   then (DASD_ECKD_CCW_READ_COUNT_MT)
	 * - when we've reached the end of sensible data in the buffer (the
	 *   record will be 0 then)
	 */
	क्रम (i = start; i < max; i++) अणु
		अगर (i > start) अणु
			अगर ((fmt_buffer[i].head == head &&
			    fmt_buffer[i].record == 1) ||
			    fmt_buffer[i].head != head ||
			    fmt_buffer[i].record == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस i - start;
पूर्ण

/*
 * Evaluate a given range of tracks. Data like number of records, blocksize,
 * record ids, and key length are compared with expected data.
 *
 * If a mismatch occurs, the corresponding error bit is set, as well as
 * additional inक्रमmation, depending on the error.
 */
अटल व्योम dasd_eckd_क्रमmat_evaluate_tracks(काष्ठा eckd_count *fmt_buffer,
					     काष्ठा क्रमmat_check_t *cdata,
					     पूर्णांक rpt_max, पूर्णांक rpt_exp,
					     पूर्णांक trk_per_cyl, पूर्णांक tpm)
अणु
	काष्ठा ch_t geo;
	पूर्णांक max_entries;
	पूर्णांक count = 0;
	पूर्णांक trkcount;
	पूर्णांक blksize;
	पूर्णांक pos = 0;
	पूर्णांक i, j;
	पूर्णांक kl;

	trkcount = cdata->expect.stop_unit - cdata->expect.start_unit + 1;
	max_entries = trkcount * rpt_max;

	क्रम (i = cdata->expect.start_unit; i <= cdata->expect.stop_unit; i++) अणु
		/* Calculate the correct next starting position in the buffer */
		अगर (tpm) अणु
			जबतक (fmt_buffer[pos].record == 0 &&
			       fmt_buffer[pos].dl == 0) अणु
				अगर (pos++ > max_entries)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i != cdata->expect.start_unit)
				pos += rpt_max - count;
		पूर्ण

		/* Calculate the expected geo values क्रम the current track */
		set_ch_t(&geo, i / trk_per_cyl, i % trk_per_cyl);

		/* Count and check number of records */
		count = dasd_eckd_count_records(fmt_buffer, pos, pos + rpt_max);

		अगर (count < rpt_exp) अणु
			cdata->result = DASD_FMT_ERR_TOO_FEW_RECORDS;
			अवरोध;
		पूर्ण
		अगर (count > rpt_exp) अणु
			cdata->result = DASD_FMT_ERR_TOO_MANY_RECORDS;
			अवरोध;
		पूर्ण

		क्रम (j = 0; j < count; j++, pos++) अणु
			blksize = cdata->expect.blksize;
			kl = 0;

			/*
			 * Set special values when checking CDL क्रमmatted
			 * devices.
			 */
			अगर ((cdata->expect.पूर्णांकensity & 0x08) &&
			    geo.cyl == 0 && geo.head == 0) अणु
				अगर (j < 3) अणु
					blksize = sizes_trk0[j] - 4;
					kl = 4;
				पूर्ण
			पूर्ण
			अगर ((cdata->expect.पूर्णांकensity & 0x08) &&
			    geo.cyl == 0 && geo.head == 1) अणु
				blksize = LABEL_SIZE - 44;
				kl = 44;
			पूर्ण

			/* Check blocksize */
			अगर (fmt_buffer[pos].dl != blksize) अणु
				cdata->result = DASD_FMT_ERR_BLKSIZE;
				जाओ out;
			पूर्ण
			/* Check अगर key length is 0 */
			अगर (fmt_buffer[pos].kl != kl) अणु
				cdata->result = DASD_FMT_ERR_KEY_LENGTH;
				जाओ out;
			पूर्ण
			/* Check अगर record_id is correct */
			अगर (fmt_buffer[pos].cyl != geo.cyl ||
			    fmt_buffer[pos].head != geo.head ||
			    fmt_buffer[pos].record != (j + 1)) अणु
				cdata->result = DASD_FMT_ERR_RECORD_ID;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	/*
	 * In हाल of no errors, we need to decrease by one
	 * to get the correct positions.
	 */
	अगर (!cdata->result) अणु
		i--;
		pos--;
	पूर्ण

	cdata->unit = i;
	cdata->num_records = count;
	cdata->rec = fmt_buffer[pos].record;
	cdata->blksize = fmt_buffer[pos].dl;
	cdata->key_length = fmt_buffer[pos].kl;
पूर्ण

/*
 * Check the क्रमmat of a range of tracks of a DASD.
 */
अटल पूर्णांक dasd_eckd_check_device_क्रमmat(काष्ठा dasd_device *base,
					 काष्ठा क्रमmat_check_t *cdata,
					 पूर्णांक enable_pav)
अणु
	काष्ठा dasd_eckd_निजी *निजी = base->निजी;
	काष्ठा eckd_count *fmt_buffer;
	काष्ठा irb irb;
	पूर्णांक rpt_max, rpt_exp;
	पूर्णांक fmt_buffer_size;
	पूर्णांक trk_per_cyl;
	पूर्णांक trkcount;
	पूर्णांक tpm = 0;
	पूर्णांक rc;

	trk_per_cyl = निजी->rdc_data.trk_per_cyl;

	/* Get maximum and expected amount of records per track */
	rpt_max = recs_per_track(&निजी->rdc_data, 0, 512) + 1;
	rpt_exp = recs_per_track(&निजी->rdc_data, 0, cdata->expect.blksize);

	trkcount = cdata->expect.stop_unit - cdata->expect.start_unit + 1;
	fmt_buffer_size = trkcount * rpt_max * माप(काष्ठा eckd_count);

	fmt_buffer = kzalloc(fmt_buffer_size, GFP_KERNEL | GFP_DMA);
	अगर (!fmt_buffer)
		वापस -ENOMEM;

	/*
	 * A certain FICON feature subset is needed to operate in transport
	 * mode. Additionally, the support क्रम transport mode is implicitly
	 * checked by comparing the buffer size with fcx_max_data. As दीर्घ as
	 * the buffer size is smaller we can operate in transport mode and
	 * process multiple tracks. If not, only one track at once is being
	 * processed using command mode.
	 */
	अगर ((निजी->features.feature[40] & 0x04) &&
	    fmt_buffer_size <= निजी->fcx_max_data)
		tpm = 1;

	rc = dasd_eckd_क्रमmat_process_data(base, &cdata->expect, enable_pav,
					   tpm, fmt_buffer, rpt_max, &irb);
	अगर (rc && rc != -EIO)
		जाओ out;
	अगर (rc == -EIO) अणु
		/*
		 * If our first attempt with transport mode enabled comes back
		 * with an incorrect length error, we're going to retry the
		 * check with command mode.
		 */
		अगर (tpm && scsw_cstat(&irb.scsw) == 0x40) अणु
			tpm = 0;
			rc = dasd_eckd_क्रमmat_process_data(base, &cdata->expect,
							   enable_pav, tpm,
							   fmt_buffer, rpt_max,
							   &irb);
			अगर (rc)
				जाओ out;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण

	dasd_eckd_क्रमmat_evaluate_tracks(fmt_buffer, cdata, rpt_max, rpt_exp,
					 trk_per_cyl, tpm);

out:
	kमुक्त(fmt_buffer);

	वापस rc;
पूर्ण

अटल व्योम dasd_eckd_handle_terminated_request(काष्ठा dasd_ccw_req *cqr)
अणु
	अगर (cqr->retries < 0) अणु
		cqr->status = DASD_CQR_FAILED;
		वापस;
	पूर्ण
	cqr->status = DASD_CQR_FILLED;
	अगर (cqr->block && (cqr->startdev != cqr->block->base)) अणु
		dasd_eckd_reset_ccw_to_base_io(cqr);
		cqr->startdev = cqr->block->base;
		cqr->lpm = dasd_path_get_opm(cqr->block->base);
	पूर्ण
पूर्ण;

अटल dasd_erp_fn_t
dasd_eckd_erp_action(काष्ठा dasd_ccw_req * cqr)
अणु
	काष्ठा dasd_device *device = (काष्ठा dasd_device *) cqr->startdev;
	काष्ठा ccw_device *cdev = device->cdev;

	चयन (cdev->id.cu_type) अणु
	हाल 0x3990:
	हाल 0x2105:
	हाल 0x2107:
	हाल 0x1750:
		वापस dasd_3990_erp_action;
	हाल 0x9343:
	हाल 0x3880:
	शेष:
		वापस dasd_शेष_erp_action;
	पूर्ण
पूर्ण

अटल dasd_erp_fn_t
dasd_eckd_erp_postaction(काष्ठा dasd_ccw_req * cqr)
अणु
	वापस dasd_शेष_erp_postaction;
पूर्ण

अटल व्योम dasd_eckd_check_क्रम_device_change(काष्ठा dasd_device *device,
					      काष्ठा dasd_ccw_req *cqr,
					      काष्ठा irb *irb)
अणु
	अक्षर mask;
	अक्षर *sense = शून्य;
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	/* first of all check क्रम state change pending पूर्णांकerrupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	अगर ((scsw_dstat(&irb->scsw) & mask) == mask) अणु
		/*
		 * क्रम alias only, not in offline processing
		 * and only अगर not suspended
		 */
		अगर (!device->block && निजी->lcu &&
		    device->state == DASD_STATE_ONLINE &&
		    !test_bit(DASD_FLAG_OFFLINE, &device->flags) &&
		    !test_bit(DASD_FLAG_SUSPENDED, &device->flags)) अणु
			/* schedule worker to reload device */
			dasd_reload_device(device);
		पूर्ण
		dasd_generic_handle_state_change(device);
		वापस;
	पूर्ण

	sense = dasd_get_sense(irb);
	अगर (!sense)
		वापस;

	/* summary unit check */
	अगर ((sense[27] & DASD_SENSE_BIT_0) && (sense[7] == 0x0D) &&
	    (scsw_dstat(&irb->scsw) & DEV_STAT_UNIT_CHECK)) अणु
		अगर (test_and_set_bit(DASD_FLAG_SUC, &device->flags)) अणु
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "eckd suc: device already notified");
			वापस;
		पूर्ण
		sense = dasd_get_sense(irb);
		अगर (!sense) अणु
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				      "eckd suc: no reason code available");
			clear_bit(DASD_FLAG_SUC, &device->flags);
			वापस;

		पूर्ण
		निजी->suc_reason = sense[8];
		DBF_DEV_EVENT(DBF_NOTICE, device, "%s %x",
			      "eckd handle summary unit check: reason",
			      निजी->suc_reason);
		dasd_get_device(device);
		अगर (!schedule_work(&device->suc_work))
			dasd_put_device(device);

		वापस;
	पूर्ण

	/* service inक्रमmation message SIM */
	अगर (!cqr && !(sense[27] & DASD_SENSE_BIT_0) &&
	    ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)) अणु
		dasd_3990_erp_handle_sim(device, sense);
		वापस;
	पूर्ण

	/* loss of device reservation is handled via base devices only
	 * as alias devices may be used with several bases
	 */
	अगर (device->block && (sense[27] & DASD_SENSE_BIT_0) &&
	    (sense[7] == 0x3F) &&
	    (scsw_dstat(&irb->scsw) & DEV_STAT_UNIT_CHECK) &&
	    test_bit(DASD_FLAG_IS_RESERVED, &device->flags)) अणु
		अगर (device->features & DASD_FEATURE_FAILONSLCK)
			set_bit(DASD_FLAG_LOCK_STOLEN, &device->flags);
		clear_bit(DASD_FLAG_IS_RESERVED, &device->flags);
		dev_err(&device->cdev->dev,
			"The device reservation was lost\n");
	पूर्ण
पूर्ण

अटल पूर्णांक dasd_eckd_ras_sanity_checks(काष्ठा dasd_device *device,
				       अचिन्हित पूर्णांक first_trk,
				       अचिन्हित पूर्णांक last_trk)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	अचिन्हित पूर्णांक trks_per_vol;
	पूर्णांक rc = 0;

	trks_per_vol = निजी->real_cyl * निजी->rdc_data.trk_per_cyl;

	अगर (first_trk >= trks_per_vol) अणु
		dev_warn(&device->cdev->dev,
			 "Start track number %u used in the space release command is too big\n",
			 first_trk);
		rc = -EINVAL;
	पूर्ण अन्यथा अगर (last_trk >= trks_per_vol) अणु
		dev_warn(&device->cdev->dev,
			 "Stop track number %u used in the space release command is too big\n",
			 last_trk);
		rc = -EINVAL;
	पूर्ण अन्यथा अगर (first_trk > last_trk) अणु
		dev_warn(&device->cdev->dev,
			 "Start track %u used in the space release command exceeds the end track\n",
			 first_trk);
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Helper function to count the amount of involved extents within a given range
 * with extent alignment in mind.
 */
अटल पूर्णांक count_exts(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to, पूर्णांक trks_per_ext)
अणु
	पूर्णांक cur_pos = 0;
	पूर्णांक count = 0;
	पूर्णांक पंचांगp;

	अगर (from == to)
		वापस 1;

	/* Count first partial extent */
	अगर (from % trks_per_ext != 0) अणु
		पंचांगp = from + trks_per_ext - (from % trks_per_ext) - 1;
		अगर (पंचांगp > to)
			पंचांगp = to;
		cur_pos = पंचांगp - from + 1;
		count++;
	पूर्ण
	/* Count full extents */
	अगर (to - (from + cur_pos) + 1 >= trks_per_ext) अणु
		पंचांगp = to - ((to - trks_per_ext + 1) % trks_per_ext);
		count += (पंचांगp - (from + cur_pos) + 1) / trks_per_ext;
		cur_pos = पंचांगp;
	पूर्ण
	/* Count last partial extent */
	अगर (cur_pos < to)
		count++;

	वापस count;
पूर्ण

/*
 * Release allocated space क्रम a given range or an entire volume.
 */
अटल काष्ठा dasd_ccw_req *
dasd_eckd_dso_ras(काष्ठा dasd_device *device, काष्ठा dasd_block *block,
		  काष्ठा request *req, अचिन्हित पूर्णांक first_trk,
		  अचिन्हित पूर्णांक last_trk, पूर्णांक by_extent)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_dso_ras_ext_range *ras_range;
	काष्ठा dasd_rssd_features *features;
	काष्ठा dasd_dso_ras_data *ras_data;
	u16 heads, beg_head, end_head;
	पूर्णांक cur_to_trk, cur_from_trk;
	काष्ठा dasd_ccw_req *cqr;
	u32 beg_cyl, end_cyl;
	काष्ठा ccw1 *ccw;
	पूर्णांक trks_per_ext;
	माप_प्रकार ras_size;
	माप_प्रकार size;
	पूर्णांक nr_exts;
	व्योम *rq;
	पूर्णांक i;

	अगर (dasd_eckd_ras_sanity_checks(device, first_trk, last_trk))
		वापस ERR_PTR(-EINVAL);

	rq = req ? blk_mq_rq_to_pdu(req) : शून्य;

	features = &निजी->features;

	trks_per_ext = dasd_eckd_ext_size(device) * निजी->rdc_data.trk_per_cyl;
	nr_exts = 0;
	अगर (by_extent)
		nr_exts = count_exts(first_trk, last_trk, trks_per_ext);
	ras_size = माप(*ras_data);
	size = ras_size + (nr_exts * माप(*ras_range));

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1, size, device, rq);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate RAS request");
		वापस cqr;
	पूर्ण

	ras_data = cqr->data;
	स_रखो(ras_data, 0, size);

	ras_data->order = DSO_ORDER_RAS;
	ras_data->flags.vol_type = 0; /* CKD volume */
	/* Release specअगरied extents or entire volume */
	ras_data->op_flags.by_extent = by_extent;
	/*
	 * This bit guarantees initialisation of tracks within an extent that is
	 * not fully specअगरied, but is only supported with a certain feature
	 * subset.
	 */
	ras_data->op_flags.guarantee_init = !!(features->feature[56] & 0x01);
	ras_data->lss = निजी->ned->ID;
	ras_data->dev_addr = निजी->ned->unit_addr;
	ras_data->nr_exts = nr_exts;

	अगर (by_extent) अणु
		heads = निजी->rdc_data.trk_per_cyl;
		cur_from_trk = first_trk;
		cur_to_trk = first_trk + trks_per_ext -
			(first_trk % trks_per_ext) - 1;
		अगर (cur_to_trk > last_trk)
			cur_to_trk = last_trk;
		ras_range = (काष्ठा dasd_dso_ras_ext_range *)(cqr->data + ras_size);

		क्रम (i = 0; i < nr_exts; i++) अणु
			beg_cyl = cur_from_trk / heads;
			beg_head = cur_from_trk % heads;
			end_cyl = cur_to_trk / heads;
			end_head = cur_to_trk % heads;

			set_ch_t(&ras_range->beg_ext, beg_cyl, beg_head);
			set_ch_t(&ras_range->end_ext, end_cyl, end_head);

			cur_from_trk = cur_to_trk + 1;
			cur_to_trk = cur_from_trk + trks_per_ext - 1;
			अगर (cur_to_trk > last_trk)
				cur_to_trk = last_trk;
			ras_range++;
		पूर्ण
	पूर्ण

	ccw = cqr->cpaddr;
	ccw->cda = (__u32)(addr_t)cqr->data;
	ccw->cmd_code = DASD_ECKD_CCW_DSO;
	ccw->count = size;

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = block;
	cqr->retries = 256;
	cqr->expires = device->शेष_expires * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	वापस cqr;
पूर्ण

अटल पूर्णांक dasd_eckd_release_space_full(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;

	cqr = dasd_eckd_dso_ras(device, शून्य, शून्य, 0, 0, 0);
	अगर (IS_ERR(cqr))
		वापस PTR_ERR(cqr);

	rc = dasd_sleep_on_पूर्णांकerruptible(cqr);

	dasd_sमुक्त_request(cqr, cqr->memdev);

	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_release_space_trks(काष्ठा dasd_device *device,
					अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_block *block = device->block;
	काष्ठा dasd_ccw_req *cqr, *n;
	काष्ठा list_head ras_queue;
	अचिन्हित पूर्णांक device_exts;
	पूर्णांक trks_per_ext;
	पूर्णांक stop, step;
	पूर्णांक cur_pos;
	पूर्णांक rc = 0;
	पूर्णांक retry;

	INIT_LIST_HEAD(&ras_queue);

	device_exts = निजी->real_cyl / dasd_eckd_ext_size(device);
	trks_per_ext = dasd_eckd_ext_size(device) * निजी->rdc_data.trk_per_cyl;

	/* Make sure device limits are not exceeded */
	step = trks_per_ext * min(device_exts, DASD_ECKD_RAS_EXTS_MAX);
	cur_pos = from;

	करो अणु
		retry = 0;
		जबतक (cur_pos < to) अणु
			stop = cur_pos + step -
				((cur_pos + step) % trks_per_ext) - 1;
			अगर (stop > to)
				stop = to;

			cqr = dasd_eckd_dso_ras(device, शून्य, शून्य, cur_pos, stop, 1);
			अगर (IS_ERR(cqr)) अणु
				rc = PTR_ERR(cqr);
				अगर (rc == -ENOMEM) अणु
					अगर (list_empty(&ras_queue))
						जाओ out;
					retry = 1;
					अवरोध;
				पूर्ण
				जाओ err_out;
			पूर्ण

			spin_lock_irq(&block->queue_lock);
			list_add_tail(&cqr->blocklist, &ras_queue);
			spin_unlock_irq(&block->queue_lock);
			cur_pos = stop + 1;
		पूर्ण

		rc = dasd_sleep_on_queue_पूर्णांकerruptible(&ras_queue);

err_out:
		list_क्रम_each_entry_safe(cqr, n, &ras_queue, blocklist) अणु
			device = cqr->startdev;
			निजी = device->निजी;

			spin_lock_irq(&block->queue_lock);
			list_del_init(&cqr->blocklist);
			spin_unlock_irq(&block->queue_lock);
			dasd_sमुक्त_request(cqr, device);
			निजी->count--;
		पूर्ण
	पूर्ण जबतक (retry);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_release_space(काष्ठा dasd_device *device,
				   काष्ठा क्रमmat_data_t *rdata)
अणु
	अगर (rdata->पूर्णांकensity & DASD_FMT_INT_ESE_FULL)
		वापस dasd_eckd_release_space_full(device);
	अन्यथा अगर (rdata->पूर्णांकensity == 0)
		वापस dasd_eckd_release_space_trks(device, rdata->start_unit,
						    rdata->stop_unit);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_cp_cmd_single(
					       काष्ठा dasd_device *startdev,
					       काष्ठा dasd_block *block,
					       काष्ठा request *req,
					       sector_t first_rec,
					       sector_t last_rec,
					       sector_t first_trk,
					       sector_t last_trk,
					       अचिन्हित पूर्णांक first_offs,
					       अचिन्हित पूर्णांक last_offs,
					       अचिन्हित पूर्णांक blk_per_trk,
					       अचिन्हित पूर्णांक blksize)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	अचिन्हित दीर्घ *idaws;
	काष्ठा LO_eckd_data *LO_data;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst;
	अचिन्हित पूर्णांक off;
	पूर्णांक count, cidaw, cplength, datasize;
	sector_t recid;
	अचिन्हित अक्षर cmd, rcmd;
	पूर्णांक use_prefix;
	काष्ठा dasd_device *basedev;

	basedev = block->base;
	निजी = basedev->निजी;
	अगर (rq_data_dir(req) == READ)
		cmd = DASD_ECKD_CCW_READ_MT;
	अन्यथा अगर (rq_data_dir(req) == WRITE)
		cmd = DASD_ECKD_CCW_WRITE_MT;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	/* Check काष्ठा bio and count the number of blocks क्रम the request. */
	count = 0;
	cidaw = 0;
	rq_क्रम_each_segment(bv, req, iter) अणु
		अगर (bv.bv_len & (blksize - 1))
			/* Eckd can only करो full blocks. */
			वापस ERR_PTR(-EINVAL);
		count += bv.bv_len >> (block->s2b_shअगरt + 9);
		अगर (idal_is_needed (page_address(bv.bv_page), bv.bv_len))
			cidaw += bv.bv_len >> (block->s2b_shअगरt + 9);
	पूर्ण
	/* Paranoia. */
	अगर (count != last_rec - first_rec + 1)
		वापस ERR_PTR(-EINVAL);

	/* use the prefix command अगर available */
	use_prefix = निजी->features.feature[8] & 0x01;
	अगर (use_prefix) अणु
		/* 1x prefix + number of blocks */
		cplength = 2 + count;
		/* 1x prefix + cidaws*माप(दीर्घ) */
		datasize = माप(काष्ठा PFX_eckd_data) +
			माप(काष्ठा LO_eckd_data) +
			cidaw * माप(अचिन्हित दीर्घ);
	पूर्ण अन्यथा अणु
		/* 1x define extent + 1x locate record + number of blocks */
		cplength = 2 + count;
		/* 1x define extent + 1x locate record + cidaws*माप(दीर्घ) */
		datasize = माप(काष्ठा DE_eckd_data) +
			माप(काष्ठा LO_eckd_data) +
			cidaw * माप(अचिन्हित दीर्घ);
	पूर्ण
	/* Find out the number of additional locate record ccws क्रम cdl. */
	अगर (निजी->uses_cdl && first_rec < 2*blk_per_trk) अणु
		अगर (last_rec >= 2*blk_per_trk)
			count = 2*blk_per_trk - first_rec;
		cplength += count;
		datasize += count*माप(काष्ठा LO_eckd_data);
	पूर्ण
	/* Allocate the ccw request. */
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, cplength, datasize,
				   startdev, blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;
	ccw = cqr->cpaddr;
	/* First ccw is define extent or prefix. */
	अगर (use_prefix) अणु
		अगर (prefix(ccw++, cqr->data, first_trk,
			   last_trk, cmd, basedev, startdev) == -EAGAIN) अणु
			/* Clock not in sync and XRC is enabled.
			 * Try again later.
			 */
			dasd_sमुक्त_request(cqr, startdev);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
		idaws = (अचिन्हित दीर्घ *) (cqr->data +
					   माप(काष्ठा PFX_eckd_data));
	पूर्ण अन्यथा अणु
		अगर (define_extent(ccw++, cqr->data, first_trk,
				  last_trk, cmd, basedev, 0) == -EAGAIN) अणु
			/* Clock not in sync and XRC is enabled.
			 * Try again later.
			 */
			dasd_sमुक्त_request(cqr, startdev);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
		idaws = (अचिन्हित दीर्घ *) (cqr->data +
					   माप(काष्ठा DE_eckd_data));
	पूर्ण
	/* Build locate_record+पढ़ो/ग_लिखो/ccws. */
	LO_data = (काष्ठा LO_eckd_data *) (idaws + cidaw);
	recid = first_rec;
	अगर (निजी->uses_cdl == 0 || recid > 2*blk_per_trk) अणु
		/* Only standard blocks so there is just one locate record. */
		ccw[-1].flags |= CCW_FLAG_CC;
		locate_record(ccw++, LO_data++, first_trk, first_offs + 1,
			      last_rec - recid + 1, cmd, basedev, blksize);
	पूर्ण
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		अगर (dasd_page_cache) अणु
			अक्षर *copy = kmem_cache_alloc(dasd_page_cache,
						      GFP_DMA | __GFP_NOWARN);
			अगर (copy && rq_data_dir(req) == WRITE)
				स_नकल(copy + bv.bv_offset, dst, bv.bv_len);
			अगर (copy)
				dst = copy + bv.bv_offset;
		पूर्ण
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			sector_t trkid = recid;
			अचिन्हित पूर्णांक recoffs = sector_भाग(trkid, blk_per_trk);
			rcmd = cmd;
			count = blksize;
			/* Locate record क्रम cdl special block ? */
			अगर (निजी->uses_cdl && recid < 2*blk_per_trk) अणु
				अगर (dasd_eckd_cdl_special(blk_per_trk, recid))अणु
					rcmd |= 0x8;
					count = dasd_eckd_cdl_reclen(recid);
					अगर (count < blksize &&
					    rq_data_dir(req) == READ)
						स_रखो(dst + count, 0xe5,
						       blksize - count);
				पूर्ण
				ccw[-1].flags |= CCW_FLAG_CC;
				locate_record(ccw++, LO_data++,
					      trkid, recoffs + 1,
					      1, rcmd, basedev, count);
			पूर्ण
			/* Locate record क्रम standard blocks ? */
			अगर (निजी->uses_cdl && recid == 2*blk_per_trk) अणु
				ccw[-1].flags |= CCW_FLAG_CC;
				locate_record(ccw++, LO_data++,
					      trkid, recoffs + 1,
					      last_rec - recid + 1,
					      cmd, basedev, count);
			पूर्ण
			/* Read/ग_लिखो ccw. */
			ccw[-1].flags |= CCW_FLAG_CC;
			ccw->cmd_code = rcmd;
			ccw->count = count;
			अगर (idal_is_needed(dst, blksize)) अणु
				ccw->cda = (__u32)(addr_t) idaws;
				ccw->flags = CCW_FLAG_IDA;
				idaws = idal_create_words(idaws, dst, blksize);
			पूर्ण अन्यथा अणु
				ccw->cda = (__u32)(addr_t) dst;
				ccw->flags = 0;
			पूर्ण
			ccw++;
			dst += blksize;
			recid++;
		पूर्ण
	पूर्ण
	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->block = block;
	cqr->expires = startdev->शेष_expires * HZ;	/* शेष 5 minutes */
	cqr->lpm = dasd_path_get_ppm(startdev);
	cqr->retries = startdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	/* Set flags to suppress output क्रम expected errors */
	अगर (dasd_eckd_is_ese(basedev)) अणु
		set_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags);
		set_bit(DASD_CQR_SUPPRESS_IL, &cqr->flags);
		set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);
	पूर्ण

	वापस cqr;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_cp_cmd_track(
					       काष्ठा dasd_device *startdev,
					       काष्ठा dasd_block *block,
					       काष्ठा request *req,
					       sector_t first_rec,
					       sector_t last_rec,
					       sector_t first_trk,
					       sector_t last_trk,
					       अचिन्हित पूर्णांक first_offs,
					       अचिन्हित पूर्णांक last_offs,
					       अचिन्हित पूर्णांक blk_per_trk,
					       अचिन्हित पूर्णांक blksize)
अणु
	अचिन्हित दीर्घ *idaws;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst, *idaw_dst;
	अचिन्हित पूर्णांक cidaw, cplength, datasize;
	अचिन्हित पूर्णांक tlf;
	sector_t recid;
	अचिन्हित अक्षर cmd;
	काष्ठा dasd_device *basedev;
	अचिन्हित पूर्णांक trkcount, count, count_to_trk_end;
	अचिन्हित पूर्णांक idaw_len, seg_len, part_len, len_to_track_end;
	अचिन्हित अक्षर new_track, end_idaw;
	sector_t trkid;
	अचिन्हित पूर्णांक recoffs;

	basedev = block->base;
	अगर (rq_data_dir(req) == READ)
		cmd = DASD_ECKD_CCW_READ_TRACK_DATA;
	अन्यथा अगर (rq_data_dir(req) == WRITE)
		cmd = DASD_ECKD_CCW_WRITE_TRACK_DATA;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	/* Track based I/O needs IDAWs क्रम each page, and not just क्रम
	 * 64 bit addresses. We need additional idals क्रम pages
	 * that get filled from two tracks, so we use the number
	 * of records as upper limit.
	 */
	cidaw = last_rec - first_rec + 1;
	trkcount = last_trk - first_trk + 1;

	/* 1x prefix + one पढ़ो/ग_लिखो ccw per track */
	cplength = 1 + trkcount;

	datasize = माप(काष्ठा PFX_eckd_data) + cidaw * माप(अचिन्हित दीर्घ);

	/* Allocate the ccw request. */
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, cplength, datasize,
				   startdev, blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;
	ccw = cqr->cpaddr;
	/* transfer length factor: how many bytes to पढ़ो from the last track */
	अगर (first_trk == last_trk)
		tlf = last_offs - first_offs + 1;
	अन्यथा
		tlf = last_offs + 1;
	tlf *= blksize;

	अगर (prefix_LRE(ccw++, cqr->data, first_trk,
		       last_trk, cmd, basedev, startdev,
		       1 /* क्रमmat */, first_offs + 1,
		       trkcount, blksize,
		       tlf) == -EAGAIN) अणु
		/* Clock not in sync and XRC is enabled.
		 * Try again later.
		 */
		dasd_sमुक्त_request(cqr, startdev);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण

	/*
	 * The translation of request पूर्णांकo ccw programs must meet the
	 * following conditions:
	 * - all idaws but the first and the last must address full pages
	 *   (or 2K blocks on 31-bit)
	 * - the scope of a ccw and it's idal ends with the track boundaries
	 */
	idaws = (अचिन्हित दीर्घ *) (cqr->data + माप(काष्ठा PFX_eckd_data));
	recid = first_rec;
	new_track = 1;
	end_idaw = 0;
	len_to_track_end = 0;
	idaw_dst = शून्य;
	idaw_len = 0;
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		seg_len = bv.bv_len;
		जबतक (seg_len) अणु
			अगर (new_track) अणु
				trkid = recid;
				recoffs = sector_भाग(trkid, blk_per_trk);
				count_to_trk_end = blk_per_trk - recoffs;
				count = min((last_rec - recid + 1),
					    (sector_t)count_to_trk_end);
				len_to_track_end = count * blksize;
				ccw[-1].flags |= CCW_FLAG_CC;
				ccw->cmd_code = cmd;
				ccw->count = len_to_track_end;
				ccw->cda = (__u32)(addr_t)idaws;
				ccw->flags = CCW_FLAG_IDA;
				ccw++;
				recid += count;
				new_track = 0;
				/* first idaw क्रम a ccw may start anywhere */
				अगर (!idaw_dst)
					idaw_dst = dst;
			पूर्ण
			/* If we start a new idaw, we must make sure that it
			 * starts on an IDA_BLOCK_SIZE boundary.
			 * If we जारी an idaw, we must make sure that the
			 * current segment begins where the so far accumulated
			 * idaw ends
			 */
			अगर (!idaw_dst) अणु
				अगर (__pa(dst) & (IDA_BLOCK_SIZE-1)) अणु
					dasd_sमुक्त_request(cqr, startdev);
					वापस ERR_PTR(-दुस्फल);
				पूर्ण अन्यथा
					idaw_dst = dst;
			पूर्ण
			अगर ((idaw_dst + idaw_len) != dst) अणु
				dasd_sमुक्त_request(cqr, startdev);
				वापस ERR_PTR(-दुस्फल);
			पूर्ण
			part_len = min(seg_len, len_to_track_end);
			seg_len -= part_len;
			dst += part_len;
			idaw_len += part_len;
			len_to_track_end -= part_len;
			/* collected memory area ends on an IDA_BLOCK border,
			 * -> create an idaw
			 * idal_create_words will handle हालs where idaw_len
			 * is larger then IDA_BLOCK_SIZE
			 */
			अगर (!(__pa(idaw_dst + idaw_len) & (IDA_BLOCK_SIZE-1)))
				end_idaw = 1;
			/* We also need to end the idaw at track end */
			अगर (!len_to_track_end) अणु
				new_track = 1;
				end_idaw = 1;
			पूर्ण
			अगर (end_idaw) अणु
				idaws = idal_create_words(idaws, idaw_dst,
							  idaw_len);
				idaw_dst = शून्य;
				idaw_len = 0;
				end_idaw = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->block = block;
	cqr->expires = startdev->शेष_expires * HZ;	/* शेष 5 minutes */
	cqr->lpm = dasd_path_get_ppm(startdev);
	cqr->retries = startdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	/* Set flags to suppress output क्रम expected errors */
	अगर (dasd_eckd_is_ese(basedev))
		set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);

	वापस cqr;
पूर्ण

अटल पूर्णांक prepare_itcw(काष्ठा itcw *itcw,
			अचिन्हित पूर्णांक trk, अचिन्हित पूर्णांक totrk, पूर्णांक cmd,
			काष्ठा dasd_device *basedev,
			काष्ठा dasd_device *startdev,
			अचिन्हित पूर्णांक rec_on_trk, पूर्णांक count,
			अचिन्हित पूर्णांक blksize,
			अचिन्हित पूर्णांक total_data_size,
			अचिन्हित पूर्णांक tlf,
			अचिन्हित पूर्णांक blk_per_trk)
अणु
	काष्ठा PFX_eckd_data pfxdata;
	काष्ठा dasd_eckd_निजी *basepriv, *startpriv;
	काष्ठा DE_eckd_data *dedata;
	काष्ठा LRE_eckd_data *lredata;
	काष्ठा dcw *dcw;

	u32 begcyl, endcyl;
	u16 heads, beghead, endhead;
	u8 pfx_cmd;

	पूर्णांक rc = 0;
	पूर्णांक sector = 0;
	पूर्णांक dn, d;


	/* setup prefix data */
	basepriv = basedev->निजी;
	startpriv = startdev->निजी;
	dedata = &pfxdata.define_extent;
	lredata = &pfxdata.locate_record;

	स_रखो(&pfxdata, 0, माप(pfxdata));
	pfxdata.क्रमmat = 1; /* PFX with LRE */
	pfxdata.base_address = basepriv->ned->unit_addr;
	pfxdata.base_lss = basepriv->ned->ID;
	pfxdata.validity.define_extent = 1;

	/* निजी uid is kept up to date, conf_data may be outdated */
	अगर (startpriv->uid.type == UA_BASE_PAV_ALIAS)
		pfxdata.validity.verअगरy_base = 1;

	अगर (startpriv->uid.type == UA_HYPER_PAV_ALIAS) अणु
		pfxdata.validity.verअगरy_base = 1;
		pfxdata.validity.hyper_pav = 1;
	पूर्ण

	चयन (cmd) अणु
	हाल DASD_ECKD_CCW_READ_TRACK_DATA:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = blksize;
		dedata->ga_extended |= 0x42;
		lredata->operation.orientation = 0x0;
		lredata->operation.operation = 0x0C;
		lredata->auxiliary.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_READ;
		अवरोध;
	हाल DASD_ECKD_CCW_WRITE_TRACK_DATA:
		dedata->mask.perm = 0x02;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = blksize;
		rc = set_बारtamp(शून्य, dedata, basedev);
		dedata->ga_extended |= 0x42;
		lredata->operation.orientation = 0x0;
		lredata->operation.operation = 0x3F;
		lredata->extended_operation = 0x23;
		lredata->auxiliary.check_bytes = 0x2;
		/*
		 * If XRC is supported the System Time Stamp is set. The
		 * validity of the समय stamp must be reflected in the prefix
		 * data as well.
		 */
		अगर (dedata->ga_extended & 0x08 && dedata->ga_extended & 0x02)
			pfxdata.validity.समय_stamp = 1; /* 'Time Stamp Valid' */
		pfx_cmd = DASD_ECKD_CCW_PFX;
		अवरोध;
	हाल DASD_ECKD_CCW_READ_COUNT_MT:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = DASD_BYPASS_CACHE;
		dedata->ga_extended |= 0x42;
		dedata->blk_size = blksize;
		lredata->operation.orientation = 0x2;
		lredata->operation.operation = 0x16;
		lredata->auxiliary.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_READ;
		अवरोध;
	शेष:
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "prepare itcw, unknown opcode 0x%x", cmd);
		BUG();
		अवरोध;
	पूर्ण
	अगर (rc)
		वापस rc;

	dedata->attributes.mode = 0x3;	/* ECKD */

	heads = basepriv->rdc_data.trk_per_cyl;
	begcyl = trk / heads;
	beghead = trk % heads;
	endcyl = totrk / heads;
	endhead = totrk % heads;

	/* check क्रम sequential prestage - enhance cylinder range */
	अगर (dedata->attributes.operation == DASD_SEQ_PRESTAGE ||
	    dedata->attributes.operation == DASD_SEQ_ACCESS) अणु

		अगर (endcyl + basepriv->attrib.nr_cyl < basepriv->real_cyl)
			endcyl += basepriv->attrib.nr_cyl;
		अन्यथा
			endcyl = (basepriv->real_cyl - 1);
	पूर्ण

	set_ch_t(&dedata->beg_ext, begcyl, beghead);
	set_ch_t(&dedata->end_ext, endcyl, endhead);

	dedata->ep_क्रमmat = 0x20; /* records per track is valid */
	dedata->ep_rec_per_track = blk_per_trk;

	अगर (rec_on_trk) अणु
		चयन (basepriv->rdc_data.dev_type) अणु
		हाल 0x3390:
			dn = उच्चमान_quot(blksize + 6, 232);
			d = 9 + उच्चमान_quot(blksize + 6 * (dn + 1), 34);
			sector = (49 + (rec_on_trk - 1) * (10 + d)) / 8;
			अवरोध;
		हाल 0x3380:
			d = 7 + उच्चमान_quot(blksize + 12, 32);
			sector = (39 + (rec_on_trk - 1) * (8 + d)) / 7;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cmd == DASD_ECKD_CCW_READ_COUNT_MT) अणु
		lredata->auxiliary.length_valid = 0;
		lredata->auxiliary.length_scope = 0;
		lredata->sector = 0xff;
	पूर्ण अन्यथा अणु
		lredata->auxiliary.length_valid = 1;
		lredata->auxiliary.length_scope = 1;
		lredata->sector = sector;
	पूर्ण
	lredata->auxiliary.imbedded_ccw_valid = 1;
	lredata->length = tlf;
	lredata->imbedded_ccw = cmd;
	lredata->count = count;
	set_ch_t(&lredata->seek_addr, begcyl, beghead);
	lredata->search_arg.cyl = lredata->seek_addr.cyl;
	lredata->search_arg.head = lredata->seek_addr.head;
	lredata->search_arg.record = rec_on_trk;

	dcw = itcw_add_dcw(itcw, pfx_cmd, 0,
		     &pfxdata, माप(pfxdata), total_data_size);
	वापस PTR_ERR_OR_ZERO(dcw);
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_cp_tpm_track(
					       काष्ठा dasd_device *startdev,
					       काष्ठा dasd_block *block,
					       काष्ठा request *req,
					       sector_t first_rec,
					       sector_t last_rec,
					       sector_t first_trk,
					       sector_t last_trk,
					       अचिन्हित पूर्णांक first_offs,
					       अचिन्हित पूर्णांक last_offs,
					       अचिन्हित पूर्णांक blk_per_trk,
					       अचिन्हित पूर्णांक blksize)
अणु
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst;
	अचिन्हित पूर्णांक trkcount, ctidaw;
	अचिन्हित अक्षर cmd;
	काष्ठा dasd_device *basedev;
	अचिन्हित पूर्णांक tlf;
	काष्ठा itcw *itcw;
	काष्ठा tidaw *last_tidaw = शून्य;
	पूर्णांक itcw_op;
	माप_प्रकार itcw_size;
	u8 tidaw_flags;
	अचिन्हित पूर्णांक seg_len, part_len, len_to_track_end;
	अचिन्हित अक्षर new_track;
	sector_t recid, trkid;
	अचिन्हित पूर्णांक offs;
	अचिन्हित पूर्णांक count, count_to_trk_end;
	पूर्णांक ret;

	basedev = block->base;
	अगर (rq_data_dir(req) == READ) अणु
		cmd = DASD_ECKD_CCW_READ_TRACK_DATA;
		itcw_op = ITCW_OP_READ;
	पूर्ण अन्यथा अगर (rq_data_dir(req) == WRITE) अणु
		cmd = DASD_ECKD_CCW_WRITE_TRACK_DATA;
		itcw_op = ITCW_OP_WRITE;
	पूर्ण अन्यथा
		वापस ERR_PTR(-EINVAL);

	/* trackbased I/O needs address all memory via TIDAWs,
	 * not just क्रम 64 bit addresses. This allows us to map
	 * each segment directly to one tidaw.
	 * In the हाल of ग_लिखो requests, additional tidaws may
	 * be needed when a segment crosses a track boundary.
	 */
	trkcount = last_trk - first_trk + 1;
	ctidaw = 0;
	rq_क्रम_each_segment(bv, req, iter) अणु
		++ctidaw;
	पूर्ण
	अगर (rq_data_dir(req) == WRITE)
		ctidaw += (last_trk - first_trk);

	/* Allocate the ccw request. */
	itcw_size = itcw_calc_size(0, ctidaw, 0);
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 0, itcw_size, startdev,
				   blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;

	/* transfer length factor: how many bytes to पढ़ो from the last track */
	अगर (first_trk == last_trk)
		tlf = last_offs - first_offs + 1;
	अन्यथा
		tlf = last_offs + 1;
	tlf *= blksize;

	itcw = itcw_init(cqr->data, itcw_size, itcw_op, 0, ctidaw, 0);
	अगर (IS_ERR(itcw)) अणु
		ret = -EINVAL;
		जाओ out_error;
	पूर्ण
	cqr->cpaddr = itcw_get_tcw(itcw);
	अगर (prepare_itcw(itcw, first_trk, last_trk,
			 cmd, basedev, startdev,
			 first_offs + 1,
			 trkcount, blksize,
			 (last_rec - first_rec + 1) * blksize,
			 tlf, blk_per_trk) == -EAGAIN) अणु
		/* Clock not in sync and XRC is enabled.
		 * Try again later.
		 */
		ret = -EAGAIN;
		जाओ out_error;
	पूर्ण
	len_to_track_end = 0;
	/*
	 * A tidaw can address 4k of memory, but must not cross page boundaries
	 * We can let the block layer handle this by setting
	 * blk_queue_segment_boundary to page boundaries and
	 * blk_max_segment_size to page size when setting up the request queue.
	 * For ग_लिखो requests, a TIDAW must not cross track boundaries, because
	 * we have to set the CBC flag on the last tidaw क्रम each track.
	 */
	अगर (rq_data_dir(req) == WRITE) अणु
		new_track = 1;
		recid = first_rec;
		rq_क्रम_each_segment(bv, req, iter) अणु
			dst = page_address(bv.bv_page) + bv.bv_offset;
			seg_len = bv.bv_len;
			जबतक (seg_len) अणु
				अगर (new_track) अणु
					trkid = recid;
					offs = sector_भाग(trkid, blk_per_trk);
					count_to_trk_end = blk_per_trk - offs;
					count = min((last_rec - recid + 1),
						    (sector_t)count_to_trk_end);
					len_to_track_end = count * blksize;
					recid += count;
					new_track = 0;
				पूर्ण
				part_len = min(seg_len, len_to_track_end);
				seg_len -= part_len;
				len_to_track_end -= part_len;
				/* We need to end the tidaw at track end */
				अगर (!len_to_track_end) अणु
					new_track = 1;
					tidaw_flags = TIDAW_FLAGS_INSERT_CBC;
				पूर्ण अन्यथा
					tidaw_flags = 0;
				last_tidaw = itcw_add_tidaw(itcw, tidaw_flags,
							    dst, part_len);
				अगर (IS_ERR(last_tidaw)) अणु
					ret = -EINVAL;
					जाओ out_error;
				पूर्ण
				dst += part_len;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rq_क्रम_each_segment(bv, req, iter) अणु
			dst = page_address(bv.bv_page) + bv.bv_offset;
			last_tidaw = itcw_add_tidaw(itcw, 0x00,
						    dst, bv.bv_len);
			अगर (IS_ERR(last_tidaw)) अणु
				ret = -EINVAL;
				जाओ out_error;
			पूर्ण
		पूर्ण
	पूर्ण
	last_tidaw->flags |= TIDAW_FLAGS_LAST;
	last_tidaw->flags &= ~TIDAW_FLAGS_INSERT_CBC;
	itcw_finalize(itcw);

	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->cpmode = 1;
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->block = block;
	cqr->expires = startdev->शेष_expires * HZ;	/* शेष 5 minutes */
	cqr->lpm = dasd_path_get_ppm(startdev);
	cqr->retries = startdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	/* Set flags to suppress output क्रम expected errors */
	अगर (dasd_eckd_is_ese(basedev)) अणु
		set_bit(DASD_CQR_SUPPRESS_FP, &cqr->flags);
		set_bit(DASD_CQR_SUPPRESS_IL, &cqr->flags);
		set_bit(DASD_CQR_SUPPRESS_NRF, &cqr->flags);
	पूर्ण

	वापस cqr;
out_error:
	dasd_sमुक्त_request(cqr, startdev);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_cp(काष्ठा dasd_device *startdev,
					       काष्ठा dasd_block *block,
					       काष्ठा request *req)
अणु
	पूर्णांक cmdrtd, cmdwtd;
	पूर्णांक use_prefix;
	पूर्णांक fcx_multitrack;
	काष्ठा dasd_eckd_निजी *निजी;
	काष्ठा dasd_device *basedev;
	sector_t first_rec, last_rec;
	sector_t first_trk, last_trk;
	अचिन्हित पूर्णांक first_offs, last_offs;
	अचिन्हित पूर्णांक blk_per_trk, blksize;
	पूर्णांक cdlspecial;
	अचिन्हित पूर्णांक data_size;
	काष्ठा dasd_ccw_req *cqr;

	basedev = block->base;
	निजी = basedev->निजी;

	/* Calculate number of blocks/records per track. */
	blksize = block->bp_block;
	blk_per_trk = recs_per_track(&निजी->rdc_data, 0, blksize);
	अगर (blk_per_trk == 0)
		वापस ERR_PTR(-EINVAL);
	/* Calculate record id of first and last block. */
	first_rec = first_trk = blk_rq_pos(req) >> block->s2b_shअगरt;
	first_offs = sector_भाग(first_trk, blk_per_trk);
	last_rec = last_trk =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	last_offs = sector_भाग(last_trk, blk_per_trk);
	cdlspecial = (निजी->uses_cdl && first_rec < 2*blk_per_trk);

	fcx_multitrack = निजी->features.feature[40] & 0x20;
	data_size = blk_rq_bytes(req);
	अगर (data_size % blksize)
		वापस ERR_PTR(-EINVAL);
	/* tpm ग_लिखो request add CBC data on each track boundary */
	अगर (rq_data_dir(req) == WRITE)
		data_size += (last_trk - first_trk) * 4;

	/* is पढ़ो track data and ग_लिखो track data in command mode supported? */
	cmdrtd = निजी->features.feature[9] & 0x20;
	cmdwtd = निजी->features.feature[12] & 0x40;
	use_prefix = निजी->features.feature[8] & 0x01;

	cqr = शून्य;
	अगर (cdlspecial || dasd_page_cache) अणु
		/* करो nothing, just fall through to the cmd mode single हाल */
	पूर्ण अन्यथा अगर ((data_size <= निजी->fcx_max_data)
		   && (fcx_multitrack || (first_trk == last_trk))) अणु
		cqr = dasd_eckd_build_cp_tpm_track(startdev, block, req,
						    first_rec, last_rec,
						    first_trk, last_trk,
						    first_offs, last_offs,
						    blk_per_trk, blksize);
		अगर (IS_ERR(cqr) && (PTR_ERR(cqr) != -EAGAIN) &&
		    (PTR_ERR(cqr) != -ENOMEM))
			cqr = शून्य;
	पूर्ण अन्यथा अगर (use_prefix &&
		   (((rq_data_dir(req) == READ) && cmdrtd) ||
		    ((rq_data_dir(req) == WRITE) && cmdwtd))) अणु
		cqr = dasd_eckd_build_cp_cmd_track(startdev, block, req,
						   first_rec, last_rec,
						   first_trk, last_trk,
						   first_offs, last_offs,
						   blk_per_trk, blksize);
		अगर (IS_ERR(cqr) && (PTR_ERR(cqr) != -EAGAIN) &&
		    (PTR_ERR(cqr) != -ENOMEM))
			cqr = शून्य;
	पूर्ण
	अगर (!cqr)
		cqr = dasd_eckd_build_cp_cmd_single(startdev, block, req,
						    first_rec, last_rec,
						    first_trk, last_trk,
						    first_offs, last_offs,
						    blk_per_trk, blksize);
	वापस cqr;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_cp_raw(काष्ठा dasd_device *startdev,
						   काष्ठा dasd_block *block,
						   काष्ठा request *req)
अणु
	sector_t start_padding_sectors, end_sector_offset, end_padding_sectors;
	अचिन्हित पूर्णांक seg_len, len_to_track_end;
	अचिन्हित पूर्णांक cidaw, cplength, datasize;
	sector_t first_trk, last_trk, sectors;
	काष्ठा dasd_eckd_निजी *base_priv;
	काष्ठा dasd_device *basedev;
	काष्ठा req_iterator iter;
	काष्ठा dasd_ccw_req *cqr;
	अचिन्हित पूर्णांक first_offs;
	अचिन्हित पूर्णांक trkcount;
	अचिन्हित दीर्घ *idaws;
	अचिन्हित पूर्णांक size;
	अचिन्हित अक्षर cmd;
	काष्ठा bio_vec bv;
	काष्ठा ccw1 *ccw;
	पूर्णांक use_prefix;
	व्योम *data;
	अक्षर *dst;

	/*
	 * raw track access needs to be mutiple of 64k and on 64k boundary
	 * For पढ़ो requests we can fix an incorrect alignment by padding
	 * the request with dummy pages.
	 */
	start_padding_sectors = blk_rq_pos(req) % DASD_RAW_SECTORS_PER_TRACK;
	end_sector_offset = (blk_rq_pos(req) + blk_rq_sectors(req)) %
		DASD_RAW_SECTORS_PER_TRACK;
	end_padding_sectors = (DASD_RAW_SECTORS_PER_TRACK - end_sector_offset) %
		DASD_RAW_SECTORS_PER_TRACK;
	basedev = block->base;
	अगर ((start_padding_sectors || end_padding_sectors) &&
	    (rq_data_dir(req) == WRITE)) अणु
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "raw write not track aligned (%llu,%llu) req %p",
			      start_padding_sectors, end_padding_sectors, req);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	first_trk = blk_rq_pos(req) / DASD_RAW_SECTORS_PER_TRACK;
	last_trk = (blk_rq_pos(req) + blk_rq_sectors(req) - 1) /
		DASD_RAW_SECTORS_PER_TRACK;
	trkcount = last_trk - first_trk + 1;
	first_offs = 0;

	अगर (rq_data_dir(req) == READ)
		cmd = DASD_ECKD_CCW_READ_TRACK;
	अन्यथा अगर (rq_data_dir(req) == WRITE)
		cmd = DASD_ECKD_CCW_WRITE_FULL_TRACK;
	अन्यथा
		वापस ERR_PTR(-EINVAL);

	/*
	 * Raw track based I/O needs IDAWs क्रम each page,
	 * and not just क्रम 64 bit addresses.
	 */
	cidaw = trkcount * DASD_RAW_BLOCK_PER_TRACK;

	/*
	 * काष्ठा PFX_eckd_data and काष्ठा LRE_eckd_data can have up to 2 bytes
	 * of extended parameter. This is needed क्रम ग_लिखो full track.
	 */
	base_priv = basedev->निजी;
	use_prefix = base_priv->features.feature[8] & 0x01;
	अगर (use_prefix) अणु
		cplength = 1 + trkcount;
		size = माप(काष्ठा PFX_eckd_data) + 2;
	पूर्ण अन्यथा अणु
		cplength = 2 + trkcount;
		size = माप(काष्ठा DE_eckd_data) +
			माप(काष्ठा LRE_eckd_data) + 2;
	पूर्ण
	size = ALIGN(size, 8);

	datasize = size + cidaw * माप(अचिन्हित दीर्घ);

	/* Allocate the ccw request. */
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, cplength,
				   datasize, startdev, blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;

	ccw = cqr->cpaddr;
	data = cqr->data;

	अगर (use_prefix) अणु
		prefix_LRE(ccw++, data, first_trk, last_trk, cmd, basedev,
			   startdev, 1, first_offs + 1, trkcount, 0, 0);
	पूर्ण अन्यथा अणु
		define_extent(ccw++, data, first_trk, last_trk, cmd, basedev, 0);
		ccw[-1].flags |= CCW_FLAG_CC;

		data += माप(काष्ठा DE_eckd_data);
		locate_record_ext(ccw++, data, first_trk, first_offs + 1,
				  trkcount, cmd, basedev, 0, 0);
	पूर्ण

	idaws = (अचिन्हित दीर्घ *)(cqr->data + size);
	len_to_track_end = 0;
	अगर (start_padding_sectors) अणु
		ccw[-1].flags |= CCW_FLAG_CC;
		ccw->cmd_code = cmd;
		/* maximum 3390 track size */
		ccw->count = 57326;
		/* 64k map to one track */
		len_to_track_end = 65536 - start_padding_sectors * 512;
		ccw->cda = (__u32)(addr_t)idaws;
		ccw->flags |= CCW_FLAG_IDA;
		ccw->flags |= CCW_FLAG_SLI;
		ccw++;
		क्रम (sectors = 0; sectors < start_padding_sectors; sectors += 8)
			idaws = idal_create_words(idaws, rawpadpage, PAGE_SIZE);
	पूर्ण
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		seg_len = bv.bv_len;
		अगर (cmd == DASD_ECKD_CCW_READ_TRACK)
			स_रखो(dst, 0, seg_len);
		अगर (!len_to_track_end) अणु
			ccw[-1].flags |= CCW_FLAG_CC;
			ccw->cmd_code = cmd;
			/* maximum 3390 track size */
			ccw->count = 57326;
			/* 64k map to one track */
			len_to_track_end = 65536;
			ccw->cda = (__u32)(addr_t)idaws;
			ccw->flags |= CCW_FLAG_IDA;
			ccw->flags |= CCW_FLAG_SLI;
			ccw++;
		पूर्ण
		len_to_track_end -= seg_len;
		idaws = idal_create_words(idaws, dst, seg_len);
	पूर्ण
	क्रम (sectors = 0; sectors < end_padding_sectors; sectors += 8)
		idaws = idal_create_words(idaws, rawpadpage, PAGE_SIZE);
	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->startdev = startdev;
	cqr->memdev = startdev;
	cqr->block = block;
	cqr->expires = startdev->शेष_expires * HZ;
	cqr->lpm = dasd_path_get_ppm(startdev);
	cqr->retries = startdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	वापस cqr;
पूर्ण


अटल पूर्णांक
dasd_eckd_मुक्त_cp(काष्ठा dasd_ccw_req *cqr, काष्ठा request *req)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	काष्ठा ccw1 *ccw;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst, *cda;
	अचिन्हित पूर्णांक blksize, blk_per_trk, off;
	sector_t recid;
	पूर्णांक status;

	अगर (!dasd_page_cache)
		जाओ out;
	निजी = cqr->block->base->निजी;
	blksize = cqr->block->bp_block;
	blk_per_trk = recs_per_track(&निजी->rdc_data, 0, blksize);
	recid = blk_rq_pos(req) >> cqr->block->s2b_shअगरt;
	ccw = cqr->cpaddr;
	/* Skip over define extent & locate record. */
	ccw++;
	अगर (निजी->uses_cdl == 0 || recid > 2*blk_per_trk)
		ccw++;
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			/* Skip locate record. */
			अगर (निजी->uses_cdl && recid <= 2*blk_per_trk)
				ccw++;
			अगर (dst) अणु
				अगर (ccw->flags & CCW_FLAG_IDA)
					cda = *((अक्षर **)((addr_t) ccw->cda));
				अन्यथा
					cda = (अक्षर *)((addr_t) ccw->cda);
				अगर (dst != cda) अणु
					अगर (rq_data_dir(req) == READ)
						स_नकल(dst, cda, bv.bv_len);
					kmem_cache_मुक्त(dasd_page_cache,
					    (व्योम *)((addr_t)cda & PAGE_MASK));
				पूर्ण
				dst = शून्य;
			पूर्ण
			ccw++;
			recid++;
		पूर्ण
	पूर्ण
out:
	status = cqr->status == DASD_CQR_DONE;
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस status;
पूर्ण

/*
 * Modअगरy ccw/tcw in cqr so it can be started on a base device.
 *
 * Note that this is not enough to restart the cqr!
 * Either reset cqr->startdev as well (summary unit check handling)
 * or restart via separate cqr (as in ERP handling).
 */
व्योम dasd_eckd_reset_ccw_to_base_io(काष्ठा dasd_ccw_req *cqr)
अणु
	काष्ठा ccw1 *ccw;
	काष्ठा PFX_eckd_data *pfxdata;
	काष्ठा tcw *tcw;
	काष्ठा tccb *tccb;
	काष्ठा dcw *dcw;

	अगर (cqr->cpmode == 1) अणु
		tcw = cqr->cpaddr;
		tccb = tcw_get_tccb(tcw);
		dcw = (काष्ठा dcw *)&tccb->tca[0];
		pfxdata = (काष्ठा PFX_eckd_data *)&dcw->cd[0];
		pfxdata->validity.verअगरy_base = 0;
		pfxdata->validity.hyper_pav = 0;
	पूर्ण अन्यथा अणु
		ccw = cqr->cpaddr;
		pfxdata = cqr->data;
		अगर (ccw->cmd_code == DASD_ECKD_CCW_PFX) अणु
			pfxdata->validity.verअगरy_base = 0;
			pfxdata->validity.hyper_pav = 0;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा DASD_ECKD_CHANQ_MAX_SIZE 4

अटल काष्ठा dasd_ccw_req *dasd_eckd_build_alias_cp(काष्ठा dasd_device *base,
						     काष्ठा dasd_block *block,
						     काष्ठा request *req)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	काष्ठा dasd_device *startdev;
	अचिन्हित दीर्घ flags;
	काष्ठा dasd_ccw_req *cqr;

	startdev = dasd_alias_get_start_dev(base);
	अगर (!startdev)
		startdev = base;
	निजी = startdev->निजी;
	अगर (निजी->count >= DASD_ECKD_CHANQ_MAX_SIZE)
		वापस ERR_PTR(-EBUSY);

	spin_lock_irqsave(get_ccwdev_lock(startdev->cdev), flags);
	निजी->count++;
	अगर ((base->features & DASD_FEATURE_USERAW))
		cqr = dasd_eckd_build_cp_raw(startdev, block, req);
	अन्यथा
		cqr = dasd_eckd_build_cp(startdev, block, req);
	अगर (IS_ERR(cqr))
		निजी->count--;
	spin_unlock_irqrestore(get_ccwdev_lock(startdev->cdev), flags);
	वापस cqr;
पूर्ण

अटल पूर्णांक dasd_eckd_मुक्त_alias_cp(काष्ठा dasd_ccw_req *cqr,
				   काष्ठा request *req)
अणु
	काष्ठा dasd_eckd_निजी *निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(cqr->memdev->cdev), flags);
	निजी = cqr->memdev->निजी;
	निजी->count--;
	spin_unlock_irqrestore(get_ccwdev_lock(cqr->memdev->cdev), flags);
	वापस dasd_eckd_मुक्त_cp(cqr, req);
पूर्ण

अटल पूर्णांक
dasd_eckd_fill_info(काष्ठा dasd_device * device,
		    काष्ठा dasd_inक्रमmation2_t * info)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	info->label_block = 2;
	info->FBA_layout = निजी->uses_cdl ? 0 : 1;
	info->क्रमmat = निजी->uses_cdl ? DASD_FORMAT_CDL : DASD_FORMAT_LDL;
	info->अक्षरacteristics_size = माप(निजी->rdc_data);
	स_नकल(info->अक्षरacteristics, &निजी->rdc_data,
	       माप(निजी->rdc_data));
	info->confdata_size = min((अचिन्हित दीर्घ)निजी->conf_len,
				  माप(info->configuration_data));
	स_नकल(info->configuration_data, निजी->conf_data,
	       info->confdata_size);
	वापस 0;
पूर्ण

/*
 * SECTION: ioctl functions क्रम eckd devices.
 */

/*
 * Release device ioctl.
 * Buils a channel programm to releases a prior reserved
 * (see dasd_eckd_reserve) device.
 */
अटल पूर्णांक
dasd_eckd_release(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;
	काष्ठा ccw1 *ccw;
	पूर्णांक useglobal;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	useglobal = 0;
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1, 32, device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		mutex_lock(&dasd_reserve_mutex);
		useglobal = 1;
		cqr = &dasd_reserve_req->cqr;
		स_रखो(cqr, 0, माप(*cqr));
		स_रखो(&dasd_reserve_req->ccw, 0,
		       माप(dasd_reserve_req->ccw));
		cqr->cpaddr = &dasd_reserve_req->ccw;
		cqr->data = &dasd_reserve_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	पूर्ण
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_RELEASE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 32;
	ccw->cda = (__u32)(addr_t) cqr->data;
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->retries = 2;	/* set retry counter to enable basic ERP */
	cqr->expires = 2 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	rc = dasd_sleep_on_immediatly(cqr);
	अगर (!rc)
		clear_bit(DASD_FLAG_IS_RESERVED, &device->flags);

	अगर (useglobal)
		mutex_unlock(&dasd_reserve_mutex);
	अन्यथा
		dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * Reserve device ioctl.
 * Options are set to 'synchronous wait for interrupt' and
 * 'timeout the request'. This leads to a terminate IO अगर
 * the पूर्णांकerrupt is outstanding क्रम a certain समय.
 */
अटल पूर्णांक
dasd_eckd_reserve(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;
	काष्ठा ccw1 *ccw;
	पूर्णांक useglobal;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	useglobal = 0;
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1, 32, device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		mutex_lock(&dasd_reserve_mutex);
		useglobal = 1;
		cqr = &dasd_reserve_req->cqr;
		स_रखो(cqr, 0, माप(*cqr));
		स_रखो(&dasd_reserve_req->ccw, 0,
		       माप(dasd_reserve_req->ccw));
		cqr->cpaddr = &dasd_reserve_req->ccw;
		cqr->data = &dasd_reserve_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	पूर्ण
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_RESERVE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 32;
	ccw->cda = (__u32)(addr_t) cqr->data;
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->retries = 2;	/* set retry counter to enable basic ERP */
	cqr->expires = 2 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	rc = dasd_sleep_on_immediatly(cqr);
	अगर (!rc)
		set_bit(DASD_FLAG_IS_RESERVED, &device->flags);

	अगर (useglobal)
		mutex_unlock(&dasd_reserve_mutex);
	अन्यथा
		dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * Steal lock ioctl - unconditional reserve device.
 * Buils a channel programm to अवरोध a device's reservation.
 * (unconditional reserve)
 */
अटल पूर्णांक
dasd_eckd_steal_lock(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;
	काष्ठा ccw1 *ccw;
	पूर्णांक useglobal;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	useglobal = 0;
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1, 32, device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		mutex_lock(&dasd_reserve_mutex);
		useglobal = 1;
		cqr = &dasd_reserve_req->cqr;
		स_रखो(cqr, 0, माप(*cqr));
		स_रखो(&dasd_reserve_req->ccw, 0,
		       माप(dasd_reserve_req->ccw));
		cqr->cpaddr = &dasd_reserve_req->ccw;
		cqr->data = &dasd_reserve_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	पूर्ण
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_SLCK;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 32;
	ccw->cda = (__u32)(addr_t) cqr->data;
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->retries = 2;	/* set retry counter to enable basic ERP */
	cqr->expires = 2 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	rc = dasd_sleep_on_immediatly(cqr);
	अगर (!rc)
		set_bit(DASD_FLAG_IS_RESERVED, &device->flags);

	अगर (useglobal)
		mutex_unlock(&dasd_reserve_mutex);
	अन्यथा
		dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * SNID - Sense Path Group ID
 * This ioctl may be used in situations where I/O is stalled due to
 * a reserve, so अगर the normal dasd_sदो_स्मृति_request fails, we use the
 * pपुनः_स्मृतिated dasd_reserve_req.
 */
अटल पूर्णांक dasd_eckd_snid(काष्ठा dasd_device *device,
			  व्योम __user *argp)
अणु
	काष्ठा dasd_ccw_req *cqr;
	पूर्णांक rc;
	काष्ठा ccw1 *ccw;
	पूर्णांक useglobal;
	काष्ठा dasd_snid_ioctl_data usrparm;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (copy_from_user(&usrparm, argp, माप(usrparm)))
		वापस -EFAULT;

	useglobal = 0;
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1,
				   माप(काष्ठा dasd_snid_data), device,
				   शून्य);
	अगर (IS_ERR(cqr)) अणु
		mutex_lock(&dasd_reserve_mutex);
		useglobal = 1;
		cqr = &dasd_reserve_req->cqr;
		स_रखो(cqr, 0, माप(*cqr));
		स_रखो(&dasd_reserve_req->ccw, 0,
		       माप(dasd_reserve_req->ccw));
		cqr->cpaddr = &dasd_reserve_req->ccw;
		cqr->data = &dasd_reserve_req->data;
		cqr->magic = DASD_ECKD_MAGIC;
	पूर्ण
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_SNID;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 12;
	ccw->cda = (__u32)(addr_t) cqr->data;
	cqr->startdev = device;
	cqr->memdev = device;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	set_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags);
	cqr->retries = 5;
	cqr->expires = 10 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	cqr->lpm = usrparm.path_mask;

	rc = dasd_sleep_on_immediatly(cqr);
	/* verअगरy that I/O processing didn't modअगरy the path mask */
	अगर (!rc && usrparm.path_mask && (cqr->lpm != usrparm.path_mask))
		rc = -EIO;
	अगर (!rc) अणु
		usrparm.data = *((काष्ठा dasd_snid_data *)cqr->data);
		अगर (copy_to_user(argp, &usrparm, माप(usrparm)))
			rc = -EFAULT;
	पूर्ण

	अगर (useglobal)
		mutex_unlock(&dasd_reserve_mutex);
	अन्यथा
		dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * Read perक्रमmance statistics
 */
अटल पूर्णांक
dasd_eckd_perक्रमmance(काष्ठा dasd_device *device, व्योम __user *argp)
अणु
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_rssd_perf_stats_t *stats;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */  + 1 /* RSSD */,
				   (माप(काष्ठा dasd_psf_prssd_data) +
				    माप(काष्ठा dasd_rssd_perf_stats_t)),
				   device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Could not allocate initialization request");
		वापस PTR_ERR(cqr);
	पूर्ण
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->retries = 0;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	cqr->expires = 10 * HZ;

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
	स_रखो(prssdp, 0, माप(काष्ठा dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x01;	/* Perक्रमmance Statistics */
	prssdp->varies[1] = 0x01;	/* Perf Statistics क्रम the Subप्रणाली */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(काष्ठा dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subप्रणाली Data - Perक्रमmance Statistics */
	stats = (काष्ठा dasd_rssd_perf_stats_t *) (prssdp + 1);
	स_रखो(stats, 0, माप(काष्ठा dasd_rssd_perf_stats_t));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(काष्ठा dasd_rssd_perf_stats_t);
	ccw->cda = (__u32)(addr_t) stats;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	rc = dasd_sleep_on(cqr);
	अगर (rc == 0) अणु
		prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
		stats = (काष्ठा dasd_rssd_perf_stats_t *) (prssdp + 1);
		अगर (copy_to_user(argp, stats,
				 माप(काष्ठा dasd_rssd_perf_stats_t)))
			rc = -EFAULT;
	पूर्ण
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * Get attributes (cache operations)
 * Returnes the cache attributes used in Define Extend (DE).
 */
अटल पूर्णांक
dasd_eckd_get_attrib(काष्ठा dasd_device *device, व्योम __user *argp)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा attrib_data_t attrib = निजी->attrib;
	पूर्णांक rc;

        अगर (!capable(CAP_SYS_ADMIN))
                वापस -EACCES;
	अगर (!argp)
                वापस -EINVAL;

	rc = 0;
	अगर (copy_to_user(argp, (दीर्घ *) &attrib,
			 माप(काष्ठा attrib_data_t)))
		rc = -EFAULT;

	वापस rc;
पूर्ण

/*
 * Set attributes (cache operations)
 * Stores the attributes क्रम cache operation to be used in Define Extend (DE).
 */
अटल पूर्णांक
dasd_eckd_set_attrib(काष्ठा dasd_device *device, व्योम __user *argp)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा attrib_data_t attrib;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!argp)
		वापस -EINVAL;

	अगर (copy_from_user(&attrib, argp, माप(काष्ठा attrib_data_t)))
		वापस -EFAULT;
	निजी->attrib = attrib;

	dev_info(&device->cdev->dev,
		 "The DASD cache mode was set to %x (%i cylinder prestage)\n",
		 निजी->attrib.operation, निजी->attrib.nr_cyl);
	वापस 0;
पूर्ण

/*
 * Issue syscall I/O to EMC Symmetrix array.
 * CCWs are PSF and RSSD
 */
अटल पूर्णांक dasd_symm_io(काष्ठा dasd_device *device, व्योम __user *argp)
अणु
	काष्ठा dasd_symmio_parms usrparm;
	अक्षर *psf_data, *rssd_result;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	अक्षर psf0, psf1;
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_RAWIO))
		वापस -EACCES;
	psf0 = psf1 = 0;

	/* Copy parms from caller */
	rc = -EFAULT;
	अगर (copy_from_user(&usrparm, argp, माप(usrparm)))
		जाओ out;
	अगर (is_compat_task()) अणु
		/* Make sure poपूर्णांकers are sane even on 31 bit. */
		rc = -EINVAL;
		अगर ((usrparm.psf_data >> 32) != 0)
			जाओ out;
		अगर ((usrparm.rssd_result >> 32) != 0)
			जाओ out;
		usrparm.psf_data &= 0x7fffffffULL;
		usrparm.rssd_result &= 0x7fffffffULL;
	पूर्ण
	/* at least 2 bytes are accessed and should be allocated */
	अगर (usrparm.psf_data_len < 2) अणु
		DBF_DEV_EVENT(DBF_WARNING, device,
			      "Symmetrix ioctl invalid data length %d",
			      usrparm.psf_data_len);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* alloc I/O data area */
	psf_data = kzalloc(usrparm.psf_data_len, GFP_KERNEL | GFP_DMA);
	rssd_result = kzalloc(usrparm.rssd_result_len, GFP_KERNEL | GFP_DMA);
	अगर (!psf_data || !rssd_result) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* get syscall header from user space */
	rc = -EFAULT;
	अगर (copy_from_user(psf_data,
			   (व्योम __user *)(अचिन्हित दीर्घ) usrparm.psf_data,
			   usrparm.psf_data_len))
		जाओ out_मुक्त;
	psf0 = psf_data[0];
	psf1 = psf_data[1];

	/* setup CCWs क्रम PSF + RSSD */
	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 2, 0, device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			"Could not allocate initialization request");
		rc = PTR_ERR(cqr);
		जाओ out_मुक्त;
	पूर्ण

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->retries = 3;
	cqr->expires = 10 * HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;

	/* Build the ccws */
	ccw = cqr->cpaddr;

	/* PSF ccw */
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = usrparm.psf_data_len;
	ccw->flags |= CCW_FLAG_CC;
	ccw->cda = (__u32)(addr_t) psf_data;

	ccw++;

	/* RSSD ccw  */
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = usrparm.rssd_result_len;
	ccw->flags = CCW_FLAG_SLI ;
	ccw->cda = (__u32)(addr_t) rssd_result;

	rc = dasd_sleep_on(cqr);
	अगर (rc)
		जाओ out_sमुक्त;

	rc = -EFAULT;
	अगर (copy_to_user((व्योम __user *)(अचिन्हित दीर्घ) usrparm.rssd_result,
			   rssd_result, usrparm.rssd_result_len))
		जाओ out_sमुक्त;
	rc = 0;

out_sमुक्त:
	dasd_sमुक्त_request(cqr, cqr->memdev);
out_मुक्त:
	kमुक्त(rssd_result);
	kमुक्त(psf_data);
out:
	DBF_DEV_EVENT(DBF_WARNING, device,
		      "Symmetrix ioctl (0x%02x 0x%02x): rc=%d",
		      (पूर्णांक) psf0, (पूर्णांक) psf1, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक
dasd_eckd_ioctl(काष्ठा dasd_block *block, अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा dasd_device *device = block->base;

	चयन (cmd) अणु
	हाल BIODASDGATTR:
		वापस dasd_eckd_get_attrib(device, argp);
	हाल BIODASDSATTR:
		वापस dasd_eckd_set_attrib(device, argp);
	हाल BIODASDPSRD:
		वापस dasd_eckd_perक्रमmance(device, argp);
	हाल BIODASDRLSE:
		वापस dasd_eckd_release(device);
	हाल BIODASDRSRV:
		वापस dasd_eckd_reserve(device);
	हाल BIODASDSLCK:
		वापस dasd_eckd_steal_lock(device);
	हाल BIODASDSNID:
		वापस dasd_eckd_snid(device, argp);
	हाल BIODASDSYMMIO:
		वापस dasd_symm_io(device, argp);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/*
 * Dump the range of CCWs पूर्णांकo 'page' buffer
 * and वापस number of prपूर्णांकed अक्षरs.
 */
अटल पूर्णांक
dasd_eckd_dump_ccw_range(काष्ठा ccw1 *from, काष्ठा ccw1 *to, अक्षर *page)
अणु
	पूर्णांक len, count;
	अक्षर *datap;

	len = 0;
	जबतक (from <= to) अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " CCW %p: %08X %08X DAT:",
			       from, ((पूर्णांक *) from)[0], ((पूर्णांक *) from)[1]);

		/* get poपूर्णांकer to data (consider IDALs) */
		अगर (from->flags & CCW_FLAG_IDA)
			datap = (अक्षर *) *((addr_t *) (addr_t) from->cda);
		अन्यथा
			datap = (अक्षर *) ((addr_t) from->cda);

		/* dump data (max 32 bytes) */
		क्रम (count = 0; count < from->count && count < 32; count++) अणु
			अगर (count % 8 == 0) len += प्र_लिखो(page + len, " ");
			अगर (count % 4 == 0) len += प्र_लिखो(page + len, " ");
			len += प्र_लिखो(page + len, "%02x", datap[count]);
		पूर्ण
		len += प्र_लिखो(page + len, "\n");
		from++;
	पूर्ण
	वापस len;
पूर्ण

अटल व्योम
dasd_eckd_dump_sense_dbf(काष्ठा dasd_device *device, काष्ठा irb *irb,
			 अक्षर *reason)
अणु
	u64 *sense;
	u64 *stat;

	sense = (u64 *) dasd_get_sense(irb);
	stat = (u64 *) &irb->scsw;
	अगर (sense) अणु
		DBF_DEV_EVENT(DBF_EMERG, device, "%s: %016llx %08x : "
			      "%016llx %016llx %016llx %016llx",
			      reason, *stat, *((u32 *) (stat + 1)),
			      sense[0], sense[1], sense[2], sense[3]);
	पूर्ण अन्यथा अणु
		DBF_DEV_EVENT(DBF_EMERG, device, "%s: %016llx %08x : %s",
			      reason, *stat, *((u32 *) (stat + 1)),
			      "NO VALID SENSE");
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक sense data and related channel program.
 * Parts are prपूर्णांकed because prपूर्णांकk buffer is only 1024 bytes.
 */
अटल व्योम dasd_eckd_dump_sense_ccw(काष्ठा dasd_device *device,
				 काष्ठा dasd_ccw_req *req, काष्ठा irb *irb)
अणु
	अक्षर *page;
	काष्ठा ccw1 *first, *last, *fail, *from, *to;
	पूर्णांक len, sl, sct;

	page = (अक्षर *) get_zeroed_page(GFP_ATOMIC);
	अगर (page == शून्य) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "No memory to dump sense data\n");
		वापस;
	पूर्ण
	/* dump the sense data */
	len = प्र_लिखो(page, PRINTK_HEADER
		      " I/O status report for device %s:\n",
		      dev_name(&device->cdev->dev));
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " in req: %p CC:%02X FC:%02X AC:%02X SC:%02X DS:%02X "
		       "CS:%02X RC:%d\n",
		       req, scsw_cc(&irb->scsw), scsw_fctl(&irb->scsw),
		       scsw_actl(&irb->scsw), scsw_stctl(&irb->scsw),
		       scsw_dstat(&irb->scsw), scsw_cstat(&irb->scsw),
		       req ? req->पूर्णांकrc : 0);
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " device %s: Failing CCW: %p\n",
		       dev_name(&device->cdev->dev),
		       (व्योम *) (addr_t) irb->scsw.cmd.cpa);
	अगर (irb->esw.esw0.erw.cons) अणु
		क्रम (sl = 0; sl < 4; sl++) अणु
			len += प्र_लिखो(page + len, PRINTK_HEADER
				       " Sense(hex) %2d-%2d:",
				       (8 * sl), ((8 * sl) + 7));

			क्रम (sct = 0; sct < 8; sct++) अणु
				len += प्र_लिखो(page + len, " %02x",
					       irb->ecw[8 * sl + sct]);
			पूर्ण
			len += प्र_लिखो(page + len, "\n");
		पूर्ण

		अगर (irb->ecw[27] & DASD_SENSE_BIT_0) अणु
			/* 24 Byte Sense Data */
			प्र_लिखो(page + len, PRINTK_HEADER
				" 24 Byte: %x MSG %x, "
				"%s MSGb to SYSOP\n",
				irb->ecw[7] >> 4, irb->ecw[7] & 0x0f,
				irb->ecw[1] & 0x10 ? "" : "no");
		पूर्ण अन्यथा अणु
			/* 32 Byte Sense Data */
			प्र_लिखो(page + len, PRINTK_HEADER
				" 32 Byte: Format: %x "
				"Exception class %x\n",
				irb->ecw[6] & 0x0f, irb->ecw[22] >> 4);
		पूर्ण
	पूर्ण अन्यथा अणु
		प्र_लिखो(page + len, PRINTK_HEADER
			" SORRY - NO VALID SENSE AVAILABLE\n");
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s", page);

	अगर (req) अणु
		/* req == शून्य क्रम unsolicited पूर्णांकerrupts */
		/* dump the Channel Program (max 140 Bytes per line) */
		/* Count CCW and prपूर्णांक first CCWs (maximum 1024 % 140 = 7) */
		first = req->cpaddr;
		क्रम (last = first; last->flags & (CCW_FLAG_CC | CCW_FLAG_DC); last++);
		to = min(first + 6, last);
		len = प्र_लिखो(page, PRINTK_HEADER
			      " Related CP in req: %p\n", req);
		dasd_eckd_dump_ccw_range(first, to, page + len);
		prपूर्णांकk(KERN_ERR "%s", page);

		/* prपूर्णांक failing CCW area (maximum 4) */
		/* scsw->cda is either valid or zero  */
		len = 0;
		from = ++to;
		fail = (काष्ठा ccw1 *)(addr_t)
				irb->scsw.cmd.cpa; /* failing CCW */
		अगर (from <  fail - 2) अणु
			from = fail - 2;     /* there is a gap - prपूर्णांक header */
			len += प्र_लिखो(page, PRINTK_HEADER "......\n");
		पूर्ण
		to = min(fail + 1, last);
		len += dasd_eckd_dump_ccw_range(from, to, page + len);

		/* prपूर्णांक last CCWs (maximum 2) */
		from = max(from, ++to);
		अगर (from < last - 1) अणु
			from = last - 1;     /* there is a gap - prपूर्णांक header */
			len += प्र_लिखो(page + len, PRINTK_HEADER "......\n");
		पूर्ण
		len += dasd_eckd_dump_ccw_range(from, last, page + len);
		अगर (len > 0)
			prपूर्णांकk(KERN_ERR "%s", page);
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ) page);
पूर्ण


/*
 * Prपूर्णांक sense data from a tcw.
 */
अटल व्योम dasd_eckd_dump_sense_tcw(काष्ठा dasd_device *device,
				 काष्ठा dasd_ccw_req *req, काष्ठा irb *irb)
अणु
	अक्षर *page;
	पूर्णांक len, sl, sct, residual;
	काष्ठा tsb *tsb;
	u8 *sense, *rcq;

	page = (अक्षर *) get_zeroed_page(GFP_ATOMIC);
	अगर (page == शून्य) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, " %s",
			    "No memory to dump sense data");
		वापस;
	पूर्ण
	/* dump the sense data */
	len = प्र_लिखो(page, PRINTK_HEADER
		      " I/O status report for device %s:\n",
		      dev_name(&device->cdev->dev));
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " in req: %p CC:%02X FC:%02X AC:%02X SC:%02X DS:%02X "
		       "CS:%02X fcxs:%02X schxs:%02X RC:%d\n",
		       req, scsw_cc(&irb->scsw), scsw_fctl(&irb->scsw),
		       scsw_actl(&irb->scsw), scsw_stctl(&irb->scsw),
		       scsw_dstat(&irb->scsw), scsw_cstat(&irb->scsw),
		       irb->scsw.पंचांग.fcxs,
		       (irb->scsw.पंचांग.अगरob << 7) | irb->scsw.पंचांग.sesq,
		       req ? req->पूर्णांकrc : 0);
	len += प्र_लिखो(page + len, PRINTK_HEADER
		       " device %s: Failing TCW: %p\n",
		       dev_name(&device->cdev->dev),
		       (व्योम *) (addr_t) irb->scsw.पंचांग.tcw);

	tsb = शून्य;
	sense = शून्य;
	अगर (irb->scsw.पंचांग.tcw && (irb->scsw.पंचांग.fcxs & 0x01))
		tsb = tcw_get_tsb(
			(काष्ठा tcw *)(अचिन्हित दीर्घ)irb->scsw.पंचांग.tcw);

	अगर (tsb) अणु
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->length %d\n", tsb->length);
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->flags %x\n", tsb->flags);
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->dcw_offset %d\n", tsb->dcw_offset);
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->count %d\n", tsb->count);
		residual = tsb->count - 28;
		len += प्र_लिखो(page + len, PRINTK_HEADER
			       " residual %d\n", residual);

		चयन (tsb->flags & 0x07) अणु
		हाल 1:	/* tsa_iostat */
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.iostat.dev_time %d\n",
				       tsb->tsa.iostat.dev_समय);
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.iostat.def_time %d\n",
				       tsb->tsa.iostat.def_समय);
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.iostat.queue_time %d\n",
				       tsb->tsa.iostat.queue_समय);
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.iostat.dev_busy_time %d\n",
				       tsb->tsa.iostat.dev_busy_समय);
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.iostat.dev_act_time %d\n",
				       tsb->tsa.iostat.dev_act_समय);
			sense = tsb->tsa.iostat.sense;
			अवरोध;
		हाल 2: /* ts_ddpc */
			len += प्र_लिखो(page + len, PRINTK_HEADER
			       " tsb->tsa.ddpc.rc %d\n", tsb->tsa.ddpc.rc);
			क्रम (sl = 0; sl < 2; sl++) अणु
				len += प्र_लिखो(page + len, PRINTK_HEADER
					       " tsb->tsa.ddpc.rcq %2d-%2d: ",
					       (8 * sl), ((8 * sl) + 7));
				rcq = tsb->tsa.ddpc.rcq;
				क्रम (sct = 0; sct < 8; sct++) अणु
					len += प्र_लिखो(page + len, " %02x",
						       rcq[8 * sl + sct]);
				पूर्ण
				len += प्र_लिखो(page + len, "\n");
			पूर्ण
			sense = tsb->tsa.ddpc.sense;
			अवरोध;
		हाल 3: /* tsa_पूर्णांकrg */
			len += प्र_लिखो(page + len, PRINTK_HEADER
				      " tsb->tsa.intrg.: not supported yet\n");
			अवरोध;
		पूर्ण

		अगर (sense) अणु
			क्रम (sl = 0; sl < 4; sl++) अणु
				len += प्र_लिखो(page + len, PRINTK_HEADER
					       " Sense(hex) %2d-%2d:",
					       (8 * sl), ((8 * sl) + 7));
				क्रम (sct = 0; sct < 8; sct++) अणु
					len += प्र_लिखो(page + len, " %02x",
						       sense[8 * sl + sct]);
				पूर्ण
				len += प्र_लिखो(page + len, "\n");
			पूर्ण

			अगर (sense[27] & DASD_SENSE_BIT_0) अणु
				/* 24 Byte Sense Data */
				प्र_लिखो(page + len, PRINTK_HEADER
					" 24 Byte: %x MSG %x, "
					"%s MSGb to SYSOP\n",
					sense[7] >> 4, sense[7] & 0x0f,
					sense[1] & 0x10 ? "" : "no");
			पूर्ण अन्यथा अणु
				/* 32 Byte Sense Data */
				प्र_लिखो(page + len, PRINTK_HEADER
					" 32 Byte: Format: %x "
					"Exception class %x\n",
					sense[6] & 0x0f, sense[22] >> 4);
			पूर्ण
		पूर्ण अन्यथा अणु
			प्र_लिखो(page + len, PRINTK_HEADER
				" SORRY - NO VALID SENSE AVAILABLE\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		प्र_लिखो(page + len, PRINTK_HEADER
			" SORRY - NO TSB DATA AVAILABLE\n");
	पूर्ण
	prपूर्णांकk(KERN_ERR "%s", page);
	मुक्त_page((अचिन्हित दीर्घ) page);
पूर्ण

अटल व्योम dasd_eckd_dump_sense(काष्ठा dasd_device *device,
				 काष्ठा dasd_ccw_req *req, काष्ठा irb *irb)
अणु
	u8 *sense = dasd_get_sense(irb);

	अगर (scsw_is_पंचांग(&irb->scsw)) अणु
		/*
		 * In some हालs the 'File Protected' or 'Incorrect Length'
		 * error might be expected and log messages shouldn't be written
		 * then. Check अगर the according suppress bit is set.
		 */
		अगर (sense && (sense[1] & SNS1_खाता_PROTECTED) &&
		    test_bit(DASD_CQR_SUPPRESS_FP, &req->flags))
			वापस;
		अगर (scsw_cstat(&irb->scsw) == 0x40 &&
		    test_bit(DASD_CQR_SUPPRESS_IL, &req->flags))
			वापस;

		dasd_eckd_dump_sense_tcw(device, req, irb);
	पूर्ण अन्यथा अणु
		/*
		 * In some हालs the 'Command Reject' or 'No Record Found'
		 * error might be expected and log messages shouldn't be
		 * written then. Check अगर the according suppress bit is set.
		 */
		अगर (sense && sense[0] & SNS0_CMD_REJECT &&
		    test_bit(DASD_CQR_SUPPRESS_CR, &req->flags))
			वापस;

		अगर (sense && sense[1] & SNS1_NO_REC_FOUND &&
		    test_bit(DASD_CQR_SUPPRESS_NRF, &req->flags))
			वापस;

		dasd_eckd_dump_sense_ccw(device, req, irb);
	पूर्ण
पूर्ण

अटल पूर्णांक dasd_eckd_reload_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	पूर्णांक rc, old_base;
	अक्षर prपूर्णांक_uid[60];
	काष्ठा dasd_uid uid;
	अचिन्हित दीर्घ flags;

	/*
	 * हटाओ device from alias handling to prevent new requests
	 * from being scheduled on the wrong alias device
	 */
	dasd_alias_हटाओ_device(device);

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	old_base = निजी->uid.base_unit_addr;
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	/* Read Configuration Data */
	rc = dasd_eckd_पढ़ो_conf(device);
	अगर (rc)
		जाओ out_err;

	rc = dasd_eckd_generate_uid(device);
	अगर (rc)
		जाओ out_err;
	/*
	 * update unit address configuration and
	 * add device to alias management
	 */
	dasd_alias_update_add_device(device);

	dasd_eckd_get_uid(device, &uid);

	अगर (old_base != uid.base_unit_addr) अणु
		अगर (म_माप(uid.vduit) > 0)
			snम_लिखो(prपूर्णांक_uid, माप(prपूर्णांक_uid),
				 "%s.%s.%04x.%02x.%s", uid.venकरोr, uid.serial,
				 uid.ssid, uid.base_unit_addr, uid.vduit);
		अन्यथा
			snम_लिखो(prपूर्णांक_uid, माप(prपूर्णांक_uid),
				 "%s.%s.%04x.%02x", uid.venकरोr, uid.serial,
				 uid.ssid, uid.base_unit_addr);

		dev_info(&device->cdev->dev,
			 "An Alias device was reassigned to a new base device "
			 "with UID: %s\n", prपूर्णांक_uid);
	पूर्ण
	वापस 0;

out_err:
	वापस -1;
पूर्ण

अटल पूर्णांक dasd_eckd_पढ़ो_message_buffer(काष्ठा dasd_device *device,
					 काष्ठा dasd_rssd_messages *messages,
					 __u8 lpum)
अणु
	काष्ठा dasd_rssd_messages *message_buf;
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   (माप(काष्ठा dasd_psf_prssd_data) +
				    माप(काष्ठा dasd_rssd_messages)),
				   device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate read message buffer request");
		वापस PTR_ERR(cqr);
	पूर्ण

	cqr->lpm = lpum;
retry:
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->expires = 10 * HZ;
	set_bit(DASD_CQR_VERIFY_PATH, &cqr->flags);
	/* dasd_sleep_on_immediatly करोes not करो complex error
	 * recovery so clear erp flag and set retry counter to
	 * करो basic erp */
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	cqr->retries = 256;

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
	स_रखो(prssdp, 0, माप(काष्ठा dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = 0x03;	/* Message Buffer */
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(काष्ठा dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subप्रणाली Data - message buffer */
	message_buf = (काष्ठा dasd_rssd_messages *) (prssdp + 1);
	स_रखो(message_buf, 0, माप(काष्ठा dasd_rssd_messages));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(काष्ठा dasd_rssd_messages);
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t) message_buf;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	rc = dasd_sleep_on_immediatly(cqr);
	अगर (rc == 0) अणु
		prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
		message_buf = (काष्ठा dasd_rssd_messages *)
			(prssdp + 1);
		स_नकल(messages, message_buf,
		       माप(काष्ठा dasd_rssd_messages));
	पूर्ण अन्यथा अगर (cqr->lpm) अणु
		/*
		 * on z/VM we might not be able to करो I/O on the requested path
		 * but instead we get the required inक्रमmation on any path
		 * so retry with खोलो path mask
		 */
		cqr->lpm = 0;
		जाओ retry;
	पूर्ण अन्यथा
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Reading messages failed with rc=%d\n"
				, rc);
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

अटल पूर्णांक dasd_eckd_query_host_access(काष्ठा dasd_device *device,
				       काष्ठा dasd_psf_query_host_access *data)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा dasd_psf_query_host_access *host_access;
	काष्ठा dasd_psf_prssd_data *prssdp;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	/* not available क्रम HYPER PAV alias devices */
	अगर (!device->block && निजी->lcu->pav == HYPER_PAV)
		वापस -EOPNOTSUPP;

	/* may not be supported by the storage server */
	अगर (!(निजी->features.feature[14] & 0x80))
		वापस -EOPNOTSUPP;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* RSSD */,
				   माप(काष्ठा dasd_psf_prssd_data) + 1,
				   device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate read message buffer request");
		वापस PTR_ERR(cqr);
	पूर्ण
	host_access = kzalloc(माप(*host_access), GFP_KERNEL | GFP_DMA);
	अगर (!host_access) अणु
		dasd_sमुक्त_request(cqr, device);
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate host_access buffer");
		वापस -ENOMEM;
	पूर्ण
	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = 10 * HZ;

	/* Prepare क्रम Read Subप्रणाली Data */
	prssdp = (काष्ठा dasd_psf_prssd_data *) cqr->data;
	स_रखो(prssdp, 0, माप(काष्ठा dasd_psf_prssd_data));
	prssdp->order = PSF_ORDER_PRSSD;
	prssdp->suborder = PSF_SUBORDER_QHA;	/* query host access */
	/* LSS and Volume that will be queried */
	prssdp->lss = निजी->ned->ID;
	prssdp->volume = निजी->ned->unit_addr;
	/* all other bytes of prssdp must be zero */

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = माप(काष्ठा dasd_psf_prssd_data);
	ccw->flags |= CCW_FLAG_CC;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t) prssdp;

	/* Read Subप्रणाली Data - query host access */
	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_RSSD;
	ccw->count = माप(काष्ठा dasd_psf_query_host_access);
	ccw->flags |= CCW_FLAG_SLI;
	ccw->cda = (__u32)(addr_t) host_access;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	/* the command might not be supported, suppress error message */
	__set_bit(DASD_CQR_SUPPRESS_CR, &cqr->flags);
	rc = dasd_sleep_on_पूर्णांकerruptible(cqr);
	अगर (rc == 0) अणु
		*data = *host_access;
	पूर्ण अन्यथा अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev,
				"Reading host access data failed with rc=%d\n",
				rc);
		rc = -EOPNOTSUPP;
	पूर्ण

	dasd_sमुक्त_request(cqr, cqr->memdev);
	kमुक्त(host_access);
	वापस rc;
पूर्ण
/*
 * वापस number of grouped devices
 */
अटल पूर्णांक dasd_eckd_host_access_count(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_psf_query_host_access *access;
	काष्ठा dasd_ckd_path_group_entry *entry;
	काष्ठा dasd_ckd_host_inक्रमmation *info;
	पूर्णांक count = 0;
	पूर्णांक rc, i;

	access = kzalloc(माप(*access), GFP_NOIO);
	अगर (!access) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate access buffer");
		वापस -ENOMEM;
	पूर्ण
	rc = dasd_eckd_query_host_access(device, access);
	अगर (rc) अणु
		kमुक्त(access);
		वापस rc;
	पूर्ण

	info = (काष्ठा dasd_ckd_host_inक्रमmation *)
		access->host_access_inक्रमmation;
	क्रम (i = 0; i < info->entry_count; i++) अणु
		entry = (काष्ठा dasd_ckd_path_group_entry *)
			(info->entry + i * info->entry_size);
		अगर (entry->status_flags & DASD_ECKD_PG_GROUPED)
			count++;
	पूर्ण

	kमुक्त(access);
	वापस count;
पूर्ण

/*
 * ग_लिखो host access inक्रमmation to a sequential file
 */
अटल पूर्णांक dasd_hosts_prपूर्णांक(काष्ठा dasd_device *device, काष्ठा seq_file *m)
अणु
	काष्ठा dasd_psf_query_host_access *access;
	काष्ठा dasd_ckd_path_group_entry *entry;
	काष्ठा dasd_ckd_host_inक्रमmation *info;
	अक्षर sysplex[9] = "";
	पूर्णांक rc, i;

	access = kzalloc(माप(*access), GFP_NOIO);
	अगर (!access) अणु
		DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "%s",
				"Could not allocate access buffer");
		वापस -ENOMEM;
	पूर्ण
	rc = dasd_eckd_query_host_access(device, access);
	अगर (rc) अणु
		kमुक्त(access);
		वापस rc;
	पूर्ण

	info = (काष्ठा dasd_ckd_host_inक्रमmation *)
		access->host_access_inक्रमmation;
	क्रम (i = 0; i < info->entry_count; i++) अणु
		entry = (काष्ठा dasd_ckd_path_group_entry *)
			(info->entry + i * info->entry_size);
		/* PGID */
		seq_म_लिखो(m, "pgid %*phN\n", 11, entry->pgid);
		/* FLAGS */
		seq_म_लिखो(m, "status_flags %02x\n", entry->status_flags);
		/* SYSPLEX NAME */
		स_नकल(&sysplex, &entry->sysplex_name, माप(sysplex) - 1);
		EBCASC(sysplex, माप(sysplex));
		seq_म_लिखो(m, "sysplex_name %8s\n", sysplex);
		/* SUPPORTED CYLINDER */
		seq_म_लिखो(m, "supported_cylinder %d\n", entry->cylinder);
		/* TIMESTAMP */
		seq_म_लिखो(m, "timestamp %lu\n", (अचिन्हित दीर्घ)
			   entry->बारtamp);
	पूर्ण
	kमुक्त(access);

	वापस 0;
पूर्ण

/*
 * Perक्रमm Subप्रणाली Function - CUIR response
 */
अटल पूर्णांक
dasd_eckd_psf_cuir_response(काष्ठा dasd_device *device, पूर्णांक response,
			    __u32 message_id, __u8 lpum)
अणु
	काष्ठा dasd_psf_cuir_response *psf_cuir;
	पूर्णांक pos = pathmask_to_pos(lpum);
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* PSF */ ,
				   माप(काष्ठा dasd_psf_cuir_response),
				   device, शून्य);

	अगर (IS_ERR(cqr)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			   "Could not allocate PSF-CUIR request");
		वापस PTR_ERR(cqr);
	पूर्ण

	psf_cuir = (काष्ठा dasd_psf_cuir_response *)cqr->data;
	psf_cuir->order = PSF_ORDER_CUIR_RESPONSE;
	psf_cuir->cc = response;
	psf_cuir->chpid = device->path[pos].chpid;
	psf_cuir->message_id = message_id;
	psf_cuir->cssid = device->path[pos].cssid;
	psf_cuir->ssid = device->path[pos].ssid;
	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->cda = (__u32)(addr_t)psf_cuir;
	ccw->flags = CCW_FLAG_SLI;
	ccw->count = माप(काष्ठा dasd_psf_cuir_response);

	cqr->startdev = device;
	cqr->memdev = device;
	cqr->block = शून्य;
	cqr->retries = 256;
	cqr->expires = 10*HZ;
	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	set_bit(DASD_CQR_VERIFY_PATH, &cqr->flags);

	rc = dasd_sleep_on(cqr);

	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस rc;
पूर्ण

/*
 * वापस configuration data that is referenced by record selector
 * अगर a record selector is specअगरied or per शेष वापस the
 * conf_data poपूर्णांकer क्रम the path specअगरied by lpum
 */
अटल काष्ठा dasd_conf_data *dasd_eckd_get_ref_conf(काष्ठा dasd_device *device,
						     __u8 lpum,
						     काष्ठा dasd_cuir_message *cuir)
अणु
	काष्ठा dasd_conf_data *conf_data;
	पूर्णांक path, pos;

	अगर (cuir->record_selector == 0)
		जाओ out;
	क्रम (path = 0x80, pos = 0; path; path >>= 1, pos++) अणु
		conf_data = device->path[pos].conf_data;
		अगर (conf_data->gneq.record_selector ==
		    cuir->record_selector)
			वापस conf_data;
	पूर्ण
out:
	वापस device->path[pathmask_to_pos(lpum)].conf_data;
पूर्ण

/*
 * This function determines the scope of a reconfiguration request by
 * analysing the path and device selection data provided in the CUIR request.
 * Returns a path mask containing CUIR affected paths क्रम the give device.
 *
 * If the CUIR request करोes not contain the required inक्रमmation वापस the
 * path mask of the path the attention message क्रम the CUIR request was reveived
 * on.
 */
अटल पूर्णांक dasd_eckd_cuir_scope(काष्ठा dasd_device *device, __u8 lpum,
				काष्ठा dasd_cuir_message *cuir)
अणु
	काष्ठा dasd_conf_data *ref_conf_data;
	अचिन्हित दीर्घ biपंचांगask = 0, mask = 0;
	काष्ठा dasd_conf_data *conf_data;
	अचिन्हित पूर्णांक pos, path;
	अक्षर *ref_gneq, *gneq;
	अक्षर *ref_ned, *ned;
	पूर्णांक tbcpm = 0;

	/* अगर CUIR request करोes not specअगरy the scope use the path
	   the attention message was presented on */
	अगर (!cuir->ned_map ||
	    !(cuir->neq_map[0] | cuir->neq_map[1] | cuir->neq_map[2]))
		वापस lpum;

	/* get reference conf data */
	ref_conf_data = dasd_eckd_get_ref_conf(device, lpum, cuir);
	/* reference ned is determined by ned_map field */
	pos = 8 - ffs(cuir->ned_map);
	ref_ned = (अक्षर *)&ref_conf_data->neds[pos];
	ref_gneq = (अक्षर *)&ref_conf_data->gneq;
	/* transfer 24 bit neq_map to mask */
	mask = cuir->neq_map[2];
	mask |= cuir->neq_map[1] << 8;
	mask |= cuir->neq_map[0] << 16;

	क्रम (path = 0; path < 8; path++) अणु
		/* initialise data per path */
		biपंचांगask = mask;
		conf_data = device->path[path].conf_data;
		pos = 8 - ffs(cuir->ned_map);
		ned = (अक्षर *) &conf_data->neds[pos];
		/* compare reference ned and per path ned */
		अगर (स_भेद(ref_ned, ned, माप(*ned)) != 0)
			जारी;
		gneq = (अक्षर *)&conf_data->gneq;
		/* compare reference gneq and per_path gneq under
		   24 bit mask where mask bit 0 equals byte 7 of
		   the gneq and mask bit 24 equals byte 31 */
		जबतक (biपंचांगask) अणु
			pos = ffs(biपंचांगask) - 1;
			अगर (स_भेद(&ref_gneq[31 - pos], &gneq[31 - pos], 1)
			    != 0)
				अवरोध;
			clear_bit(pos, &biपंचांगask);
		पूर्ण
		अगर (biपंचांगask)
			जारी;
		/* device and path match the reference values
		   add path to CUIR scope */
		tbcpm |= 0x80 >> path;
	पूर्ण
	वापस tbcpm;
पूर्ण

अटल व्योम dasd_eckd_cuir_notअगरy_user(काष्ठा dasd_device *device,
				       अचिन्हित दीर्घ paths, पूर्णांक action)
अणु
	पूर्णांक pos;

	जबतक (paths) अणु
		/* get position of bit in mask */
		pos = 8 - ffs(paths);
		/* get channel path descriptor from this position */
		अगर (action == CUIR_QUIESCE)
			pr_warn("Service on the storage server caused path %x.%02x to go offline",
				device->path[pos].cssid,
				device->path[pos].chpid);
		अन्यथा अगर (action == CUIR_RESUME)
			pr_info("Path %x.%02x is back online after service on the storage server",
				device->path[pos].cssid,
				device->path[pos].chpid);
		clear_bit(7 - pos, &paths);
	पूर्ण
पूर्ण

अटल पूर्णांक dasd_eckd_cuir_हटाओ_path(काष्ठा dasd_device *device, __u8 lpum,
				      काष्ठा dasd_cuir_message *cuir)
अणु
	अचिन्हित दीर्घ tbcpm;

	tbcpm = dasd_eckd_cuir_scope(device, lpum, cuir);
	/* nothing to करो अगर path is not in use */
	अगर (!(dasd_path_get_opm(device) & tbcpm))
		वापस 0;
	अगर (!(dasd_path_get_opm(device) & ~tbcpm)) अणु
		/* no path would be left अगर the CUIR action is taken
		   वापस error */
		वापस -EINVAL;
	पूर्ण
	/* हटाओ device from operational path mask */
	dasd_path_हटाओ_opm(device, tbcpm);
	dasd_path_add_cuirpm(device, tbcpm);
	वापस tbcpm;
पूर्ण

/*
 * walk through all devices and build a path mask to quiesce them
 * वापस an error अगर the last path to a device would be हटाओd
 *
 * अगर only part of the devices are quiesced and an error
 * occurs no onlining necessary, the storage server will
 * notअगरy the alपढ़ोy set offline devices again
 */
अटल पूर्णांक dasd_eckd_cuir_quiesce(काष्ठा dasd_device *device, __u8 lpum,
				  काष्ठा dasd_cuir_message *cuir)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_pav_group *pavgroup, *tempgroup;
	काष्ठा dasd_device *dev, *n;
	अचिन्हित दीर्घ paths = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक tbcpm;

	/* active devices */
	list_क्रम_each_entry_safe(dev, n, &निजी->lcu->active_devices,
				 alias_list) अणु
		spin_lock_irqsave(get_ccwdev_lock(dev->cdev), flags);
		tbcpm = dasd_eckd_cuir_हटाओ_path(dev, lpum, cuir);
		spin_unlock_irqrestore(get_ccwdev_lock(dev->cdev), flags);
		अगर (tbcpm < 0)
			जाओ out_err;
		paths |= tbcpm;
	पूर्ण
	/* inactive devices */
	list_क्रम_each_entry_safe(dev, n, &निजी->lcu->inactive_devices,
				 alias_list) अणु
		spin_lock_irqsave(get_ccwdev_lock(dev->cdev), flags);
		tbcpm = dasd_eckd_cuir_हटाओ_path(dev, lpum, cuir);
		spin_unlock_irqrestore(get_ccwdev_lock(dev->cdev), flags);
		अगर (tbcpm < 0)
			जाओ out_err;
		paths |= tbcpm;
	पूर्ण
	/* devices in PAV groups */
	list_क्रम_each_entry_safe(pavgroup, tempgroup,
				 &निजी->lcu->grouplist, group) अणु
		list_क्रम_each_entry_safe(dev, n, &pavgroup->baselist,
					 alias_list) अणु
			spin_lock_irqsave(get_ccwdev_lock(dev->cdev), flags);
			tbcpm = dasd_eckd_cuir_हटाओ_path(dev, lpum, cuir);
			spin_unlock_irqrestore(
				get_ccwdev_lock(dev->cdev), flags);
			अगर (tbcpm < 0)
				जाओ out_err;
			paths |= tbcpm;
		पूर्ण
		list_क्रम_each_entry_safe(dev, n, &pavgroup->aliaslist,
					 alias_list) अणु
			spin_lock_irqsave(get_ccwdev_lock(dev->cdev), flags);
			tbcpm = dasd_eckd_cuir_हटाओ_path(dev, lpum, cuir);
			spin_unlock_irqrestore(
				get_ccwdev_lock(dev->cdev), flags);
			अगर (tbcpm < 0)
				जाओ out_err;
			paths |= tbcpm;
		पूर्ण
	पूर्ण
	/* notअगरy user about all paths affected by CUIR action */
	dasd_eckd_cuir_notअगरy_user(device, paths, CUIR_QUIESCE);
	वापस 0;
out_err:
	वापस tbcpm;
पूर्ण

अटल पूर्णांक dasd_eckd_cuir_resume(काष्ठा dasd_device *device, __u8 lpum,
				 काष्ठा dasd_cuir_message *cuir)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_pav_group *pavgroup, *tempgroup;
	काष्ठा dasd_device *dev, *n;
	अचिन्हित दीर्घ paths = 0;
	पूर्णांक tbcpm;

	/*
	 * the path may have been added through a generic path event beक्रमe
	 * only trigger path verअगरication अगर the path is not alपढ़ोy in use
	 */
	list_क्रम_each_entry_safe(dev, n,
				 &निजी->lcu->active_devices,
				 alias_list) अणु
		tbcpm = dasd_eckd_cuir_scope(dev, lpum, cuir);
		paths |= tbcpm;
		अगर (!(dasd_path_get_opm(dev) & tbcpm)) अणु
			dasd_path_add_tbvpm(dev, tbcpm);
			dasd_schedule_device_bh(dev);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(dev, n,
				 &निजी->lcu->inactive_devices,
				 alias_list) अणु
		tbcpm = dasd_eckd_cuir_scope(dev, lpum, cuir);
		paths |= tbcpm;
		अगर (!(dasd_path_get_opm(dev) & tbcpm)) अणु
			dasd_path_add_tbvpm(dev, tbcpm);
			dasd_schedule_device_bh(dev);
		पूर्ण
	पूर्ण
	/* devices in PAV groups */
	list_क्रम_each_entry_safe(pavgroup, tempgroup,
				 &निजी->lcu->grouplist,
				 group) अणु
		list_क्रम_each_entry_safe(dev, n,
					 &pavgroup->baselist,
					 alias_list) अणु
			tbcpm = dasd_eckd_cuir_scope(dev, lpum, cuir);
			paths |= tbcpm;
			अगर (!(dasd_path_get_opm(dev) & tbcpm)) अणु
				dasd_path_add_tbvpm(dev, tbcpm);
				dasd_schedule_device_bh(dev);
			पूर्ण
		पूर्ण
		list_क्रम_each_entry_safe(dev, n,
					 &pavgroup->aliaslist,
					 alias_list) अणु
			tbcpm = dasd_eckd_cuir_scope(dev, lpum, cuir);
			paths |= tbcpm;
			अगर (!(dasd_path_get_opm(dev) & tbcpm)) अणु
				dasd_path_add_tbvpm(dev, tbcpm);
				dasd_schedule_device_bh(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	/* notअगरy user about all paths affected by CUIR action */
	dasd_eckd_cuir_notअगरy_user(device, paths, CUIR_RESUME);
	वापस 0;
पूर्ण

अटल व्योम dasd_eckd_handle_cuir(काष्ठा dasd_device *device, व्योम *messages,
				 __u8 lpum)
अणु
	काष्ठा dasd_cuir_message *cuir = messages;
	पूर्णांक response;

	DBF_DEV_EVENT(DBF_WARNING, device,
		      "CUIR request: %016llx %016llx %016llx %08x",
		      ((u64 *)cuir)[0], ((u64 *)cuir)[1], ((u64 *)cuir)[2],
		      ((u32 *)cuir)[3]);

	अगर (cuir->code == CUIR_QUIESCE) अणु
		/* quiesce */
		अगर (dasd_eckd_cuir_quiesce(device, lpum, cuir))
			response = PSF_CUIR_LAST_PATH;
		अन्यथा
			response = PSF_CUIR_COMPLETED;
	पूर्ण अन्यथा अगर (cuir->code == CUIR_RESUME) अणु
		/* resume */
		dasd_eckd_cuir_resume(device, lpum, cuir);
		response = PSF_CUIR_COMPLETED;
	पूर्ण अन्यथा
		response = PSF_CUIR_NOT_SUPPORTED;

	dasd_eckd_psf_cuir_response(device, response,
				    cuir->message_id, lpum);
	DBF_DEV_EVENT(DBF_WARNING, device,
		      "CUIR response: %d on message ID %08x", response,
		      cuir->message_id);
	/* to make sure there is no attention left schedule work again */
	device->discipline->check_attention(device, lpum);
पूर्ण

अटल व्योम dasd_eckd_oos_resume(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;
	काष्ठा alias_pav_group *pavgroup, *tempgroup;
	काष्ठा dasd_device *dev, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&निजी->lcu->lock, flags);
	list_क्रम_each_entry_safe(dev, n, &निजी->lcu->active_devices,
				 alias_list) अणु
		अगर (dev->stopped & DASD_STOPPED_NOSPC)
			dasd_generic_space_avail(dev);
	पूर्ण
	list_क्रम_each_entry_safe(dev, n, &निजी->lcu->inactive_devices,
				 alias_list) अणु
		अगर (dev->stopped & DASD_STOPPED_NOSPC)
			dasd_generic_space_avail(dev);
	पूर्ण
	/* devices in PAV groups */
	list_क्रम_each_entry_safe(pavgroup, tempgroup,
				 &निजी->lcu->grouplist,
				 group) अणु
		list_क्रम_each_entry_safe(dev, n, &pavgroup->baselist,
					 alias_list) अणु
			अगर (dev->stopped & DASD_STOPPED_NOSPC)
				dasd_generic_space_avail(dev);
		पूर्ण
		list_क्रम_each_entry_safe(dev, n, &pavgroup->aliaslist,
					 alias_list) अणु
			अगर (dev->stopped & DASD_STOPPED_NOSPC)
				dasd_generic_space_avail(dev);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&निजी->lcu->lock, flags);
पूर्ण

अटल व्योम dasd_eckd_handle_oos(काष्ठा dasd_device *device, व्योम *messages,
				 __u8 lpum)
अणु
	काष्ठा dasd_oos_message *oos = messages;

	चयन (oos->code) अणु
	हाल REPO_WARN:
	हाल POOL_WARN:
		dev_warn(&device->cdev->dev,
			 "Extent pool usage has reached a critical value\n");
		dasd_eckd_oos_resume(device);
		अवरोध;
	हाल REPO_EXHAUST:
	हाल POOL_EXHAUST:
		dev_warn(&device->cdev->dev,
			 "Extent pool is exhausted\n");
		अवरोध;
	हाल REPO_RELIEVE:
	हाल POOL_RELIEVE:
		dev_info(&device->cdev->dev,
			 "Extent pool physical space constraint has been relieved\n");
		अवरोध;
	पूर्ण

	/* In any हाल, update related data */
	dasd_eckd_पढ़ो_ext_pool_info(device);

	/* to make sure there is no attention left schedule work again */
	device->discipline->check_attention(device, lpum);
पूर्ण

अटल व्योम dasd_eckd_check_attention_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा check_attention_work_data *data;
	काष्ठा dasd_rssd_messages *messages;
	काष्ठा dasd_device *device;
	पूर्णांक rc;

	data = container_of(work, काष्ठा check_attention_work_data, worker);
	device = data->device;
	messages = kzalloc(माप(*messages), GFP_KERNEL);
	अगर (!messages) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "Could not allocate attention message buffer");
		जाओ out;
	पूर्ण
	rc = dasd_eckd_पढ़ो_message_buffer(device, messages, data->lpum);
	अगर (rc)
		जाओ out;

	अगर (messages->length == ATTENTION_LENGTH_CUIR &&
	    messages->क्रमmat == ATTENTION_FORMAT_CUIR)
		dasd_eckd_handle_cuir(device, messages, data->lpum);
	अगर (messages->length == ATTENTION_LENGTH_OOS &&
	    messages->क्रमmat == ATTENTION_FORMAT_OOS)
		dasd_eckd_handle_oos(device, messages, data->lpum);

out:
	dasd_put_device(device);
	kमुक्त(messages);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक dasd_eckd_check_attention(काष्ठा dasd_device *device, __u8 lpum)
अणु
	काष्ठा check_attention_work_data *data;

	data = kzalloc(माप(*data), GFP_ATOMIC);
	अगर (!data)
		वापस -ENOMEM;
	INIT_WORK(&data->worker, dasd_eckd_check_attention_work);
	dasd_get_device(device);
	data->device = device;
	data->lpum = lpum;
	schedule_work(&data->worker);
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_eckd_disable_hpf_path(काष्ठा dasd_device *device, __u8 lpum)
अणु
	अगर (~lpum & dasd_path_get_opm(device)) अणु
		dasd_path_add_nohpfpm(device, lpum);
		dasd_path_हटाओ_opm(device, lpum);
		dev_err(&device->cdev->dev,
			"Channel path %02X lost HPF functionality and is disabled\n",
			lpum);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dasd_eckd_disable_hpf_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	dev_err(&device->cdev->dev,
		"High Performance FICON disabled\n");
	निजी->fcx_max_data = 0;
पूर्ण

अटल पूर्णांक dasd_eckd_hpf_enabled(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	वापस निजी->fcx_max_data ? 1 : 0;
पूर्ण

अटल व्योम dasd_eckd_handle_hpf_error(काष्ठा dasd_device *device,
				       काष्ठा irb *irb)
अणु
	काष्ठा dasd_eckd_निजी *निजी = device->निजी;

	अगर (!निजी->fcx_max_data) अणु
		/* sanity check क्रम no HPF, the error makes no sense */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "Trying to disable HPF for a non HPF device");
		वापस;
	पूर्ण
	अगर (irb->scsw.पंचांग.sesq == SCSW_SESQ_DEV_NOFCX) अणु
		dasd_eckd_disable_hpf_device(device);
	पूर्ण अन्यथा अगर (irb->scsw.पंचांग.sesq == SCSW_SESQ_PATH_NOFCX) अणु
		अगर (dasd_eckd_disable_hpf_path(device, irb->esw.esw1.lpum))
			वापस;
		dasd_eckd_disable_hpf_device(device);
		dasd_path_set_tbvpm(device,
				  dasd_path_get_hpfpm(device));
	पूर्ण
	/*
	 * prevent that any new I/O ist started on the device and schedule a
	 * requeue of existing requests
	 */
	dasd_device_set_stop_bits(device, DASD_STOPPED_NOT_ACC);
	dasd_schedule_requeue(device);
पूर्ण

/*
 * Initialize block layer request queue.
 */
अटल व्योम dasd_eckd_setup_blk_queue(काष्ठा dasd_block *block)
अणु
	अचिन्हित पूर्णांक logical_block_size = block->bp_block;
	काष्ठा request_queue *q = block->request_queue;
	काष्ठा dasd_device *device = block->base;
	पूर्णांक max;

	अगर (device->features & DASD_FEATURE_USERAW) अणु
		/*
		 * the max_blocks value क्रम raw_track access is 256
		 * it is higher than the native ECKD value because we
		 * only need one ccw per track
		 * so the max_hw_sectors are
		 * 2048 x 512B = 1024kB = 16 tracks
		 */
		max = DASD_ECKD_MAX_BLOCKS_RAW << block->s2b_shअगरt;
	पूर्ण अन्यथा अणु
		max = DASD_ECKD_MAX_BLOCKS << block->s2b_shअगरt;
	पूर्ण
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	q->limits.max_dev_sectors = max;
	blk_queue_logical_block_size(q, logical_block_size);
	blk_queue_max_hw_sectors(q, max);
	blk_queue_max_segments(q, अच_लघु_उच्च);
	/* With page sized segments each segment can be translated पूर्णांकo one idaw/tidaw */
	blk_queue_max_segment_size(q, PAGE_SIZE);
	blk_queue_segment_boundary(q, PAGE_SIZE - 1);
पूर्ण

अटल काष्ठा ccw_driver dasd_eckd_driver = अणु
	.driver = अणु
		.name	= "dasd-eckd",
		.owner	= THIS_MODULE,
		.dev_groups = dasd_dev_groups,
	पूर्ण,
	.ids	     = dasd_eckd_ids,
	.probe	     = dasd_eckd_probe,
	.हटाओ      = dasd_generic_हटाओ,
	.set_offline = dasd_generic_set_offline,
	.set_online  = dasd_eckd_set_online,
	.notअगरy      = dasd_generic_notअगरy,
	.path_event  = dasd_generic_path_event,
	.shutकरोwn    = dasd_generic_shutकरोwn,
	.uc_handler  = dasd_generic_uc_handler,
	.पूर्णांक_class   = IRQIO_DAS,
पूर्ण;

अटल काष्ठा dasd_discipline dasd_eckd_discipline = अणु
	.owner = THIS_MODULE,
	.name = "ECKD",
	.ebcname = "ECKD",
	.check_device = dasd_eckd_check_अक्षरacteristics,
	.uncheck_device = dasd_eckd_uncheck_device,
	.करो_analysis = dasd_eckd_करो_analysis,
	.pe_handler = dasd_eckd_pe_handler,
	.basic_to_पढ़ोy = dasd_eckd_basic_to_पढ़ोy,
	.online_to_पढ़ोy = dasd_eckd_online_to_पढ़ोy,
	.basic_to_known = dasd_eckd_basic_to_known,
	.setup_blk_queue = dasd_eckd_setup_blk_queue,
	.fill_geometry = dasd_eckd_fill_geometry,
	.start_IO = dasd_start_IO,
	.term_IO = dasd_term_IO,
	.handle_terminated_request = dasd_eckd_handle_terminated_request,
	.क्रमmat_device = dasd_eckd_क्रमmat_device,
	.check_device_क्रमmat = dasd_eckd_check_device_क्रमmat,
	.erp_action = dasd_eckd_erp_action,
	.erp_postaction = dasd_eckd_erp_postaction,
	.check_क्रम_device_change = dasd_eckd_check_क्रम_device_change,
	.build_cp = dasd_eckd_build_alias_cp,
	.मुक्त_cp = dasd_eckd_मुक्त_alias_cp,
	.dump_sense = dasd_eckd_dump_sense,
	.dump_sense_dbf = dasd_eckd_dump_sense_dbf,
	.fill_info = dasd_eckd_fill_info,
	.ioctl = dasd_eckd_ioctl,
	.reload = dasd_eckd_reload_device,
	.get_uid = dasd_eckd_get_uid,
	.kick_validate = dasd_eckd_kick_validate_server,
	.check_attention = dasd_eckd_check_attention,
	.host_access_count = dasd_eckd_host_access_count,
	.hosts_prपूर्णांक = dasd_hosts_prपूर्णांक,
	.handle_hpf_error = dasd_eckd_handle_hpf_error,
	.disable_hpf = dasd_eckd_disable_hpf_device,
	.hpf_enabled = dasd_eckd_hpf_enabled,
	.reset_path = dasd_eckd_reset_path,
	.is_ese = dasd_eckd_is_ese,
	.space_allocated = dasd_eckd_space_allocated,
	.space_configured = dasd_eckd_space_configured,
	.logical_capacity = dasd_eckd_logical_capacity,
	.release_space = dasd_eckd_release_space,
	.ext_pool_id = dasd_eckd_ext_pool_id,
	.ext_size = dasd_eckd_ext_size,
	.ext_pool_cap_at_warnlevel = dasd_eckd_ext_pool_cap_at_warnlevel,
	.ext_pool_warn_thrshld = dasd_eckd_ext_pool_warn_thrshld,
	.ext_pool_oos = dasd_eckd_ext_pool_oos,
	.ext_pool_exhaust = dasd_eckd_ext_pool_exhaust,
	.ese_क्रमmat = dasd_eckd_ese_क्रमmat,
	.ese_पढ़ो = dasd_eckd_ese_पढ़ो,
पूर्ण;

अटल पूर्णांक __init
dasd_eckd_init(व्योम)
अणु
	पूर्णांक ret;

	ASCEBC(dasd_eckd_discipline.ebcname, 4);
	dasd_reserve_req = kदो_स्मृति(माप(*dasd_reserve_req),
				   GFP_KERNEL | GFP_DMA);
	अगर (!dasd_reserve_req)
		वापस -ENOMEM;
	dasd_vol_info_req = kदो_स्मृति(माप(*dasd_vol_info_req),
				    GFP_KERNEL | GFP_DMA);
	अगर (!dasd_vol_info_req)
		वापस -ENOMEM;
	pe_handler_worker = kदो_स्मृति(माप(*pe_handler_worker),
				    GFP_KERNEL | GFP_DMA);
	अगर (!pe_handler_worker) अणु
		kमुक्त(dasd_reserve_req);
		kमुक्त(dasd_vol_info_req);
		वापस -ENOMEM;
	पूर्ण
	rawpadpage = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!rawpadpage) अणु
		kमुक्त(pe_handler_worker);
		kमुक्त(dasd_reserve_req);
		kमुक्त(dasd_vol_info_req);
		वापस -ENOMEM;
	पूर्ण
	ret = ccw_driver_रेजिस्टर(&dasd_eckd_driver);
	अगर (!ret)
		रुको_क्रम_device_probe();
	अन्यथा अणु
		kमुक्त(pe_handler_worker);
		kमुक्त(dasd_reserve_req);
		kमुक्त(dasd_vol_info_req);
		मुक्त_page((अचिन्हित दीर्घ)rawpadpage);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास
dasd_eckd_cleanup(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&dasd_eckd_driver);
	kमुक्त(pe_handler_worker);
	kमुक्त(dasd_reserve_req);
	मुक्त_page((अचिन्हित दीर्घ)rawpadpage);
पूर्ण

module_init(dasd_eckd_init);
module_निकास(dasd_eckd_cleanup);
