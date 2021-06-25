<शैली गुरु>
/*
 * Copyright (C) 2016 Red Hat
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 */

#घोषणा DEBUG /* क्रम pr_debug() */

#समावेश <मानकतर्क.स>

#समावेश <linux/पन.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>

/*
 * __drm_debug: Enable debug output.
 * Biपंचांगask of DRM_UT_x. See include/drm/drm_prपूर्णांक.h क्रम details.
 */
अचिन्हित पूर्णांक __drm_debug;
EXPORT_SYMBOL(__drm_debug);

MODULE_PARM_DESC(debug, "Enable debug output, where each bit enables a debug category.\n"
"\t\tBit 0 (0x01)  will enable CORE messages (drm core code)\n"
"\t\tBit 1 (0x02)  will enable DRIVER messages (drm controller code)\n"
"\t\tBit 2 (0x04)  will enable KMS messages (modesetting code)\n"
"\t\tBit 3 (0x08)  will enable PRIME messages (prime code)\n"
"\t\tBit 4 (0x10)  will enable ATOMIC messages (atomic code)\n"
"\t\tBit 5 (0x20)  will enable VBL messages (vblank code)\n"
"\t\tBit 7 (0x80)  will enable LEASE messages (leasing code)\n"
"\t\tBit 8 (0x100) will enable DP messages (displayport code)");
module_param_named(debug, __drm_debug, पूर्णांक, 0600);

व्योम __drm_माला_दो_coredump(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str)
अणु
	काष्ठा drm_prपूर्णांक_iterator *iterator = p->arg;
	sमाप_प्रकार len;

	अगर (!iterator->reमुख्य)
		वापस;

	अगर (iterator->offset < iterator->start) अणु
		sमाप_प्रकार copy;

		len = म_माप(str);

		अगर (iterator->offset + len <= iterator->start) अणु
			iterator->offset += len;
			वापस;
		पूर्ण

		copy = len - (iterator->start - iterator->offset);

		अगर (copy > iterator->reमुख्य)
			copy = iterator->reमुख्य;

		/* Copy out the bit of the string that we need */
		स_नकल(iterator->data,
			str + (iterator->start - iterator->offset), copy);

		iterator->offset = iterator->start + copy;
		iterator->reमुख्य -= copy;
	पूर्ण अन्यथा अणु
		sमाप_प्रकार pos = iterator->offset - iterator->start;

		len = min_t(sमाप_प्रकार, म_माप(str), iterator->reमुख्य);

		स_नकल(iterator->data + pos, str, len);

		iterator->offset += len;
		iterator->reमुख्य -= len;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__drm_माला_दो_coredump);

