<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 * Copyright तऊ 2004 Ferenc Havasi <havasi@inf.u-szeged.hu>,
 *		    University of Szeged, Hungary
 *
 * Created by Arjan van de Ven <arjan@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "compr.h"

अटल DEFINE_SPINLOCK(jffs2_compressor_list_lock);

/* Available compressors are on this list */
अटल LIST_HEAD(jffs2_compressor_list);

/* Actual compression mode */
अटल पूर्णांक jffs2_compression_mode = JFFS2_COMPR_MODE_PRIORITY;

/* Statistics क्रम blocks stored without compression */
अटल uपूर्णांक32_t none_stat_compr_blocks=0,none_stat_decompr_blocks=0,none_stat_compr_size=0;


/*
 * Return 1 to use this compression
 */
अटल पूर्णांक jffs2_is_best_compression(काष्ठा jffs2_compressor *this,
		काष्ठा jffs2_compressor *best, uपूर्णांक32_t size, uपूर्णांक32_t bestsize)
अणु
	चयन (jffs2_compression_mode) अणु
	हाल JFFS2_COMPR_MODE_SIZE:
		अगर (bestsize > size)
			वापस 1;
		वापस 0;
	हाल JFFS2_COMPR_MODE_FAVOURLZO:
		अगर ((this->compr == JFFS2_COMPR_LZO) && (bestsize > size))
			वापस 1;
		अगर ((best->compr != JFFS2_COMPR_LZO) && (bestsize > size))
			वापस 1;
		अगर ((this->compr == JFFS2_COMPR_LZO) && (bestsize > (size * FAVOUR_LZO_PERCENT / 100)))
			वापस 1;
		अगर ((bestsize * FAVOUR_LZO_PERCENT / 100) > size)
			वापस 1;

		वापस 0;
	पूर्ण
	/* Shouldn't happen */
	वापस 0;
पूर्ण

/*
 * jffs2_selected_compress:
 * @compr: Explicit compression type to use (ie, JFFS2_COMPR_ZLIB).
 *	If 0, just take the first available compression mode.
 * @data_in: Poपूर्णांकer to uncompressed data
 * @cpage_out: Poपूर्णांकer to वापसed poपूर्णांकer to buffer क्रम compressed data
 * @datalen: On entry, holds the amount of data available क्रम compression.
 *	On निकास, expected to hold the amount of data actually compressed.
 * @cdatalen: On entry, holds the amount of space available क्रम compressed
 *	data. On निकास, expected to hold the actual size of the compressed
 *	data.
 *
 * Returns: the compression type used.  Zero is used to show that the data
 * could not be compressed; probably because we couldn't find the requested
 * compression mode.
 */
अटल पूर्णांक jffs2_selected_compress(u8 compr, अचिन्हित अक्षर *data_in,
		अचिन्हित अक्षर **cpage_out, u32 *datalen, u32 *cdatalen)
अणु
	काष्ठा jffs2_compressor *this;
	पूर्णांक err, ret = JFFS2_COMPR_NONE;
	uपूर्णांक32_t orig_slen, orig_dlen;
	अक्षर *output_buf;

	output_buf = kदो_स्मृति(*cdatalen, GFP_KERNEL);
	अगर (!output_buf) अणु
		pr_warn("No memory for compressor allocation. Compression failed.\n");
		वापस ret;
	पूर्ण
	orig_slen = *datalen;
	orig_dlen = *cdatalen;
	spin_lock(&jffs2_compressor_list_lock);
	list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
		/* Skip decompress-only and disabled modules */
		अगर (!this->compress || this->disabled)
			जारी;

		/* Skip अगर not the desired compression type */
		अगर (compr && (compr != this->compr))
			जारी;

		/*
		 * Either compression type was unspecअगरied, or we found our
		 * compressor; either way, we're good to go.
		 */
		this->usecount++;
		spin_unlock(&jffs2_compressor_list_lock);

		*datalen  = orig_slen;
		*cdatalen = orig_dlen;
		err = this->compress(data_in, output_buf, datalen, cdatalen);

		spin_lock(&jffs2_compressor_list_lock);
		this->usecount--;
		अगर (!err) अणु
			/* Success */
			ret = this->compr;
			this->stat_compr_blocks++;
			this->stat_compr_orig_size += *datalen;
			this->stat_compr_new_size += *cdatalen;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&jffs2_compressor_list_lock);
	अगर (ret == JFFS2_COMPR_NONE)
		kमुक्त(output_buf);
	अन्यथा
		*cpage_out = output_buf;

	वापस ret;
