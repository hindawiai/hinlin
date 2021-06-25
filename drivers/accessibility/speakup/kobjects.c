<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Speakup kobject implementation
 *
 * Copyright (C) 2009 William Hubbs
 *
 * This code is based on kobject-example.c, which came with linux 2.6.x.
 *
 * Copyright (C) 2004-2007 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2007 Novell Inc.
 *
 * Released under the GPL version 2 only.
 *
 */
#समावेश <linux/slab.h>		/* For kदो_स्मृति. */
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/string_helpers.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>

#समावेश "speakup.h"
#समावेश "spk_priv.h"

/*
 * This is called when a user पढ़ोs the अक्षरacters or अक्षरtab sys file.
 */
अटल sमाप_प्रकार अक्षरs_अक्षरtab_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;
	अक्षर *cp;
	अक्षर *buf_poपूर्णांकer = buf;
	माप_प्रकार bufsize = PAGE_SIZE;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	*buf_poपूर्णांकer = '\0';
	क्रम (i = 0; i < 256; i++) अणु
		अगर (bufsize <= 1)
			अवरोध;
		अगर (म_भेद("characters", attr->attr.name) == 0) अणु
			len = scnम_लिखो(buf_poपूर्णांकer, bufsize, "%d\t%s\n",
					i, spk_अक्षरacters[i]);
		पूर्ण अन्यथा अणु	/* show अक्षरtab entry */
			अगर (IS_TYPE(i, B_CTL))
				cp = "B_CTL";
			अन्यथा अगर (IS_TYPE(i, WDLM))
				cp = "WDLM";
			अन्यथा अगर (IS_TYPE(i, A_PUNC))
				cp = "A_PUNC";
			अन्यथा अगर (IS_TYPE(i, PUNC))
				cp = "PUNC";
			अन्यथा अगर (IS_TYPE(i, NUM))
				cp = "NUM";
			अन्यथा अगर (IS_TYPE(i, A_CAP))
				cp = "A_CAP";
			अन्यथा अगर (IS_TYPE(i, ALPHA))
				cp = "ALPHA";
			अन्यथा अगर (IS_TYPE(i, B_CAPSYM))
				cp = "B_CAPSYM";
			अन्यथा अगर (IS_TYPE(i, B_SYM))
				cp = "B_SYM";
			अन्यथा
				cp = "0";
			len =
			    scnम_लिखो(buf_poपूर्णांकer, bufsize, "%d\t%s\n", i, cp);
		पूर्ण
		bufsize -= len;
		buf_poपूर्णांकer += len;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस buf_poपूर्णांकer - buf;
पूर्ण

/*
 * Prपूर्णांक inक्रमmational messages or warnings after updating
 * अक्षरacter descriptions or अक्षरtab entries.
 */
अटल व्योम report_अक्षर_अक्षरtab_status(पूर्णांक reset, पूर्णांक received, पूर्णांक used,
				       पूर्णांक rejected, पूर्णांक करो_अक्षरacters)
अणु
	अटल अक्षर स्थिर *object_type[] = अणु
		"character class entries",
		"character descriptions",
	पूर्ण;
	पूर्णांक len;
	अक्षर buf[80];

	अगर (reset) अणु
		pr_info("%s reset to defaults\n", object_type[करो_अक्षरacters]);
	पूर्ण अन्यथा अगर (received) अणु
		len = snम_लिखो(buf, माप(buf),
			       " updated %d of %d %s\n",
			       used, received, object_type[करो_अक्षरacters]);
		अगर (rejected)
			snम_लिखो(buf + (len - 1), माप(buf) - (len - 1),
				 " with %d reject%s\n",
				 rejected, rejected > 1 ? "s" : "");
		pr_info("%s", buf);
	पूर्ण
पूर्ण

/*
 * This is called when a user changes the अक्षरacters or अक्षरtab parameters.
 */
