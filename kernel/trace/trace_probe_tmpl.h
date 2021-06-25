<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Traceprobe fetch helper अंतरभूतs
 */

अटल nokprobe_अंतरभूत व्योम
fetch_store_raw(अचिन्हित दीर्घ val, काष्ठा fetch_insn *code, व्योम *buf)
अणु
	चयन (code->size) अणु
	हाल 1:
		*(u8 *)buf = (u8)val;
		अवरोध;
	हाल 2:
		*(u16 *)buf = (u16)val;
		अवरोध;
	हाल 4:
		*(u32 *)buf = (u32)val;
		अवरोध;
	हाल 8:
		//TBD: 32bit चिन्हित
		*(u64 *)buf = (u64)val;
		अवरोध;
	शेष:
		*(अचिन्हित दीर्घ *)buf = val;
	पूर्ण
पूर्ण

अटल nokprobe_अंतरभूत व्योम
fetch_apply_bitfield(काष्ठा fetch_insn *code, व्योम *buf)
अणु
	चयन (code->basesize) अणु
	हाल 1:
		*(u8 *)buf <<= code->lshअगरt;
		*(u8 *)buf >>= code->rshअगरt;
		अवरोध;
	हाल 2:
		*(u16 *)buf <<= code->lshअगरt;
		*(u16 *)buf >>= code->rshअगरt;
		अवरोध;
	हाल 4:
		*(u32 *)buf <<= code->lshअगरt;
		*(u32 *)buf >>= code->rshअगरt;
		अवरोध;
	हाल 8:
		*(u64 *)buf <<= code->lshअगरt;
		*(u64 *)buf >>= code->rshअगरt;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * These functions must be defined क्रम each callsite.
 * Return consumed dynamic data size (>= 0), or error (< 0).
 * If dest is शून्य, करोn't store result and वापस required dynamic data size.
 */
अटल पूर्णांक
process_fetch_insn(काष्ठा fetch_insn *code, काष्ठा pt_regs *regs,
		   व्योम *dest, व्योम *base);
अटल nokprobe_अंतरभूत पूर्णांक fetch_store_म_माप(अचिन्हित दीर्घ addr);
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base);
अटल nokprobe_अंतरभूत पूर्णांक fetch_store_म_माप_user(अचिन्हित दीर्घ addr);
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string_user(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base);
अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो(व्योम *dest, व्योम *src, माप_प्रकार size);
अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो_user(व्योम *dest, व्योम *src, माप_प्रकार size);

/* From the 2nd stage, routine is same */
अटल nokprobe_अंतरभूत पूर्णांक
process_fetch_insn_bottom(काष्ठा fetch_insn *code, अचिन्हित दीर्घ val,
			   व्योम *dest, व्योम *base)
अणु
	काष्ठा fetch_insn *s3 = शून्य;
	पूर्णांक total = 0, ret = 0, i = 0;
	u32 loc = 0;
	अचिन्हित दीर्घ lval = val;

stage2:
	/* 2nd stage: dereference memory अगर needed */
	करो अणु
		अगर (code->op == FETCH_OP_DEREF) अणु
			lval = val;
			ret = probe_mem_पढ़ो(&val, (व्योम *)val + code->offset,
					     माप(val));
		पूर्ण अन्यथा अगर (code->op == FETCH_OP_UDEREF) अणु
			lval = val;
			ret = probe_mem_पढ़ो_user(&val,
				 (व्योम *)val + code->offset, माप(val));
		पूर्ण अन्यथा
			अवरोध;
		अगर (ret)
			वापस ret;
		code++;
	पूर्ण जबतक (1);

	s3 = code;
