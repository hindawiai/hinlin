<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019-2020 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Helper functions to generate a raw byte sequence payload from values.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/v4l2-controls.h>

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/log2.h>

#समावेश "nal-rbsp.h"

व्योम rbsp_init(काष्ठा rbsp *rbsp, व्योम *addr, माप_प्रकार size,
	       काष्ठा nal_rbsp_ops *ops)
अणु
	अगर (!rbsp)
		वापस;

	rbsp->data = addr;
	rbsp->size = size;
	rbsp->pos = 0;
	rbsp->ops = ops;
	rbsp->error = 0;
पूर्ण

व्योम rbsp_unsupported(काष्ठा rbsp *rbsp)
अणु
	rbsp->error = -EINVAL;
पूर्ण

अटल पूर्णांक rbsp_पढ़ो_bits(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक *value);
अटल पूर्णांक rbsp_ग_लिखो_bits(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक value);

/*
 * When पढ़ोing or writing, the emulation_prevention_three_byte is detected
 * only when the 2 one bits need to be inserted. Thereक्रमe, we are not
 * actually adding the 0x3 byte, but the 2 one bits and the six 0 bits of the
 * next byte.
 */
#घोषणा EMULATION_PREVENTION_THREE_BYTE (0x3 << 6)

अटल पूर्णांक add_emulation_prevention_three_byte(काष्ठा rbsp *rbsp)
अणु
	rbsp->num_consecutive_zeros = 0;
	rbsp_ग_लिखो_bits(rbsp, 8, EMULATION_PREVENTION_THREE_BYTE);

	वापस 0;
पूर्ण