अटल sमाप_प्रकार अक्षरs_अक्षरtab_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *cp = (अक्षर *)buf;
	अक्षर *end = cp + count; /* the null at the end of the buffer */
	अक्षर *linefeed = शून्य;
	अक्षर keyword[MAX_DESC_LEN + 1];
	अक्षर *outptr = शून्य;	/* Will hold keyword or desc. */
	अक्षर *temp = शून्य;
	अक्षर *desc = शून्य;
	sमाप_प्रकार retval = count;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ index = 0;
	पूर्णांक अक्षरclass = 0;
	पूर्णांक received = 0;
	पूर्णांक used = 0;
	पूर्णांक rejected = 0;
	पूर्णांक reset = 0;
	पूर्णांक करो_अक्षरacters = !म_भेद(attr->attr.name, "characters");
	माप_प्रकार desc_length = 0;
	पूर्णांक i;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	जबतक (cp < end) अणु
		जबतक ((cp < end) && (*cp == ' ' || *cp == '\t'))
			cp++;

		अगर (cp == end)
			अवरोध;
		अगर ((*cp == '\n') || म_अक्षर("dDrR", *cp)) अणु
			reset = 1;
			अवरोध;
		पूर्ण
		received++;

		linefeed = म_अक्षर(cp, '\n');
		अगर (!linefeed) अणु
			rejected++;
			अवरोध;
		पूर्ण

		अगर (!है_अंक(*cp)) अणु
			rejected++;
			cp = linefeed + 1;
			जारी;
		पूर्ण

		/*
		 * Do not replace with kम_से_अदीर्घ:
		 * here we need temp to be updated
		 */
		index = simple_म_से_अदीर्घ(cp, &temp, 10);
		अगर (index > 255) अणु
			rejected++;
			cp = linefeed + 1;
			जारी;
		पूर्ण

		जबतक ((temp < linefeed) && (*temp == ' ' || *temp == '\t'))
			temp++;

		desc_length = linefeed - temp;
		अगर (desc_length > MAX_DESC_LEN) अणु
			rejected++;
			cp = linefeed + 1;
			जारी;
		पूर्ण
		अगर (करो_अक्षरacters) अणु
			desc = kदो_स्मृति(desc_length + 1, GFP_ATOMIC);
			अगर (!desc) अणु
				retval = -ENOMEM;
				reset = 1;	/* just reset on error. */
				अवरोध;
			पूर्ण
			outptr = desc;
		पूर्ण अन्यथा अणु
			outptr = keyword;
		पूर्ण

		क्रम (i = 0; i < desc_length; i++)
			outptr[i] = temp[i];
		outptr[desc_length] = '\0';

		अगर (करो_अक्षरacters) अणु
			अगर (spk_अक्षरacters[index] != spk_शेष_अक्षरs[index])
				kमुक्त(spk_अक्षरacters[index]);
			spk_अक्षरacters[index] = desc;
			used++;
		पूर्ण अन्यथा अणु
			अक्षरclass = spk_अक्षरtab_get_value(keyword);
			अगर (अक्षरclass == 0) अणु
				rejected++;
				cp = linefeed + 1;
				जारी;
			पूर्ण
			अगर (अक्षरclass != spk_अक्षरtab[index]) अणु
				spk_अक्षरtab[index] = अक्षरclass;
				used++;
			पूर्ण
		पूर्ण
		cp = linefeed + 1;
	पूर्ण

	अगर (reset) अणु
		अगर (करो_अक्षरacters)
			spk_reset_शेष_अक्षरs();
		अन्यथा
			spk_reset_शेष_अक्षरtab();
	पूर्ण

	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	report_अक्षर_अक्षरtab_status(reset, received, used, rejected,
				   करो_अक्षरacters);
	वापस retval;
पूर्ण

/*
 * This is called when a user पढ़ोs the keymap parameter.
 */
अटल sमाप_प्रकार keymap_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   अक्षर *buf)
अणु
	अक्षर *cp = buf;
	पूर्णांक i;
	पूर्णांक n;
	पूर्णांक num_keys;
	पूर्णांक nstates;
	u_अक्षर *cp1;
	u_अक्षर ch;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	cp1 = spk_key_buf + SHIFT_TBL_SIZE;
	num_keys = (पूर्णांक)(*cp1);
	nstates = (पूर्णांक)cp1[1];
	cp += प्र_लिखो(cp, "%d, %d, %d,\n", KEY_MAP_VER, num_keys, nstates);
	cp1 += 2; /* now poपूर्णांकing at shअगरt states */
	/* dump num_keys+1 as first row is shअगरt states + flags,
	 * each subsequent row is key + states
	 */
	क्रम (n = 0; n <= num_keys; n++) अणु
		क्रम (i = 0; i <= nstates; i++) अणु
			ch = *cp1++;
			cp += प्र_लिखो(cp, "%d,", (पूर्णांक)ch);
			*cp++ = (i < nstates) ? SPACE : '\n';
		पूर्ण
	पूर्ण
	cp += प्र_लिखो(cp, "0, %d\n", KEY_MAP_VER);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस (पूर्णांक)(cp - buf);