stage3:
	/* 3rd stage: store value to buffer */
	अगर (unlikely(!dest)) अणु
		अगर (code->op == FETCH_OP_ST_STRING) अणु
			ret = fetch_store_म_माप(val + code->offset);
			code++;
			जाओ array;
		पूर्ण अन्यथा अगर (code->op == FETCH_OP_ST_USTRING) अणु
			ret += fetch_store_म_माप_user(val + code->offset);
			code++;
			जाओ array;
		पूर्ण अन्यथा
			वापस -EILSEQ;
	पूर्ण

	चयन (code->op) अणु
	हाल FETCH_OP_ST_RAW:
		fetch_store_raw(val, code, dest);
		अवरोध;
	हाल FETCH_OP_ST_MEM:
		probe_mem_पढ़ो(dest, (व्योम *)val + code->offset, code->size);
		अवरोध;
	हाल FETCH_OP_ST_UMEM:
		probe_mem_पढ़ो_user(dest, (व्योम *)val + code->offset, code->size);
		अवरोध;
	हाल FETCH_OP_ST_STRING:
		loc = *(u32 *)dest;
		ret = fetch_store_string(val + code->offset, dest, base);
		अवरोध;
	हाल FETCH_OP_ST_USTRING:
		loc = *(u32 *)dest;
		ret = fetch_store_string_user(val + code->offset, dest, base);
		अवरोध;
	शेष:
		वापस -EILSEQ;
	पूर्ण
	code++;

	/* 4th stage: modअगरy stored value अगर needed */
	अगर (code->op == FETCH_OP_MOD_BF) अणु
		fetch_apply_bitfield(code, dest);
		code++;
	पूर्ण

array:
	/* the last stage: Loop on array */
	अगर (code->op == FETCH_OP_LP_ARRAY) अणु
		total += ret;
		अगर (++i < code->param) अणु
			code = s3;
			अगर (s3->op != FETCH_OP_ST_STRING &&
			    s3->op != FETCH_OP_ST_USTRING) अणु
				dest += s3->size;
				val += s3->size;
				जाओ stage3;
			पूर्ण
			code--;
			val = lval + माप(अक्षर *);
			अगर (dest) अणु
				dest += माप(u32);
				*(u32 *)dest = update_data_loc(loc, ret);
			पूर्ण
			जाओ stage2;
		पूर्ण
		code++;
		ret = total;
	पूर्ण

	वापस code->op == FETCH_OP_END ? ret : -EILSEQ;
पूर्ण

/* Sum up total data length क्रम dynamic arrays (strings) */
अटल nokprobe_अंतरभूत पूर्णांक
__get_data_size(काष्ठा trace_probe *tp, काष्ठा pt_regs *regs)
अणु
	काष्ठा probe_arg *arg;
	पूर्णांक i, len, ret = 0;

	क्रम (i = 0; i < tp->nr_args; i++) अणु
		arg = tp->args + i;
		अगर (unlikely(arg->dynamic)) अणु
			len = process_fetch_insn(arg->code, regs, शून्य, शून्य);
			अगर (len > 0)
				ret += len;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* Store the value of each argument */
अटल nokprobe_अंतरभूत व्योम
store_trace_args(व्योम *data, काष्ठा trace_probe *tp, काष्ठा pt_regs *regs,
		 पूर्णांक header_size, पूर्णांक maxlen)
अणु
	काष्ठा probe_arg *arg;
	व्योम *base = data - header_size;
	व्योम *dyndata = data + tp->size;
	u32 *dl;	/* Data location */
	पूर्णांक ret, i;

	क्रम (i = 0; i < tp->nr_args; i++) अणु
		arg = tp->args + i;
		dl = data + arg->offset;
		/* Poपूर्णांक the dynamic data area अगर needed */
		अगर (unlikely(arg->dynamic))
			*dl = make_data_loc(maxlen, dyndata - base);
		ret = process_fetch_insn(arg->code, regs, dl, base);
		अगर (unlikely(ret < 0 && arg->dynamic)) अणु
			*dl = make_data_loc(0, dyndata - base);
		पूर्ण अन्यथा अणु
			dyndata += ret;
			maxlen -= ret;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
prपूर्णांक_probe_args(काष्ठा trace_seq *s, काष्ठा probe_arg *args, पूर्णांक nr_args,
		 u8 *data, व्योम *field)
अणु
	व्योम *p;
	पूर्णांक i, j;

	क्रम (i = 0; i < nr_args; i++) अणु
		काष्ठा probe_arg *a = args + i;

		trace_seq_म_लिखो(s, " %s=", a->name);
		अगर (likely(!a->count)) अणु
			अगर (!a->type->prपूर्णांक(s, data + a->offset, field))
				वापस -ENOMEM;
			जारी;
		पूर्ण
		trace_seq_अ_दो(s, '{');
		p = data + a->offset;
		क्रम (j = 0; j < a->count; j++) अणु
			अगर (!a->type->prपूर्णांक(s, p, field))
				वापस -ENOMEM;
			trace_seq_अ_दो(s, j == a->count - 1 ? '}' : ',');
			p += a->type->size;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