अटल पूर्णांक discard_emulation_prevention_three_byte(काष्ठा rbsp *rbsp)
अणु
	अचिन्हित पूर्णांक पंचांगp = 0;

	rbsp->num_consecutive_zeros = 0;
	rbsp_पढ़ो_bits(rbsp, 8, &पंचांगp);
	अगर (पंचांगp != EMULATION_PREVENTION_THREE_BYTE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rbsp_पढ़ो_bit(काष्ठा rbsp *rbsp)
अणु
	पूर्णांक shअगरt;
	पूर्णांक ofs;
	पूर्णांक bit;
	पूर्णांक err;

	अगर (rbsp->num_consecutive_zeros == 22) अणु
		err = discard_emulation_prevention_three_byte(rbsp);
		अगर (err)
			वापस err;
	पूर्ण

	shअगरt = 7 - (rbsp->pos % 8);
	ofs = rbsp->pos / 8;
	अगर (ofs >= rbsp->size)
		वापस -EINVAL;

	bit = (rbsp->data[ofs] >> shअगरt) & 1;

	rbsp->pos++;

	अगर (bit == 1 ||
	    (rbsp->num_consecutive_zeros < 7 && (rbsp->pos % 8 == 0)))
		rbsp->num_consecutive_zeros = 0;
	अन्यथा
		rbsp->num_consecutive_zeros++;

	वापस bit;
पूर्ण

अटल अंतरभूत पूर्णांक rbsp_ग_लिखो_bit(काष्ठा rbsp *rbsp, bool value)
अणु
	पूर्णांक shअगरt;
	पूर्णांक ofs;

	अगर (rbsp->num_consecutive_zeros == 22)
		add_emulation_prevention_three_byte(rbsp);

	shअगरt = 7 - (rbsp->pos % 8);
	ofs = rbsp->pos / 8;
	अगर (ofs >= rbsp->size)
		वापस -EINVAL;

	rbsp->data[ofs] &= ~(1 << shअगरt);
	rbsp->data[ofs] |= value << shअगरt;

	rbsp->pos++;

	अगर (value ||
	    (rbsp->num_consecutive_zeros < 7 && (rbsp->pos % 8 == 0))) अणु
		rbsp->num_consecutive_zeros = 0;
	पूर्ण अन्यथा अणु
		rbsp->num_consecutive_zeros++;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rbsp_पढ़ो_bits(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक i;
	पूर्णांक bit;
	अचिन्हित पूर्णांक पंचांगp = 0;

	अगर (n > 8 * माप(*value))
		वापस -EINVAL;

	क्रम (i = n; i > 0; i--) अणु
		bit = rbsp_पढ़ो_bit(rbsp);
		अगर (bit < 0)
			वापस bit;
		पंचांगp |= bit << (i - 1);
	पूर्ण

	अगर (value)
		*value = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_ग_लिखो_bits(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (n > 8 * माप(value))
		वापस -EINVAL;

	जबतक (n--) अणु
		ret = rbsp_ग_लिखो_bit(rbsp, (value >> n) & 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_पढ़ो_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक leading_zero_bits = 0;
	अचिन्हित पूर्णांक पंचांगp = 0;
	पूर्णांक ret;

	जबतक ((ret = rbsp_पढ़ो_bit(rbsp)) == 0)
		leading_zero_bits++;
	अगर (ret < 0)
		वापस ret;

	अगर (leading_zero_bits > 0) अणु
		ret = rbsp_पढ़ो_bits(rbsp, leading_zero_bits, &पंचांगp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (value)
		*value = (1 << leading_zero_bits) - 1 + पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_ग_लिखो_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret;
	पूर्णांक leading_zero_bits;

	अगर (!value)
		वापस -EINVAL;

	leading_zero_bits = ilog2(*value + 1);

	ret = rbsp_ग_लिखो_bits(rbsp, leading_zero_bits, 0);
	अगर (ret)
		वापस ret;

	वापस rbsp_ग_लिखो_bits(rbsp, leading_zero_bits + 1, *value + 1);
पूर्ण

अटल पूर्णांक rbsp_पढ़ो_sev(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;

	ret = rbsp_पढ़ो_uev(rbsp, &पंचांगp);
	अगर (ret)
		वापस ret;

	अगर (value) अणु
		अगर (पंचांगp & 1)
			*value = (पंचांगp + 1) / 2;
		अन्यथा
			*value = -(पंचांगp / 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rbsp_ग_लिखो_sev(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (!value)
		वापस -EINVAL;

	अगर (*value > 0)
		पंचांगp = (2 * (*value)) | 1;
	अन्यथा
		पंचांगp = -2 * (*value);

	वापस rbsp_ग_लिखो_uev(rbsp, &पंचांगp);
पूर्ण

अटल पूर्णांक __rbsp_ग_लिखो_bit(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	वापस rbsp_ग_लिखो_bit(rbsp, *value);
पूर्ण

अटल पूर्णांक __rbsp_ग_लिखो_bits(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक *value)
अणु
	वापस rbsp_ग_लिखो_bits(rbsp, n, *value);
पूर्ण

काष्ठा nal_rbsp_ops ग_लिखो = अणु
	.rbsp_bit = __rbsp_ग_लिखो_bit,
	.rbsp_bits = __rbsp_ग_लिखो_bits,
	.rbsp_uev = rbsp_ग_लिखो_uev,
	.rbsp_sev = rbsp_ग_लिखो_sev,
पूर्ण;

अटल पूर्णांक __rbsp_पढ़ो_bit(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	पूर्णांक पंचांगp = rbsp_पढ़ो_bit(rbsp);

	अगर (पंचांगp < 0)
		वापस पंचांगp;
	*value = पंचांगp;

	वापस 0;
पूर्ण

काष्ठा nal_rbsp_ops पढ़ो = अणु
	.rbsp_bit = __rbsp_पढ़ो_bit,
	.rbsp_bits = rbsp_पढ़ो_bits,
	.rbsp_uev = rbsp_पढ़ो_uev,
	.rbsp_sev = rbsp_पढ़ो_sev,
पूर्ण;

व्योम rbsp_bit(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	अगर (rbsp->error)
		वापस;
	rbsp->error = rbsp->ops->rbsp_bit(rbsp, value);
पूर्ण

व्योम rbsp_bits(काष्ठा rbsp *rbsp, पूर्णांक n, पूर्णांक *value)
अणु
	अगर (rbsp->error)
		वापस;
	rbsp->error = rbsp->ops->rbsp_bits(rbsp, n, value);
पूर्ण

व्योम rbsp_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *value)
अणु
	अगर (rbsp->error)
		वापस;
	rbsp->error = rbsp->ops->rbsp_uev(rbsp, value);
पूर्ण

व्योम rbsp_sev(काष्ठा rbsp *rbsp, पूर्णांक *value)
अणु
	अगर (rbsp->error)
		वापस;
	rbsp->error = rbsp->ops->rbsp_sev(rbsp, value);
पूर्ण

व्योम rbsp_trailing_bits(काष्ठा rbsp *rbsp)
अणु
	अचिन्हित पूर्णांक rbsp_stop_one_bit = 1;
	अचिन्हित पूर्णांक rbsp_alignment_zero_bit = 0;

	rbsp_bit(rbsp, &rbsp_stop_one_bit);
	rbsp_bits(rbsp, round_up(rbsp->pos, 8) - rbsp->pos,
		  &rbsp_alignment_zero_bit);
पूर्ण