पूर्ण

/* jffs2_compress:
 * @data_in: Poपूर्णांकer to uncompressed data
 * @cpage_out: Poपूर्णांकer to वापसed poपूर्णांकer to buffer क्रम compressed data
 * @datalen: On entry, holds the amount of data available क्रम compression.
 *	On निकास, expected to hold the amount of data actually compressed.
 * @cdatalen: On entry, holds the amount of space available क्रम compressed
 *	data. On निकास, expected to hold the actual size of the compressed
 *	data.
 *
 * Returns: Lower byte to be stored with data indicating compression type used.
 * Zero is used to show that the data could not be compressed - the
 * compressed version was actually larger than the original.
 * Upper byte will be used later. (soon)
 *
 * If the cdata buffer isn't large enough to hold all the uncompressed data,
 * jffs2_compress should compress as much as will fit, and should set
 * *datalen accordingly to show the amount of data which were compressed.
 */
uपूर्णांक16_t jffs2_compress(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			अचिन्हित अक्षर *data_in, अचिन्हित अक्षर **cpage_out,
			uपूर्णांक32_t *datalen, uपूर्णांक32_t *cdatalen)
अणु
	पूर्णांक ret = JFFS2_COMPR_NONE;
	पूर्णांक mode, compr_ret;
	काष्ठा jffs2_compressor *this, *best=शून्य;
	अचिन्हित अक्षर *output_buf = शून्य, *पंचांगp_buf;
	uपूर्णांक32_t orig_slen, orig_dlen;
	uपूर्णांक32_t best_slen=0, best_dlen=0;

	अगर (c->mount_opts.override_compr)
		mode = c->mount_opts.compr;
	अन्यथा
		mode = jffs2_compression_mode;

	चयन (mode) अणु
	हाल JFFS2_COMPR_MODE_NONE:
		अवरोध;
	हाल JFFS2_COMPR_MODE_PRIORITY:
		ret = jffs2_selected_compress(0, data_in, cpage_out, datalen,
				cdatalen);
		अवरोध;
	हाल JFFS2_COMPR_MODE_SIZE:
	हाल JFFS2_COMPR_MODE_FAVOURLZO:
		orig_slen = *datalen;
		orig_dlen = *cdatalen;
		spin_lock(&jffs2_compressor_list_lock);
		list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
			/* Skip decompress-only backwards-compatibility and disabled modules */
			अगर ((!this->compress)||(this->disabled))
				जारी;
			/* Allocating memory क्रम output buffer अगर necessary */
			अगर ((this->compr_buf_size < orig_slen) && (this->compr_buf)) अणु
				spin_unlock(&jffs2_compressor_list_lock);
				kमुक्त(this->compr_buf);
				spin_lock(&jffs2_compressor_list_lock);
				this->compr_buf_size=0;
				this->compr_buf=शून्य;
			पूर्ण
			अगर (!this->compr_buf) अणु
				spin_unlock(&jffs2_compressor_list_lock);
				पंचांगp_buf = kदो_स्मृति(orig_slen, GFP_KERNEL);
				spin_lock(&jffs2_compressor_list_lock);
				अगर (!पंचांगp_buf) अणु
					pr_warn("No memory for compressor allocation. (%d bytes)\n",
						orig_slen);
					जारी;
				पूर्ण
				अन्यथा अणु
					this->compr_buf = पंचांगp_buf;
					this->compr_buf_size = orig_slen;
				पूर्ण
			पूर्ण
			this->usecount++;
			spin_unlock(&jffs2_compressor_list_lock);
			*datalen  = orig_slen;
			*cdatalen = orig_dlen;
			compr_ret = this->compress(data_in, this->compr_buf, datalen, cdatalen);
			spin_lock(&jffs2_compressor_list_lock);
			this->usecount--;
			अगर (!compr_ret) अणु
				अगर (((!best_dlen) || jffs2_is_best_compression(this, best, *cdatalen, best_dlen))
						&& (*cdatalen < *datalen)) अणु
					best_dlen = *cdatalen;
					best_slen = *datalen;
					best = this;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (best_dlen) अणु
			*cdatalen = best_dlen;
			*datalen  = best_slen;
			output_buf = best->compr_buf;
			best->compr_buf = शून्य;
			best->compr_buf_size = 0;
			best->stat_compr_blocks++;
			best->stat_compr_orig_size += best_slen;
			best->stat_compr_new_size  += best_dlen;
			ret = best->compr;
			*cpage_out = output_buf;
		पूर्ण
		spin_unlock(&jffs2_compressor_list_lock);
		अवरोध;
	हाल JFFS2_COMPR_MODE_FORCELZO:
		ret = jffs2_selected_compress(JFFS2_COMPR_LZO, data_in,
				cpage_out, datalen, cdatalen);
		अवरोध;
	हाल JFFS2_COMPR_MODE_FORCEZLIB:
		ret = jffs2_selected_compress(JFFS2_COMPR_ZLIB, data_in,
				cpage_out, datalen, cdatalen);
		अवरोध;
	शेष:
		pr_err("unknown compression mode\n");
	पूर्ण

	अगर (ret == JFFS2_COMPR_NONE) अणु
		*cpage_out = data_in;
		*datalen = *cdatalen;
		none_stat_compr_blocks++;
		none_stat_compr_size += *datalen;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक jffs2_decompress(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
		     uपूर्णांक16_t comprtype, अचिन्हित अक्षर *cdata_in,
		     अचिन्हित अक्षर *data_out, uपूर्णांक32_t cdatalen, uपूर्णांक32_t datalen)