पूर्ण

/*
 * This is called when a user changes the keymap parameter.
 */
अटल sमाप_प्रकार keymap_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i;
	sमाप_प्रकार ret = count;
	अक्षर *in_buff = शून्य;
	अक्षर *cp;
	u_अक्षर *cp1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	in_buff = kmemdup(buf, count + 1, GFP_ATOMIC);
	अगर (!in_buff) अणु
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस -ENOMEM;
	पूर्ण
	अगर (म_अक्षर("dDrR", *in_buff)) अणु
		spk_set_key_info(spk_key_शेषs, spk_key_buf);
		pr_info("keymap set to default values\n");
		kमुक्त(in_buff);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस count;
	पूर्ण
	अगर (in_buff[count - 1] == '\n')
		in_buff[count - 1] = '\0';
	cp = in_buff;
	cp1 = (u_अक्षर *)in_buff;
	क्रम (i = 0; i < 3; i++) अणु
		cp = spk_s2uअक्षर(cp, cp1);
		cp1++;
	पूर्ण
	i = (पूर्णांक)cp1[-2] + 1;
	i *= (पूर्णांक)cp1[-1] + 1;
	i += 2; /* 0 and last map ver */
	अगर (cp1[-3] != KEY_MAP_VER || cp1[-1] > 10 ||
	    i + SHIFT_TBL_SIZE + 4 >= माप(spk_key_buf)) अणु
		pr_warn("i %d %d %d %d\n", i,
			(पूर्णांक)cp1[-3], (पूर्णांक)cp1[-2], (पूर्णांक)cp1[-1]);
		kमुक्त(in_buff);
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस -EINVAL;
	पूर्ण
	जबतक (--i >= 0) अणु
		cp = spk_s2uअक्षर(cp, cp1);
		cp1++;
		अगर (!(*cp))
			अवरोध;
	पूर्ण
	अगर (i != 0 || cp1[-1] != KEY_MAP_VER || cp1[-2] != 0) अणु
		ret = -EINVAL;
		pr_warn("end %d %d %d %d\n", i,
			(पूर्णांक)cp1[-3], (पूर्णांक)cp1[-2], (पूर्णांक)cp1[-1]);
	पूर्ण अन्यथा अणु
		अगर (spk_set_key_info(in_buff, spk_key_buf)) अणु
			spk_set_key_info(spk_key_शेषs, spk_key_buf);
			ret = -EINVAL;
			pr_warn("set key failed\n");
		पूर्ण
	पूर्ण
	kमुक्त(in_buff);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस ret;
पूर्ण

/*
 * This is called when a user changes the value of the silent parameter.
 */
अटल sमाप_प्रकार silent_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक len;
	काष्ठा vc_data *vc = vc_cons[fg_console].d;
	अक्षर ch = 0;
	अक्षर shut;
	अचिन्हित दीर्घ flags;

	len = म_माप(buf);
	अगर (len > 0 && len < 3) अणु
		ch = buf[0];
		अगर (ch == '\n')
			ch = '0';
	पूर्ण
	अगर (ch < '0' || ch > '7') अणु
		pr_warn("silent value '%c' not in range (0,7)\n", ch);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (ch & 2) अणु
		shut = 1;
		spk_करो_flush();
	पूर्ण अन्यथा अणु
		shut = 0;
	पूर्ण
	अगर (ch & 4)
		shut |= 0x40;
	अगर (ch & 1)
		spk_shut_up |= shut;
	अन्यथा
		spk_shut_up &= ~shut;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस count;
पूर्ण

/*
 * This is called when a user पढ़ोs the synth setting.
 */
अटल sमाप_प्रकार synth_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक rv;

	अगर (!synth)
		rv = प्र_लिखो(buf, "%s\n", "none");
	अन्यथा
		rv = प्र_लिखो(buf, "%s\n", synth->name);
	वापस rv;
पूर्ण

/*
 * This is called when a user requests to change synthesizers.
 */
