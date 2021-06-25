<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश "pvrusb2-ctrl.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>


अटल पूर्णांक pvr2_ctrl_range_check(काष्ठा pvr2_ctrl *cptr,पूर्णांक val)
अणु
	अगर (cptr->info->check_value) अणु
		अगर (!cptr->info->check_value(cptr,val)) वापस -दुस्फल;
	पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_क्रमागत) अणु
		अगर (val < 0) वापस -दुस्फल;
		अगर (val >= cptr->info->def.type_क्रमागत.count) वापस -दुस्फल;
	पूर्ण अन्यथा अणु
		पूर्णांक lim;
		lim = cptr->info->def.type_पूर्णांक.min_value;
		अगर (cptr->info->get_min_value) अणु
			cptr->info->get_min_value(cptr,&lim);
		पूर्ण
		अगर (val < lim) वापस -दुस्फल;
		lim = cptr->info->def.type_पूर्णांक.max_value;
		अगर (cptr->info->get_max_value) अणु
			cptr->info->get_max_value(cptr,&lim);
		पूर्ण
		अगर (val > lim) वापस -दुस्फल;
	पूर्ण
	वापस 0;
पूर्ण


/* Set the given control. */
पूर्णांक pvr2_ctrl_set_value(काष्ठा pvr2_ctrl *cptr,पूर्णांक val)
अणु
	वापस pvr2_ctrl_set_mask_value(cptr,~0,val);
पूर्ण


/* Set/clear specअगरic bits of the given control. */
पूर्णांक pvr2_ctrl_set_mask_value(काष्ठा pvr2_ctrl *cptr,पूर्णांक mask,पूर्णांक val)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस -EINVAL;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->set_value) अणु
			अगर (cptr->info->type == pvr2_ctl_biपंचांगask) अणु
				mask &= cptr->info->def.type_biपंचांगask.valid_bits;
			पूर्ण अन्यथा अगर ((cptr->info->type == pvr2_ctl_पूर्णांक)||
				   (cptr->info->type == pvr2_ctl_क्रमागत)) अणु
				ret = pvr2_ctrl_range_check(cptr,val);
				अगर (ret < 0) अवरोध;
			पूर्ण अन्यथा अगर (cptr->info->type != pvr2_ctl_bool) अणु
				अवरोध;
			पूर्ण
			ret = cptr->info->set_value(cptr,mask,val);
		पूर्ण अन्यथा अणु
			ret = -EPERM;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Get the current value of the given control. */
पूर्णांक pvr2_ctrl_get_value(काष्ठा pvr2_ctrl *cptr,पूर्णांक *valptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस -EINVAL;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		ret = cptr->info->get_value(cptr,valptr);
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve control's type */
क्रमागत pvr2_ctl_type pvr2_ctrl_get_type(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस pvr2_ctl_पूर्णांक;
	वापस cptr->info->type;
पूर्ण


/* Retrieve control's maximum value (पूर्णांक type) */
पूर्णांक pvr2_ctrl_get_max(काष्ठा pvr2_ctrl *cptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस 0;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->get_max_value) अणु
			cptr->info->get_max_value(cptr,&ret);
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_पूर्णांक) अणु
			ret = cptr->info->def.type_पूर्णांक.max_value;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve control's minimum value (पूर्णांक type) */
पूर्णांक pvr2_ctrl_get_min(काष्ठा pvr2_ctrl *cptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस 0;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->get_min_value) अणु
			cptr->info->get_min_value(cptr,&ret);
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_पूर्णांक) अणु
			ret = cptr->info->def.type_पूर्णांक.min_value;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve control's शेष value (any type) */
पूर्णांक pvr2_ctrl_get_def(काष्ठा pvr2_ctrl *cptr, पूर्णांक *valptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस -EINVAL;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->get_def_value) अणु
			ret = cptr->info->get_def_value(cptr, valptr);
		पूर्ण अन्यथा अणु
			*valptr = cptr->info->शेष_value;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve control's क्रमागतeration count (क्रमागत only) */
