<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software (UK) Limited.
 * Copyright (C) 2004, 2010-2011 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/device-mapper.h>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>

#घोषणा DM_MSG_PREFIX "flakey"

#घोषणा all_corrupt_bio_flags_match(bio, fc)	\
	(((bio)->bi_opf & (fc)->corrupt_bio_flags) == (fc)->corrupt_bio_flags)

/*
 * Flakey: Used क्रम testing only, simulates पूर्णांकermittent,
 * catastrophic device failure.
 */
काष्ठा flakey_c अणु
	काष्ठा dm_dev *dev;
	अचिन्हित दीर्घ start_समय;
	sector_t start;
	अचिन्हित up_पूर्णांकerval;
	अचिन्हित करोwn_पूर्णांकerval;
	अचिन्हित दीर्घ flags;
	अचिन्हित corrupt_bio_byte;
	अचिन्हित corrupt_bio_rw;
	अचिन्हित corrupt_bio_value;
	अचिन्हित corrupt_bio_flags;
पूर्ण;

क्रमागत feature_flag_bits अणु
	DROP_WRITES,
	ERROR_WRITES
पूर्ण;

काष्ठा per_bio_data अणु
	bool bio_submitted;
पूर्ण;

अटल पूर्णांक parse_features(काष्ठा dm_arg_set *as, काष्ठा flakey_c *fc,
			  काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	अचिन्हित argc;
	स्थिर अक्षर *arg_name;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 6, "Invalid number of feature args"पूर्ण,
		अणु1, अच_पूर्णांक_उच्च, "Invalid corrupt bio byte"पूर्ण,
		अणु0, 255, "Invalid corrupt value to write into bio byte (0-255)"पूर्ण,
		अणु0, अच_पूर्णांक_उच्च, "Invalid corrupt bio flags mask"पूर्ण,
	पूर्ण;

	/* No feature arguments supplied. */
	अगर (!as->argc)
		वापस 0;

	r = dm_पढ़ो_arg_group(_args, as, &argc, &ti->error);
	अगर (r)
		वापस r;

	जबतक (argc) अणु
		arg_name = dm_shअगरt_arg(as);
		argc--;

		अगर (!arg_name) अणु
			ti->error = "Insufficient feature arguments";
			वापस -EINVAL;
		पूर्ण

		/*
		 * drop_ग_लिखोs
		 */
		अगर (!strहालcmp(arg_name, "drop_writes")) अणु
			अगर (test_and_set_bit(DROP_WRITES, &fc->flags)) अणु
				ti->error = "Feature drop_writes duplicated";
				वापस -EINVAL;
			पूर्ण अन्यथा अगर (test_bit(ERROR_WRITES, &fc->flags)) अणु
				ti->error = "Feature drop_writes conflicts with feature error_writes";
				वापस -EINVAL;
			पूर्ण

			जारी;
		पूर्ण

		/*
		 * error_ग_लिखोs
		 */
		अगर (!strहालcmp(arg_name, "error_writes")) अणु
			अगर (test_and_set_bit(ERROR_WRITES, &fc->flags)) अणु
				ti->error = "Feature error_writes duplicated";
				वापस -EINVAL;

			पूर्ण अन्यथा अगर (test_bit(DROP_WRITES, &fc->flags)) अणु
				ti->error = "Feature error_writes conflicts with feature drop_writes";
				वापस -EINVAL;
			पूर्ण

			जारी;
		पूर्ण

		/*
		 * corrupt_bio_byte <Nth_byte> <direction> <value> <bio_flags>
		 */
		अगर (!strहालcmp(arg_name, "corrupt_bio_byte")) अणु
			अगर (!argc) अणु
				ti->error = "Feature corrupt_bio_byte requires parameters";
				वापस -EINVAL;
			पूर्ण

			r = dm_पढ़ो_arg(_args + 1, as, &fc->corrupt_bio_byte, &ti->error);
			अगर (r)
				वापस r;
			argc--;

			/*
			 * Direction r or w?
			 */
			arg_name = dm_shअगरt_arg(as);
			अगर (!strहालcmp(arg_name, "w"))
				fc->corrupt_bio_rw = WRITE;
			अन्यथा अगर (!strहालcmp(arg_name, "r"))
				fc->corrupt_bio_rw = READ;
			अन्यथा अणु
				ti->error = "Invalid corrupt bio direction (r or w)";
				वापस -EINVAL;
			पूर्ण
			argc--;

			/*
			 * Value of byte (0-255) to ग_लिखो in place of correct one.
			 */
			r = dm_पढ़ो_arg(_args + 2, as, &fc->corrupt_bio_value, &ti->error);
			अगर (r)
				वापस r;
			argc--;

			/*
			 * Only corrupt bios with these flags set.
			 */
			r = dm_पढ़ो_arg(_args + 3, as, &fc->corrupt_bio_flags, &ti->error);
			अगर (r)
				वापस r;
			argc--;

			जारी;
		पूर्ण

		ti->error = "Unrecognised flakey feature requested";
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(DROP_WRITES, &fc->flags) && (fc->corrupt_bio_rw == WRITE)) अणु
		ti->error = "drop_writes is incompatible with corrupt_bio_byte with the WRITE flag set";
		वापस -EINVAL;

	पूर्ण अन्यथा अगर (test_bit(ERROR_WRITES, &fc->flags) && (fc->corrupt_bio_rw == WRITE)) अणु
		ti->error = "error_writes is incompatible with corrupt_bio_byte with the WRITE flag set";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Conकाष्ठा a flakey mapping:
 * <dev_path> <offset> <up पूर्णांकerval> <करोwn पूर्णांकerval> [<#feature args> [<arg>]*]
 *
 *   Feature args:
 *     [drop_ग_लिखोs]
 *     [corrupt_bio_byte <Nth_byte> <direction> <value> <bio_flags>]
 *
 *   Nth_byte starts from 1 क्रम the first byte.
 *   Direction is r क्रम READ or w क्रम WRITE.
 *   bio_flags is ignored अगर 0.
 */
अटल पूर्णांक flakey_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, अच_पूर्णांक_उच्च, "Invalid up interval"पूर्ण,
		अणु0, अच_पूर्णांक_उच्च, "Invalid down interval"पूर्ण,
	पूर्ण;

	पूर्णांक r;
	काष्ठा flakey_c *fc;
	अचिन्हित दीर्घ दीर्घ पंचांगpll;
	काष्ठा dm_arg_set as;
	स्थिर अक्षर *devname;
	अक्षर dummy;

	as.argc = argc;
	as.argv = argv;

	अगर (argc < 4) अणु
		ti->error = "Invalid argument count";
		वापस -EINVAL;
	पूर्ण

	fc = kzalloc(माप(*fc), GFP_KERNEL);
	अगर (!fc) अणु
		ti->error = "Cannot allocate context";
		वापस -ENOMEM;
	पूर्ण
	fc->start_समय = jअगरfies;

	devname = dm_shअगरt_arg(&as);

	r = -EINVAL;
	अगर (माला_पूछो(dm_shअगरt_arg(&as), "%llu%c", &पंचांगpll, &dummy) != 1 || पंचांगpll != (sector_t)पंचांगpll) अणु
		ti->error = "Invalid device sector";
		जाओ bad;
	पूर्ण
	fc->start = पंचांगpll;

	r = dm_पढ़ो_arg(_args, &as, &fc->up_पूर्णांकerval, &ti->error);
	अगर (r)
		जाओ bad;

	r = dm_पढ़ो_arg(_args, &as, &fc->करोwn_पूर्णांकerval, &ti->error);
	अगर (r)
		जाओ bad;

	अगर (!(fc->up_पूर्णांकerval + fc->करोwn_पूर्णांकerval)) अणु
		ti->error = "Total (up + down) interval is zero";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (fc->up_पूर्णांकerval + fc->करोwn_पूर्णांकerval < fc->up_पूर्णांकerval) अणु
		ti->error = "Interval overflow";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	r = parse_features(&as, fc, ti);
	अगर (r)
		जाओ bad;

	r = dm_get_device(ti, devname, dm_table_get_mode(ti->table), &fc->dev);
	अगर (r) अणु
		ti->error = "Device lookup failed";
		जाओ bad;
	पूर्ण

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->per_io_data_size = माप(काष्ठा per_bio_data);
	ti->निजी = fc;
	वापस 0;

bad:
	kमुक्त(fc);
	वापस r;
पूर्ण

अटल व्योम flakey_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा flakey_c *fc = ti->निजी;

	dm_put_device(ti, fc->dev);
	kमुक्त(fc);
पूर्ण

अटल sector_t flakey_map_sector(काष्ठा dm_target *ti, sector_t bi_sector)
अणु
	काष्ठा flakey_c *fc = ti->निजी;

	वापस fc->start + dm_target_offset(ti, bi_sector);
पूर्ण

अटल व्योम flakey_map_bio(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा flakey_c *fc = ti->निजी;

	bio_set_dev(bio, fc->dev->bdev);
	अगर (bio_sectors(bio) || op_is_zone_mgmt(bio_op(bio)))
		bio->bi_iter.bi_sector =
			flakey_map_sector(ti, bio->bi_iter.bi_sector);
पूर्ण

अटल व्योम corrupt_bio_data(काष्ठा bio *bio, काष्ठा flakey_c *fc)
अणु
	अचिन्हित पूर्णांक corrupt_bio_byte = fc->corrupt_bio_byte - 1;

	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bvec;

	अगर (!bio_has_data(bio))
		वापस;

	/*
	 * Overग_लिखो the Nth byte of the bio's data, on whichever page
	 * it falls.
	 */
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अगर (bio_iter_len(bio, iter) > corrupt_bio_byte) अणु
			अक्षर *segment = (page_address(bio_iter_page(bio, iter))
					 + bio_iter_offset(bio, iter));
			segment[corrupt_bio_byte] = fc->corrupt_bio_value;
			DMDEBUG("Corrupting data bio=%p by writing %u to byte %u "
				"(rw=%c bi_opf=%u bi_sector=%llu size=%u)\n",
				bio, fc->corrupt_bio_value, fc->corrupt_bio_byte,
				(bio_data_dir(bio) == WRITE) ? 'w' : 'r', bio->bi_opf,
				(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector, bio->bi_iter.bi_size);
			अवरोध;
		पूर्ण
		corrupt_bio_byte -= bio_iter_len(bio, iter);
	पूर्ण
पूर्ण

अटल पूर्णांक flakey_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा flakey_c *fc = ti->निजी;
	अचिन्हित elapsed;
	काष्ठा per_bio_data *pb = dm_per_bio_data(bio, माप(काष्ठा per_bio_data));
	pb->bio_submitted = false;

	अगर (op_is_zone_mgmt(bio_op(bio)))
		जाओ map_bio;

	/* Are we alive ? */
	elapsed = (jअगरfies - fc->start_समय) / HZ;
	अगर (elapsed % (fc->up_पूर्णांकerval + fc->करोwn_पूर्णांकerval) >= fc->up_पूर्णांकerval) अणु
		/*
		 * Flag this bio as submitted जबतक करोwn.
		 */
		pb->bio_submitted = true;

		/*
		 * Error पढ़ोs अगर neither corrupt_bio_byte or drop_ग_लिखोs or error_ग_लिखोs are set.
		 * Otherwise, flakey_end_io() will decide अगर the पढ़ोs should be modअगरied.
		 */
		अगर (bio_data_dir(bio) == READ) अणु
			अगर (!fc->corrupt_bio_byte && !test_bit(DROP_WRITES, &fc->flags) &&
			    !test_bit(ERROR_WRITES, &fc->flags))
				वापस DM_MAPIO_KILL;
			जाओ map_bio;
		पूर्ण

		/*
		 * Drop or error ग_लिखोs?
		 */
		अगर (test_bit(DROP_WRITES, &fc->flags)) अणु
			bio_endio(bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण
		अन्यथा अगर (test_bit(ERROR_WRITES, &fc->flags)) अणु
			bio_io_error(bio);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण

		/*
		 * Corrupt matching ग_लिखोs.
		 */
		अगर (fc->corrupt_bio_byte && (fc->corrupt_bio_rw == WRITE)) अणु
			अगर (all_corrupt_bio_flags_match(bio, fc))
				corrupt_bio_data(bio, fc);
			जाओ map_bio;
		पूर्ण

		/*
		 * By शेष, error all I/O.
		 */
		वापस DM_MAPIO_KILL;
	पूर्ण

map_bio:
	flakey_map_bio(ti, bio);

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक flakey_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio,
			 blk_status_t *error)
अणु
	काष्ठा flakey_c *fc = ti->निजी;
	काष्ठा per_bio_data *pb = dm_per_bio_data(bio, माप(काष्ठा per_bio_data));

	अगर (op_is_zone_mgmt(bio_op(bio)))
		वापस DM_ENDIO_DONE;

	अगर (!*error && pb->bio_submitted && (bio_data_dir(bio) == READ)) अणु
		अगर (fc->corrupt_bio_byte && (fc->corrupt_bio_rw == READ) &&
		    all_corrupt_bio_flags_match(bio, fc)) अणु
			/*
			 * Corrupt successful matching READs जबतक in करोwn state.
			 */
			corrupt_bio_data(bio, fc);

		पूर्ण अन्यथा अगर (!test_bit(DROP_WRITES, &fc->flags) &&
			   !test_bit(ERROR_WRITES, &fc->flags)) अणु
			/*
			 * Error पढ़ो during the करोwn_पूर्णांकerval अगर drop_ग_लिखोs
			 * and error_ग_लिखोs were not configured.
			 */
			*error = BLK_STS_IOERR;
		पूर्ण
	पूर्ण

	वापस DM_ENDIO_DONE;
पूर्ण

अटल व्योम flakey_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा flakey_c *fc = ti->निजी;
	अचिन्हित drop_ग_लिखोs, error_ग_लिखोs;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		result[0] = '\0';
		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %llu %u %u ", fc->dev->name,
		       (अचिन्हित दीर्घ दीर्घ)fc->start, fc->up_पूर्णांकerval,
		       fc->करोwn_पूर्णांकerval);

		drop_ग_लिखोs = test_bit(DROP_WRITES, &fc->flags);
		error_ग_लिखोs = test_bit(ERROR_WRITES, &fc->flags);
		DMEMIT("%u ", drop_ग_लिखोs + error_ग_लिखोs + (fc->corrupt_bio_byte > 0) * 5);

		अगर (drop_ग_लिखोs)
			DMEMIT("drop_writes ");
		अन्यथा अगर (error_ग_लिखोs)
			DMEMIT("error_writes ");

		अगर (fc->corrupt_bio_byte)
			DMEMIT("corrupt_bio_byte %u %c %u %u ",
			       fc->corrupt_bio_byte,
			       (fc->corrupt_bio_rw == WRITE) ? 'w' : 'r',
			       fc->corrupt_bio_value, fc->corrupt_bio_flags);

		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक flakey_prepare_ioctl(काष्ठा dm_target *ti, काष्ठा block_device **bdev)
अणु
	काष्ठा flakey_c *fc = ti->निजी;

	*bdev = fc->dev->bdev;

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (fc->start ||
	    ti->len != i_size_पढ़ो((*bdev)->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल पूर्णांक flakey_report_zones(काष्ठा dm_target *ti,
		काष्ठा dm_report_zones_args *args, अचिन्हित पूर्णांक nr_zones)
अणु
	काष्ठा flakey_c *fc = ti->निजी;
	sector_t sector = flakey_map_sector(ti, args->next_sector);

	args->start = fc->start;
	वापस blkdev_report_zones(fc->dev->bdev, sector, nr_zones,
				   dm_report_zones_cb, args);
पूर्ण
#अन्यथा
#घोषणा flakey_report_zones शून्य
#पूर्ण_अगर

अटल पूर्णांक flakey_iterate_devices(काष्ठा dm_target *ti, iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा flakey_c *fc = ti->निजी;

	वापस fn(ti, fc->dev, fc->start, ti->len, data);
पूर्ण

अटल काष्ठा target_type flakey_target = अणु
	.name   = "flakey",
	.version = अणु1, 5, 0पूर्ण,
	.features = DM_TARGET_ZONED_HM | DM_TARGET_PASSES_CRYPTO,
	.report_zones = flakey_report_zones,
	.module = THIS_MODULE,
	.ctr    = flakey_ctr,
	.dtr    = flakey_dtr,
	.map    = flakey_map,
	.end_io = flakey_end_io,
	.status = flakey_status,
	.prepare_ioctl = flakey_prepare_ioctl,
	.iterate_devices = flakey_iterate_devices,
पूर्ण;

अटल पूर्णांक __init dm_flakey_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_target(&flakey_target);

	अगर (r < 0)
		DMERR("register failed %d", r);

	वापस r;
पूर्ण

अटल व्योम __निकास dm_flakey_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&flakey_target);
पूर्ण

/* Module hooks */
module_init(dm_flakey_init);
module_निकास(dm_flakey_निकास);

MODULE_DESCRIPTION(DM_NAME " flakey target");
MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