अटल sमाप_प्रकार synth_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक len;
	अक्षर new_synth_name[10];

	len = म_माप(buf);
	अगर (len < 2 || len > 9)
		वापस -EINVAL;
	स_नकल(new_synth_name, buf, len);
	अगर (new_synth_name[len - 1] == '\n')
		len--;
	new_synth_name[len] = '\0';
	spk_strlwr(new_synth_name);
	अगर (synth && !म_भेद(new_synth_name, synth->name)) अणु
		pr_warn("%s already in use\n", new_synth_name);
	पूर्ण अन्यथा अगर (synth_init(new_synth_name) != 0) अणु
		pr_warn("failed to init synth %s\n", new_synth_name);
		वापस -ENODEV;
	पूर्ण
	वापस count;
पूर्ण

/*
 * This is called when text is sent to the synth via the synth_direct file.
 */
अटल sमाप_प्रकार synth_direct_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u_अक्षर पंचांगp[256];
	पूर्णांक len;
	पूर्णांक bytes;
	स्थिर अक्षर *ptr = buf;
	अचिन्हित दीर्घ flags;

	अगर (!synth)
		वापस -EPERM;

	len = म_माप(buf);
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	जबतक (len > 0) अणु
		bytes = min_t(माप_प्रकार, len, 250);
		म_नकलन(पंचांगp, ptr, bytes);
		पंचांगp[bytes] = '\0';
		string_unescape_any_inplace(पंचांगp);
		synth_म_लिखो("%s", पंचांगp);
		ptr += bytes;
		len -= bytes;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस count;
पूर्ण

/*
 * This function is called when a user पढ़ोs the version.
 */
अटल sमाप_प्रकार version_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    अक्षर *buf)
अणु
	अक्षर *cp;

	cp = buf;
	cp += प्र_लिखो(cp, "Speakup version %s\n", SPEAKUP_VERSION);
	अगर (synth)
		cp += प्र_लिखो(cp, "%s synthesizer driver version %s\n",
		synth->name, synth->version);
	वापस cp - buf;
पूर्ण

/*
 * This is called when a user पढ़ोs the punctuation settings.
 */
अटल sमाप_प्रकार punc_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक i;
	अक्षर *cp = buf;
	काष्ठा st_var_header *p_header;
	काष्ठा punc_var_t *var;
	काष्ठा st_bits_data *pb;
	लघु mask;
	अचिन्हित दीर्घ flags;

	p_header = spk_var_header_by_name(attr->attr.name);
	अगर (!p_header) अणु
		pr_warn("p_header is null, attr->attr.name is %s\n",
			attr->attr.name);
		वापस -EINVAL;
	पूर्ण

	var = spk_get_punc_var(p_header->var_id);
	अगर (!var) अणु
		pr_warn("var is null, p_header->var_id is %i\n",
			p_header->var_id);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	pb = (काष्ठा st_bits_data *)&spk_punc_info[var->value];
	mask = pb->mask;
	क्रम (i = 33; i < 128; i++) अणु
		अगर (!(spk_अक्षरtab[i] & mask))
			जारी;
		*cp++ = (अक्षर)i;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस cp - buf;
पूर्ण

/*
 * This is called when a user changes the punctuation settings.
 */
अटल sमाप_प्रकार punc_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक x;
	काष्ठा st_var_header *p_header;
	काष्ठा punc_var_t *var;
	अक्षर punc_buf[100];
	अचिन्हित दीर्घ flags;

	x = म_माप(buf);
	अगर (x < 1 || x > 99)
		वापस -EINVAL;

	p_header = spk_var_header_by_name(attr->attr.name);
	अगर (!p_header) अणु
		pr_warn("p_header is null, attr->attr.name is %s\n",
			attr->attr.name);
		वापस -EINVAL;
	पूर्ण

	var = spk_get_punc_var(p_header->var_id);
	अगर (!var) अणु
		pr_warn("var is null, p_header->var_id is %i\n",
			p_header->var_id);
		वापस -EINVAL;
	पूर्ण

	स_नकल(punc_buf, buf, x);

	जबतक (x && punc_buf[x - 1] == '\n')
		x--;
	punc_buf[x] = '\0';

	spin_lock_irqsave(&speakup_info.spinlock, flags);

	अगर (*punc_buf == 'd' || *punc_buf == 'r')
		x = spk_set_mask_bits(शून्य, var->value, 3);
	अन्यथा
		x = spk_set_mask_bits(punc_buf, var->value, 3);

	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस count;