अणु
	काष्ठा jffs2_compressor *this;
	पूर्णांक ret;

	/* Older code had a bug where it would ग_लिखो non-zero 'usercompr'
	   fields. Deal with it. */
	अगर ((comprtype & 0xff) <= JFFS2_COMPR_ZLIB)
		comprtype &= 0xff;

	चयन (comprtype & 0xff) अणु
	हाल JFFS2_COMPR_NONE:
		/* This should be special-हालd अन्यथाwhere, but we might as well deal with it */
		स_नकल(data_out, cdata_in, datalen);
		none_stat_decompr_blocks++;
		अवरोध;
	हाल JFFS2_COMPR_ZERO:
		स_रखो(data_out, 0, datalen);
		अवरोध;
	शेष:
		spin_lock(&jffs2_compressor_list_lock);
		list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
			अगर (comprtype == this->compr) अणु
				this->usecount++;
				spin_unlock(&jffs2_compressor_list_lock);
				ret = this->decompress(cdata_in, data_out, cdatalen, datalen);
				spin_lock(&jffs2_compressor_list_lock);
				अगर (ret) अणु
					pr_warn("Decompressor \"%s\" returned %d\n",
						this->name, ret);
				पूर्ण
				अन्यथा अणु
					this->stat_decompr_blocks++;
				पूर्ण
				this->usecount--;
				spin_unlock(&jffs2_compressor_list_lock);
				वापस ret;
			पूर्ण
		पूर्ण
		pr_warn("compression type 0x%02x not available\n", comprtype);
		spin_unlock(&jffs2_compressor_list_lock);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक jffs2_रेजिस्टर_compressor(काष्ठा jffs2_compressor *comp)