पूर्णांक pvr2_ctrl_get_cnt(काष्ठा pvr2_ctrl *cptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस 0;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->type == pvr2_ctl_क्रमागत) अणु
			ret = cptr->info->def.type_क्रमागत.count;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve control's valid mask bits (bit mask only) */
पूर्णांक pvr2_ctrl_get_mask(काष्ठा pvr2_ctrl *cptr)
अणु
	पूर्णांक ret = 0;
	अगर (!cptr) वापस 0;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->type == pvr2_ctl_biपंचांगask) अणु
			ret = cptr->info->def.type_biपंचांगask.valid_bits;
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Retrieve the control's name */
स्थिर अक्षर *pvr2_ctrl_get_name(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस शून्य;
	वापस cptr->info->name;
पूर्ण


/* Retrieve the control's desc */
स्थिर अक्षर *pvr2_ctrl_get_desc(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस शून्य;
	वापस cptr->info->desc;
पूर्ण


/* Retrieve a control क्रमागतeration or bit mask value */
पूर्णांक pvr2_ctrl_get_valname(काष्ठा pvr2_ctrl *cptr,पूर्णांक val,
			  अक्षर *bptr,अचिन्हित पूर्णांक bmax,
			  अचिन्हित पूर्णांक *blen)
अणु
	पूर्णांक ret = -EINVAL;
	अगर (!cptr) वापस 0;
	*blen = 0;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->type == pvr2_ctl_क्रमागत) अणु
			स्थिर अक्षर * स्थिर *names;
			names = cptr->info->def.type_क्रमागत.value_names;
			अगर (pvr2_ctrl_range_check(cptr,val) == 0) अणु
				अगर (names[val]) अणु
					*blen = scnम_लिखो(
						bptr,bmax,"%s",
						names[val]);
				पूर्ण अन्यथा अणु
					*blen = 0;
				पूर्ण
				ret = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_biपंचांगask) अणु
			स्थिर अक्षर **names;
			अचिन्हित पूर्णांक idx;
			पूर्णांक msk;
			names = cptr->info->def.type_biपंचांगask.bit_names;
			val &= cptr->info->def.type_biपंचांगask.valid_bits;
			क्रम (idx = 0, msk = 1; val; idx++, msk <<= 1) अणु
				अगर (val & msk) अणु
					*blen = scnम_लिखो(bptr,bmax,"%s",
							  names[idx]);
					ret = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Return V4L ID क्रम this control or zero अगर none */