पूर्ण

/*
 * This function is called when a user पढ़ोs one of the variable parameters.
 */
sमाप_प्रकार spk_var_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		     अक्षर *buf)
अणु
	पूर्णांक rv = 0;
	काष्ठा st_var_header *param;
	काष्ठा var_t *var;
	अक्षर *cp1;
	अक्षर *cp;
	अक्षर ch;
	अचिन्हित दीर्घ flags;

	param = spk_var_header_by_name(attr->attr.name);
	अगर (!param)
		वापस -EINVAL;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	var = (काष्ठा var_t *)param->data;
	चयन (param->var_type) अणु
	हाल VAR_NUM:
	हाल VAR_TIME:
		अगर (var)
			rv = प्र_लिखो(buf, "%i\n", var->u.n.value);
		अन्यथा
			rv = प्र_लिखो(buf, "0\n");
		अवरोध;
	हाल VAR_STRING:
		अगर (var) अणु
			cp1 = buf;
			*cp1++ = '"';
			क्रम (cp = (अक्षर *)param->p_val; (ch = *cp); cp++) अणु
				अगर (ch >= ' ' && ch < '~')
					*cp1++ = ch;
				अन्यथा
					cp1 += प्र_लिखो(cp1, "\\x%02x", ch);
			पूर्ण
			*cp1++ = '"';
			*cp1++ = '\n';
			*cp1 = '\0';
			rv = cp1 - buf;
		पूर्ण अन्यथा अणु
			rv = प्र_लिखो(buf, "\"\"\n");
		पूर्ण
		अवरोध;
	शेष:
		rv = प्र_लिखो(buf, "Bad parameter  %s, type %i\n",
			     param->name, param->var_type);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(spk_var_show);

/*
 * Used to reset either शेष_pitch or शेष_vol.
 */
अटल अंतरभूत व्योम spk_reset_शेष_value(अक्षर *header_name,
					   पूर्णांक *synth_शेष_value, पूर्णांक idx)
अणु
	काष्ठा st_var_header *param;

	अगर (synth && synth_शेष_value) अणु
		param = spk_var_header_by_name(header_name);
		अगर (param)  अणु
			spk_set_num_var(synth_शेष_value[idx],
					param, E_NEW_DEFAULT);
			spk_set_num_var(0, param, E_DEFAULT);
			pr_info("%s reset to default value\n", param->name);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function is called when a user echos a value to one of the
 * variable parameters.
 */
sमाप_प्रकार spk_var_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा st_var_header *param;
	पूर्णांक ret;
	पूर्णांक len;
	अक्षर *cp;
	काष्ठा var_t *var_data;
	दीर्घ value;
	अचिन्हित दीर्घ flags;

	param = spk_var_header_by_name(attr->attr.name);
	अगर (!param)
		वापस -EINVAL;
	अगर (!param->data)
		वापस 0;
	ret = 0;
	cp = (अक्षर *)buf;
	string_unescape_any_inplace(cp);

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	चयन (param->var_type) अणु
	हाल VAR_NUM:
	हाल VAR_TIME:
		अगर (*cp == 'd' || *cp == 'r' || *cp == '\0')
			len = E_DEFAULT;
		अन्यथा अगर (*cp == '+' || *cp == '-')
			len = E_INC;
		अन्यथा
			len = E_SET;
		अगर (kम_से_दीर्घ(cp, 10, &value) == 0)
			ret = spk_set_num_var(value, param, len);
		अन्यथा
			pr_warn("overflow or parsing error has occurred");
		अगर (ret == -दुस्फल) अणु
			var_data = param->data;
			pr_warn("value for %s out of range, expect %d to %d\n",
				param->name,
				var_data->u.n.low, var_data->u.n.high);
		पूर्ण

	       /*
		* If voice was just changed, we might need to reset our शेष
		* pitch and volume.
		*/
		अगर (param->var_id == VOICE && synth &&
		    (ret == 0 || ret == -ERESTART)) अणु
			var_data = param->data;
			value = var_data->u.n.value;
			spk_reset_शेष_value("pitch", synth->शेष_pitch,
						value);
			spk_reset_शेष_value("vol", synth->शेष_vol,
						value);
		पूर्ण
		अवरोध;
	हाल VAR_STRING:
		len = म_माप(cp);
		अगर ((len >= 1) && (cp[len - 1] == '\n'))
			--len;
		अगर ((len >= 2) && (cp[0] == '"') && (cp[len - 1] == '"')) अणु
			++cp;
			len -= 2;
		पूर्ण
		cp[len] = '\0';
		ret = spk_set_string_var(cp, param, len);
		अगर (ret == -E2BIG)
			pr_warn("value too long for %s\n",
				param->name);
		अवरोध;
	शेष:
		pr_warn("%s unknown type %d\n",
			param->name, (पूर्णांक)param->var_type);
	अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);

	अगर (ret == -ERESTART)
		pr_info("%s reset to default value\n", param->name);
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(spk_var_store);