व्योम __drm_म_लिखोn_coredump(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	काष्ठा drm_prपूर्णांक_iterator *iterator = p->arg;
	माप_प्रकार len;
	अक्षर *buf;

	अगर (!iterator->reमुख्य)
		वापस;

	/* Figure out how big the string will be */
	len = snम_लिखो(शून्य, 0, "%pV", vaf);

	/* This is the easiest path, we've alपढ़ोy advanced beyond the offset */
	अगर (iterator->offset + len <= iterator->start) अणु
		iterator->offset += len;
		वापस;
	पूर्ण

	/* Then check अगर we can directly copy पूर्णांकo the target buffer */
	अगर ((iterator->offset >= iterator->start) && (len < iterator->reमुख्य)) अणु
		sमाप_प्रकार pos = iterator->offset - iterator->start;

		snम_लिखो(((अक्षर *) iterator->data) + pos,
			iterator->reमुख्य, "%pV", vaf);

		iterator->offset += len;
		iterator->reमुख्य -= len;

		वापस;
	पूर्ण

	/*
	 * Finally, hit the slow path and make a temporary string to copy over
	 * using _drm_माला_दो_coredump
	 */
	buf = kदो_स्मृति(len + 1, GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY);
	अगर (!buf)
		वापस;

	snम_लिखो(buf, len + 1, "%pV", vaf);
	__drm_माला_दो_coredump(p, (स्थिर अक्षर *) buf);

	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL(__drm_म_लिखोn_coredump);

व्योम __drm_माला_दो_seq_file(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str)
अणु
	seq_माला_दो(p->arg, str);
पूर्ण
EXPORT_SYMBOL(__drm_माला_दो_seq_file);

व्योम __drm_म_लिखोn_seq_file(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	seq_म_लिखो(p->arg, "%pV", vaf);
पूर्ण
EXPORT_SYMBOL(__drm_म_लिखोn_seq_file);

व्योम __drm_म_लिखोn_info(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	dev_info(p->arg, "[" DRM_NAME "] %pV", vaf);
पूर्ण
EXPORT_SYMBOL(__drm_म_लिखोn_info);

व्योम __drm_म_लिखोn_debug(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	pr_debug("%s %pV", p->prefix, vaf);
पूर्ण
EXPORT_SYMBOL(__drm_म_लिखोn_debug);

व्योम __drm_म_लिखोn_err(काष्ठा drm_prपूर्णांकer *p, काष्ठा va_क्रमmat *vaf)
अणु
	pr_err("*ERROR* %s %pV", p->prefix, vaf);
पूर्ण
EXPORT_SYMBOL(__drm_म_लिखोn_err);

/**
 * drm_माला_दो - prपूर्णांक a स्थिर string to a &drm_prपूर्णांकer stream
 * @p: the &drm prपूर्णांकer
 * @str: स्थिर string
 *
 * Allow &drm_prपूर्णांकer types that have a स्थिरant string
 * option to use it.
 */
व्योम drm_माला_दो(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *str)
अणु
	अगर (p->माला_दो)
		p->माला_दो(p, str);
	अन्यथा
		drm_म_लिखो(p, "%s", str);
पूर्ण
EXPORT_SYMBOL(drm_माला_दो);

/**
 * drm_म_लिखो - prपूर्णांक to a &drm_prपूर्णांकer stream
 * @p: the &drm_prपूर्णांकer
 * @f: क्रमmat string
 */
व्योम drm_म_लिखो(काष्ठा drm_prपूर्णांकer *p, स्थिर अक्षर *f, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, f);
	drm_भ_लिखो(p, f, &args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(drm_म_लिखो);

/**
 * drm_prपूर्णांक_bits - prपूर्णांक bits to a &drm_prपूर्णांकer stream
 *
 * Prपूर्णांक bits (in flag fields क्रम example) in human पढ़ोable क्रमm.
 *
 * @p: the &drm_prपूर्णांकer
 * @value: field value.
 * @bits: Array with bit names.
 * @nbits: Size of bit names array.
 */
व्योम drm_prपूर्णांक_bits(काष्ठा drm_prपूर्णांकer *p, अचिन्हित दीर्घ value,
		    स्थिर अक्षर * स्थिर bits[], अचिन्हित पूर्णांक nbits)
अणु
	bool first = true;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON_ONCE(nbits > BITS_PER_TYPE(value)))
		nbits = BITS_PER_TYPE(value);

	क्रम_each_set_bit(i, &value, nbits) अणु
		अगर (WARN_ON_ONCE(!bits[i]))
			जारी;
		drm_म_लिखो(p, "%s%s", first ? "" : ",",
			   bits[i]);
		first = false;
	पूर्ण
	अगर (first)
		drm_म_लिखो(p, "(none)");
पूर्ण
EXPORT_SYMBOL(drm_prपूर्णांक_bits);

व्योम drm_dev_prपूर्णांकk(स्थिर काष्ठा device *dev, स्थिर अक्षर *level,
		    स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	अगर (dev)
		dev_prपूर्णांकk(level, dev, "[" DRM_NAME ":%ps] %pV",
			   __builtin_वापस_address(0), &vaf);
	अन्यथा
		prपूर्णांकk("%s" "[" DRM_NAME ":%ps] %pV",
		       level, __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(drm_dev_prपूर्णांकk);

व्योम drm_dev_dbg(स्थिर काष्ठा device *dev, क्रमागत drm_debug_category category,
		 स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!drm_debug_enabled(category))
		वापस;

	बहु_शुरू(args, क्रमmat);
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	अगर (dev)
		dev_prपूर्णांकk(KERN_DEBUG, dev, "[" DRM_NAME ":%ps] %pV",
			   __builtin_वापस_address(0), &vaf);
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "[" DRM_NAME ":%ps] %pV",
		       __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(drm_dev_dbg);

व्योम __drm_dbg(क्रमागत drm_debug_category category, स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!drm_debug_enabled(category))
		वापस;

	बहु_शुरू(args, क्रमmat);
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	prपूर्णांकk(KERN_DEBUG "[" DRM_NAME ":%ps] %pV",
	       __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__drm_dbg);

व्योम __drm_err(स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	prपूर्णांकk(KERN_ERR "[" DRM_NAME ":%ps] *ERROR* %pV",
	       __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__drm_err);

/**
 * drm_prपूर्णांक_regset32 - prपूर्णांक the contents of रेजिस्टरs to a
 * &drm_prपूर्णांकer stream.
 *
 * @p: the &drm prपूर्णांकer
 * @regset: the list of रेजिस्टरs to prपूर्णांक.
 *
 * Often in driver debug, it's useful to be able to either capture the
 * contents of रेजिस्टरs in the steady state using debugfs or at
 * specअगरic poपूर्णांकs during operation.  This lets the driver have a
 * single list of रेजिस्टरs क्रम both.
 */
व्योम drm_prपूर्णांक_regset32(काष्ठा drm_prपूर्णांकer *p, काष्ठा debugfs_regset32 *regset)
अणु
	पूर्णांक namelen = 0;
	पूर्णांक i;

	क्रम (i = 0; i < regset->nregs; i++)
		namelen = max(namelen, (पूर्णांक)म_माप(regset->regs[i].name));

	क्रम (i = 0; i < regset->nregs; i++) अणु
		drm_म_लिखो(p, "%*s = 0x%08x\n",
			   namelen, regset->regs[i].name,
			   पढ़ोl(regset->base + regset->regs[i].offset));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_prपूर्णांक_regset32);