पूर्णांक pvr2_ctrl_get_v4lid(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस 0;
	वापस cptr->info->v4l_id;
पूर्ण


अचिन्हित पूर्णांक pvr2_ctrl_get_v4lflags(काष्ठा pvr2_ctrl *cptr)
अणु
	अचिन्हित पूर्णांक flags = 0;

	अगर (cptr->info->get_v4lflags) अणु
		flags = cptr->info->get_v4lflags(cptr);
	पूर्ण

	अगर (cptr->info->set_value) अणु
		flags &= ~V4L2_CTRL_FLAG_READ_ONLY;
	पूर्ण अन्यथा अणु
		flags |= V4L2_CTRL_FLAG_READ_ONLY;
	पूर्ण

	वापस flags;
पूर्ण


/* Return true अगर control is writable */
पूर्णांक pvr2_ctrl_is_writable(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस 0;
	वापस cptr->info->set_value != शून्य;
पूर्ण


/* Return true अगर control has custom symbolic representation */
पूर्णांक pvr2_ctrl_has_custom_symbols(काष्ठा pvr2_ctrl *cptr)
अणु
	अगर (!cptr) वापस 0;
	अगर (!cptr->info->val_to_sym) वापस 0;
	अगर (!cptr->info->sym_to_val) वापस 0;
	वापस !0;
पूर्ण


/* Convert a given mask/val to a custom symbolic value */
पूर्णांक pvr2_ctrl_custom_value_to_sym(काष्ठा pvr2_ctrl *cptr,
				  पूर्णांक mask,पूर्णांक val,
				  अक्षर *buf,अचिन्हित पूर्णांक maxlen,
				  अचिन्हित पूर्णांक *len)
अणु
	अगर (!cptr) वापस -EINVAL;
	अगर (!cptr->info->val_to_sym) वापस -EINVAL;
	वापस cptr->info->val_to_sym(cptr,mask,val,buf,maxlen,len);
पूर्ण


/* Convert a symbolic value to a mask/value pair */
पूर्णांक pvr2_ctrl_custom_sym_to_value(काष्ठा pvr2_ctrl *cptr,
				  स्थिर अक्षर *buf,अचिन्हित पूर्णांक len,
				  पूर्णांक *maskptr,पूर्णांक *valptr)
अणु
	अगर (!cptr) वापस -EINVAL;
	अगर (!cptr->info->sym_to_val) वापस -EINVAL;
	वापस cptr->info->sym_to_val(cptr,buf,len,maskptr,valptr);
पूर्ण


अटल अचिन्हित पूर्णांक gen_biपंचांगask_string(पूर्णांक msk,पूर्णांक val,पूर्णांक msk_only,
				       स्थिर अक्षर **names,
				       अक्षर *ptr,अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक idx;
	दीर्घ sm,um;
	पूर्णांक spcFl;
	अचिन्हित पूर्णांक uc,cnt;
	स्थिर अक्षर *idStr;

	spcFl = 0;
	uc = 0;
	um = 0;
	क्रम (idx = 0, sm = 1; msk; idx++, sm <<= 1) अणु
		अगर (sm & msk) अणु
			msk &= ~sm;
			idStr = names[idx];
			अगर (idStr) अणु
				cnt = scnम_लिखो(ptr,len,"%s%s%s",
						(spcFl ? " " : ""),
						(msk_only ? "" :
						 ((val & sm) ? "+" : "-")),
						idStr);
				ptr += cnt; len -= cnt; uc += cnt;
				spcFl = !0;
			पूर्ण अन्यथा अणु
				um |= sm;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (um) अणु
		अगर (msk_only) अणु
			cnt = scnम_लिखो(ptr,len,"%s0x%lx",
					(spcFl ? " " : ""),
					um);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		पूर्ण अन्यथा अगर (um & val) अणु
			cnt = scnम_लिखो(ptr,len,"%s+0x%lx",
					(spcFl ? " " : ""),
					um & val);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		पूर्ण अन्यथा अगर (um & ~val) अणु
			cnt = scnम_लिखो(ptr,len,"%s+0x%lx",
					(spcFl ? " " : ""),
					um & ~val);
			ptr += cnt; len -= cnt; uc += cnt;
			spcFl = !0;
		पूर्ण
	पूर्ण
	वापस uc;
पूर्ण


अटल स्थिर अक्षर *boolNames[] = अणु
	"false",
	"true",
	"no",
	"yes",
पूर्ण;


अटल पूर्णांक parse_token(स्थिर अक्षर *ptr,अचिन्हित पूर्णांक len,
		       पूर्णांक *valptr,
		       स्थिर अक्षर * स्थिर *names, अचिन्हित पूर्णांक namecnt)
अणु
	अक्षर buf[33];
	अचिन्हित पूर्णांक slen;
	अचिन्हित पूर्णांक idx;
	पूर्णांक negfl;
	अक्षर *p2;
	*valptr = 0;
	अगर (!names) namecnt = 0;
	क्रम (idx = 0; idx < namecnt; idx++) अणु
		अगर (!names[idx]) जारी;
		slen = म_माप(names[idx]);
		अगर (slen != len) जारी;
		अगर (स_भेद(names[idx],ptr,slen)) जारी;
		*valptr = idx;
		वापस 0;
	पूर्ण
	negfl = 0;
	अगर ((*ptr == '-') || (*ptr == '+')) अणु
		negfl = (*ptr == '-');
		ptr++; len--;
	पूर्ण
	अगर (len >= माप(buf)) वापस -EINVAL;
	स_नकल(buf,ptr,len);
	buf[len] = 0;
	*valptr = simple_म_से_दीर्घ(buf,&p2,0);
	अगर (negfl) *valptr = -(*valptr);
	अगर (*p2) वापस -EINVAL;
	वापस 1;
पूर्ण


अटल पूर्णांक parse_mtoken(स्थिर अक्षर *ptr,अचिन्हित पूर्णांक len,
			पूर्णांक *valptr,
			स्थिर अक्षर **names,पूर्णांक valid_bits)
अणु
	अक्षर buf[33];
	अचिन्हित पूर्णांक slen;
	अचिन्हित पूर्णांक idx;
	अक्षर *p2;
	पूर्णांक msk;
	*valptr = 0;
	क्रम (idx = 0, msk = 1; valid_bits; idx++, msk <<= 1) अणु
		अगर (!(msk & valid_bits)) जारी;
		valid_bits &= ~msk;
		अगर (!names[idx]) जारी;
		slen = म_माप(names[idx]);
		अगर (slen != len) जारी;
		अगर (स_भेद(names[idx],ptr,slen)) जारी;
		*valptr = msk;
		वापस 0;
	पूर्ण
	अगर (len >= माप(buf)) वापस -EINVAL;
	स_नकल(buf,ptr,len);
	buf[len] = 0;
	*valptr = simple_म_से_दीर्घ(buf,&p2,0);
	अगर (*p2) वापस -EINVAL;
	वापस 0;
पूर्ण


अटल पूर्णांक parse_tlist(स्थिर अक्षर *ptr,अचिन्हित पूर्णांक len,
		       पूर्णांक *maskptr,पूर्णांक *valptr,
		       स्थिर अक्षर **names,पूर्णांक valid_bits)
अणु
	अचिन्हित पूर्णांक cnt;
	पूर्णांक mask,val,kv,mode,ret;
	mask = 0;
	val = 0;
	ret = 0;
	जबतक (len) अणु
		cnt = 0;
		जबतक ((cnt < len) &&
		       ((ptr[cnt] <= 32) ||
			(ptr[cnt] >= 127))) cnt++;
		ptr += cnt;
		len -= cnt;
		mode = 0;
		अगर ((*ptr == '-') || (*ptr == '+')) अणु
			mode = (*ptr == '-') ? -1 : 1;
			ptr++;
			len--;
		पूर्ण
		cnt = 0;
		जबतक (cnt < len) अणु
			अगर (ptr[cnt] <= 32) अवरोध;
			अगर (ptr[cnt] >= 127) अवरोध;
			cnt++;
		पूर्ण
		अगर (!cnt) अवरोध;
		अगर (parse_mtoken(ptr,cnt,&kv,names,valid_bits)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ptr += cnt;
		len -= cnt;
		चयन (mode) अणु
		हाल 0:
			mask = valid_bits;
			val |= kv;
			अवरोध;
		हाल -1:
			mask |= kv;
			val &= ~kv;
			अवरोध;
		हाल 1:
			mask |= kv;
			val |= kv;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	*maskptr = mask;
	*valptr = val;
	वापस ret;
पूर्ण


/* Convert a symbolic value to a mask/value pair */
पूर्णांक pvr2_ctrl_sym_to_value(काष्ठा pvr2_ctrl *cptr,
			   स्थिर अक्षर *ptr,अचिन्हित पूर्णांक len,
			   पूर्णांक *maskptr,पूर्णांक *valptr)
अणु
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक cnt;

	*maskptr = 0;
	*valptr = 0;

	cnt = 0;
	जबतक ((cnt < len) && ((ptr[cnt] <= 32) || (ptr[cnt] >= 127))) cnt++;
	len -= cnt; ptr += cnt;
	cnt = 0;
	जबतक ((cnt < len) && ((ptr[len-(cnt+1)] <= 32) ||
			       (ptr[len-(cnt+1)] >= 127))) cnt++;
	len -= cnt;

	अगर (!len) वापस -EINVAL;

	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		अगर (cptr->info->type == pvr2_ctl_पूर्णांक) अणु
			ret = parse_token(ptr,len,valptr,शून्य,0);
			अगर (ret >= 0) अणु
				ret = pvr2_ctrl_range_check(cptr,*valptr);
			पूर्ण
			*maskptr = ~0;
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_bool) अणु
			ret = parse_token(ptr,len,valptr,boolNames,
					  ARRAY_SIZE(boolNames));
			अगर (ret == 1) अणु
				*valptr = *valptr ? !0 : 0;
			पूर्ण अन्यथा अगर (ret == 0) अणु
				*valptr = (*valptr & 1) ? !0 : 0;
			पूर्ण
			*maskptr = 1;
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_क्रमागत) अणु
			ret = parse_token(
				ptr,len,valptr,
				cptr->info->def.type_क्रमागत.value_names,
				cptr->info->def.type_क्रमागत.count);
			अगर (ret >= 0) अणु
				ret = pvr2_ctrl_range_check(cptr,*valptr);
			पूर्ण
			*maskptr = ~0;
		पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_biपंचांगask) अणु
			ret = parse_tlist(
				ptr,len,maskptr,valptr,
				cptr->info->def.type_biपंचांगask.bit_names,
				cptr->info->def.type_biपंचांगask.valid_bits);
		पूर्ण
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण


/* Convert a given mask/val to a symbolic value */
पूर्णांक pvr2_ctrl_value_to_sym_पूर्णांकernal(काष्ठा pvr2_ctrl *cptr,
				    पूर्णांक mask,पूर्णांक val,
				    अक्षर *buf,अचिन्हित पूर्णांक maxlen,
				    अचिन्हित पूर्णांक *len)
अणु
	पूर्णांक ret = -EINVAL;

	*len = 0;
	अगर (cptr->info->type == pvr2_ctl_पूर्णांक) अणु
		*len = scnम_लिखो(buf,maxlen,"%d",val);
		ret = 0;
	पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_bool) अणु
		*len = scnम_लिखो(buf,maxlen,"%s",val ? "true" : "false");
		ret = 0;
	पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_क्रमागत) अणु
		स्थिर अक्षर * स्थिर *names;
		names = cptr->info->def.type_क्रमागत.value_names;
		अगर ((val >= 0) &&
		    (val < cptr->info->def.type_क्रमागत.count)) अणु
			अगर (names[val]) अणु
				*len = scnम_लिखो(
					buf,maxlen,"%s",
					names[val]);
			पूर्ण अन्यथा अणु
				*len = 0;
			पूर्ण
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (cptr->info->type == pvr2_ctl_biपंचांगask) अणु
		*len = gen_biपंचांगask_string(
			val & mask & cptr->info->def.type_biपंचांगask.valid_bits,
			~0,!0,
			cptr->info->def.type_biपंचांगask.bit_names,
			buf,maxlen);
	पूर्ण
	वापस ret;
पूर्ण


/* Convert a given mask/val to a symbolic value */
पूर्णांक pvr2_ctrl_value_to_sym(काष्ठा pvr2_ctrl *cptr,
			   पूर्णांक mask,पूर्णांक val,
			   अक्षर *buf,अचिन्हित पूर्णांक maxlen,
			   अचिन्हित पूर्णांक *len)
अणु
	पूर्णांक ret;
	LOCK_TAKE(cptr->hdw->big_lock); करो अणु
		ret = pvr2_ctrl_value_to_sym_पूर्णांकernal(cptr,mask,val,
						      buf,maxlen,len);
	पूर्ण जबतक(0); LOCK_GIVE(cptr->hdw->big_lock);
	वापस ret;
पूर्ण