/*
 * Functions क्रम पढ़ोing and writing lists of i18n messages.  Incomplete.
 */

अटल sमाप_प्रकार message_show_helper(अक्षर *buf, क्रमागत msg_index_t first,
				   क्रमागत msg_index_t last)
अणु
	माप_प्रकार bufsize = PAGE_SIZE;
	अक्षर *buf_poपूर्णांकer = buf;
	पूर्णांक prपूर्णांकed;
	क्रमागत msg_index_t cursor;
	पूर्णांक index = 0;
	*buf_poपूर्णांकer = '\0'; /* buf_poपूर्णांकer always looking at a NUL byte. */

	क्रम (cursor = first; cursor <= last; cursor++, index++) अणु
		अगर (bufsize <= 1)
			अवरोध;
		prपूर्णांकed = scnम_लिखो(buf_poपूर्णांकer, bufsize, "%d\t%s\n",
				    index, spk_msg_get(cursor));
		buf_poपूर्णांकer += prपूर्णांकed;
		bufsize -= prपूर्णांकed;
	पूर्ण

	वापस buf_poपूर्णांकer - buf;
पूर्ण

अटल व्योम report_msg_status(पूर्णांक reset, पूर्णांक received, पूर्णांक used,
			      पूर्णांक rejected, अक्षर *groupname)
अणु
	पूर्णांक len;
	अक्षर buf[160];

	अगर (reset) अणु
		pr_info("i18n messages from group %s reset to defaults\n",
			groupname);
	पूर्ण अन्यथा अगर (received) अणु
		len = snम_लिखो(buf, माप(buf),
			       " updated %d of %d i18n messages from group %s\n",
				       used, received, groupname);
		अगर (rejected)
			snम_लिखो(buf + (len - 1), माप(buf) - (len - 1),
				 " with %d reject%s\n",
				 rejected, rejected > 1 ? "s" : "");
		pr_info("%s", buf);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार message_store_helper(स्थिर अक्षर *buf, माप_प्रकार count,
				    काष्ठा msg_group_t *group)