अणु
	काष्ठा jffs2_compressor *this;

	अगर (!comp->name) अणु
		pr_warn("NULL compressor name at registering JFFS2 compressor. Failed.\n");
		वापस -1;
	पूर्ण
	comp->compr_buf_size=0;
	comp->compr_buf=शून्य;
	comp->usecount=0;
	comp->stat_compr_orig_size=0;
	comp->stat_compr_new_size=0;
	comp->stat_compr_blocks=0;
	comp->stat_decompr_blocks=0;
	jffs2_dbg(1, "Registering JFFS2 compressor \"%s\"\n", comp->name);

	spin_lock(&jffs2_compressor_list_lock);

	list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
		अगर (this->priority < comp->priority) अणु
			list_add(&comp->list, this->list.prev);
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_tail(&comp->list, &jffs2_compressor_list);
out:
	D2(list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
		prपूर्णांकk(KERN_DEBUG "Compressor \"%s\", prio %d\n", this->name, this->priority);
	पूर्ण)

	spin_unlock(&jffs2_compressor_list_lock);

	वापस 0;
पूर्ण

पूर्णांक jffs2_unरेजिस्टर_compressor(काष्ठा jffs2_compressor *comp)
अणु
	D2(काष्ठा jffs2_compressor *this);

	jffs2_dbg(1, "Unregistering JFFS2 compressor \"%s\"\n", comp->name);

	spin_lock(&jffs2_compressor_list_lock);

	अगर (comp->usecount) अणु
		spin_unlock(&jffs2_compressor_list_lock);
		pr_warn("Compressor module is in use. Unregister failed.\n");
		वापस -1;
	पूर्ण
	list_del(&comp->list);

	D2(list_क्रम_each_entry(this, &jffs2_compressor_list, list) अणु
		prपूर्णांकk(KERN_DEBUG "Compressor \"%s\", prio %d\n", this->name, this->priority);
	पूर्ण)
	spin_unlock(&jffs2_compressor_list_lock);
	वापस 0;
पूर्ण

व्योम jffs2_मुक्त_comprbuf(अचिन्हित अक्षर *comprbuf, अचिन्हित अक्षर *orig)
अणु
	अगर (orig != comprbuf)
		kमुक्त(comprbuf);
पूर्ण

पूर्णांक __init jffs2_compressors_init(व्योम)
अणु
/* Registering compressors */
#अगर_घोषित CONFIG_JFFS2_ZLIB
	jffs2_zlib_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_RTIME
	jffs2_rसमय_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_RUBIN
	jffs2_rubinmips_init();
	jffs2_dynrubin_init();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_LZO
	jffs2_lzo_init();
#पूर्ण_अगर
/* Setting शेष compression mode */
#अगर_घोषित CONFIG_JFFS2_CMODE_NONE
	jffs2_compression_mode = JFFS2_COMPR_MODE_NONE;
	jffs2_dbg(1, "default compression mode: none\n");
#अन्यथा
#अगर_घोषित CONFIG_JFFS2_CMODE_SIZE
	jffs2_compression_mode = JFFS2_COMPR_MODE_SIZE;
	jffs2_dbg(1, "default compression mode: size\n");
#अन्यथा
#अगर_घोषित CONFIG_JFFS2_CMODE_FAVOURLZO
	jffs2_compression_mode = JFFS2_COMPR_MODE_FAVOURLZO;
	jffs2_dbg(1, "default compression mode: favourlzo\n");
#अन्यथा
	jffs2_dbg(1, "default compression mode: priority\n");
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक jffs2_compressors_निकास(व्योम)
अणु
/* Unरेजिस्टरing compressors */
#अगर_घोषित CONFIG_JFFS2_LZO
	jffs2_lzo_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_RUBIN
	jffs2_dynrubin_निकास();
	jffs2_rubinmips_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_RTIME
	jffs2_rसमय_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_ZLIB
	jffs2_zlib_निकास();
#पूर्ण_अगर
	वापस 0;
पूर्ण