अणु
	अक्षर *cp = (अक्षर *)buf;
	अक्षर *end = cp + count;
	अक्षर *linefeed = शून्य;
	अक्षर *temp = शून्य;
	sमाप_प्रकार msg_stored = 0;
	sमाप_प्रकार retval = count;
	माप_प्रकार desc_length = 0;
	अचिन्हित दीर्घ index = 0;
	पूर्णांक received = 0;
	पूर्णांक used = 0;
	पूर्णांक rejected = 0;
	पूर्णांक reset = 0;
	क्रमागत msg_index_t firsपंचांगessage = group->start;
	क्रमागत msg_index_t lasपंचांगessage = group->end;
	क्रमागत msg_index_t curmessage;

	जबतक (cp < end) अणु
		जबतक ((cp < end) && (*cp == ' ' || *cp == '\t'))
			cp++;

		अगर (cp == end)
			अवरोध;
		अगर (म_अक्षर("dDrR", *cp)) अणु
			reset = 1;
			अवरोध;
		पूर्ण
		received++;

		linefeed = म_अक्षर(cp, '\n');
		अगर (!linefeed) अणु
			rejected++;
			अवरोध;
		पूर्ण

		अगर (!है_अंक(*cp)) अणु
			rejected++;
			cp = linefeed + 1;
			जारी;
		पूर्ण

		/*
		 * Do not replace with kम_से_अदीर्घ:
		 * here we need temp to be updated
		 */
		index = simple_म_से_अदीर्घ(cp, &temp, 10);

		जबतक ((temp < linefeed) && (*temp == ' ' || *temp == '\t'))
			temp++;

		desc_length = linefeed - temp;
		curmessage = firsपंचांगessage + index;

		/*
		 * Note the check (curmessage < firsपंचांगessage).  It is not
		 * redundant.  Suppose that the user gave us an index
		 * equal to अच_दीर्घ_उच्च - 1.  If firsपंचांगessage > 1, then
		 * firsपंचांगessage + index < firsपंचांगessage!
		 */

		अगर ((curmessage < firsपंचांगessage) || (curmessage > lasपंचांगessage)) अणु
			rejected++;
			cp = linefeed + 1;
			जारी;
		पूर्ण

		msg_stored = spk_msg_set(curmessage, temp, desc_length);
		अगर (msg_stored < 0) अणु
			retval = msg_stored;
			अगर (msg_stored == -ENOMEM)
				reset = 1;
			अवरोध;
		पूर्ण

		used++;

		cp = linefeed + 1;
	पूर्ण

	अगर (reset)
		spk_reset_msg_group(group);

	report_msg_status(reset, received, used, rejected, group->name);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार message_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार retval = 0;
	काष्ठा msg_group_t *group = spk_find_msg_group(attr->attr.name);
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!group))
		वापस -EINVAL;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	retval = message_show_helper(buf, group->start, group->end);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार message_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा msg_group_t *group = spk_find_msg_group(attr->attr.name);

	अगर (WARN_ON(!group))
		वापस -EINVAL;

	वापस message_store_helper(buf, count, group);
पूर्ण

/*
 * Declare the attributes.
 */
अटल काष्ठा kobj_attribute keymap_attribute =
	__ATTR_RW(keymap);
अटल काष्ठा kobj_attribute silent_attribute =
	__ATTR_WO(silent);
अटल काष्ठा kobj_attribute synth_attribute =
	__ATTR_RW(synth);
अटल काष्ठा kobj_attribute synth_direct_attribute =
	__ATTR_WO(synth_direct);
अटल काष्ठा kobj_attribute version_attribute =
	__ATTR_RO(version);

अटल काष्ठा kobj_attribute delimiters_attribute =
	__ATTR(delimiters, 0644, punc_show, punc_store);
अटल काष्ठा kobj_attribute ex_num_attribute =
	__ATTR(ex_num, 0644, punc_show, punc_store);
अटल काष्ठा kobj_attribute punc_all_attribute =
	__ATTR(punc_all, 0644, punc_show, punc_store);
अटल काष्ठा kobj_attribute punc_most_attribute =
	__ATTR(punc_most, 0644, punc_show, punc_store);
अटल काष्ठा kobj_attribute punc_some_attribute =
	__ATTR(punc_some, 0644, punc_show, punc_store);
अटल काष्ठा kobj_attribute repeats_attribute =
	__ATTR(repeats, 0644, punc_show, punc_store);

अटल काष्ठा kobj_attribute attrib_bleep_attribute =
	__ATTR(attrib_bleep, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute bell_pos_attribute =
	__ATTR(bell_pos, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute bleep_समय_attribute =
	__ATTR(bleep_समय, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute bleeps_attribute =
	__ATTR(bleeps, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute cursor_समय_attribute =
	__ATTR(cursor_समय, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute key_echo_attribute =
	__ATTR(key_echo, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute no_पूर्णांकerrupt_attribute =
	__ATTR(no_पूर्णांकerrupt, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute punc_level_attribute =
	__ATTR(punc_level, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute पढ़ोing_punc_attribute =
	__ATTR(पढ़ोing_punc, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute say_control_attribute =
	__ATTR(say_control, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute say_word_ctl_attribute =
	__ATTR(say_word_ctl, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute spell_delay_attribute =
	__ATTR(spell_delay, 0644, spk_var_show, spk_var_store);

/*
 * These attributes are i18n related.
 */
अटल काष्ठा kobj_attribute announcements_attribute =
	__ATTR(announcements, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute अक्षरacters_attribute =
	__ATTR(अक्षरacters, 0644, अक्षरs_अक्षरtab_show,
	       अक्षरs_अक्षरtab_store);
अटल काष्ठा kobj_attribute अक्षरtab_attribute =
	__ATTR(अक्षरtab, 0644, अक्षरs_अक्षरtab_show,
	       अक्षरs_अक्षरtab_store);
अटल काष्ठा kobj_attribute ctl_keys_attribute =
	__ATTR(ctl_keys, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute colors_attribute =
	__ATTR(colors, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute क्रमmatted_attribute =
	__ATTR(क्रमmatted, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute function_names_attribute =
	__ATTR(function_names, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute key_names_attribute =
	__ATTR(key_names, 0644, message_show, message_store);
अटल काष्ठा kobj_attribute states_attribute =
	__ATTR(states, 0644, message_show, message_store);

/*
 * Create groups of attributes so that we can create and destroy them all
 * at once.
 */
अटल काष्ठा attribute *मुख्य_attrs[] = अणु
	&keymap_attribute.attr,
	&silent_attribute.attr,
	&synth_attribute.attr,
	&synth_direct_attribute.attr,
	&version_attribute.attr,
	&delimiters_attribute.attr,
	&ex_num_attribute.attr,
	&punc_all_attribute.attr,
	&punc_most_attribute.attr,
	&punc_some_attribute.attr,
	&repeats_attribute.attr,
	&attrib_bleep_attribute.attr,
	&bell_pos_attribute.attr,
	&bleep_समय_attribute.attr,
	&bleeps_attribute.attr,
	&cursor_समय_attribute.attr,
	&key_echo_attribute.attr,
	&no_पूर्णांकerrupt_attribute.attr,
	&punc_level_attribute.attr,
	&पढ़ोing_punc_attribute.attr,
	&say_control_attribute.attr,
	&say_word_ctl_attribute.attr,
	&spell_delay_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *i18n_attrs[] = अणु
	&announcements_attribute.attr,
	&अक्षरacters_attribute.attr,
	&अक्षरtab_attribute.attr,
	&ctl_keys_attribute.attr,
	&colors_attribute.attr,
	&क्रमmatted_attribute.attr,
	&function_names_attribute.attr,
	&key_names_attribute.attr,
	&states_attribute.attr,
	शून्य,
पूर्ण;

/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specअगरy a name, a subdirectory will be
 * created क्रम the attributes with the directory being the name of the
 * attribute group.
 */
अटल स्थिर काष्ठा attribute_group मुख्य_attr_group = अणु
	.attrs = मुख्य_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group i18n_attr_group = अणु
	.attrs = i18n_attrs,
	.name = "i18n",
पूर्ण;

अटल काष्ठा kobject *accessibility_kobj;
काष्ठा kobject *speakup_kobj;

पूर्णांक speakup_kobj_init(व्योम)
अणु
	पूर्णांक retval;

	/*
	 * Create a simple kobject with the name of "accessibility",
	 * located under /sys/
	 *
	 * As this is a simple directory, no uevent will be sent to
	 * userspace.  That is why this function should not be used क्रम
	 * any type of dynamic kobjects, where the name and number are
	 * not known ahead of समय.
	 */
	accessibility_kobj = kobject_create_and_add("accessibility", शून्य);
	अगर (!accessibility_kobj) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	speakup_kobj = kobject_create_and_add("speakup", accessibility_kobj);
	अगर (!speakup_kobj) अणु
		retval = -ENOMEM;
		जाओ err_acc;
	पूर्ण

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(speakup_kobj, &मुख्य_attr_group);
	अगर (retval)
		जाओ err_speakup;

	retval = sysfs_create_group(speakup_kobj, &i18n_attr_group);
	अगर (retval)
		जाओ err_group;

	जाओ out;

err_group:
	sysfs_हटाओ_group(speakup_kobj, &मुख्य_attr_group);
err_speakup:
	kobject_put(speakup_kobj);
err_acc:
	kobject_put(accessibility_kobj);
out:
	वापस retval;
पूर्ण

व्योम speakup_kobj_निकास(व्योम)
अणु
	sysfs_हटाओ_group(speakup_kobj, &i18n_attr_group);
	sysfs_हटाओ_group(speakup_kobj, &मुख्य_attr_group);
	kobject_put(speakup_kobj);
	kobject_put(accessibility_kobj);
पूर्ण
