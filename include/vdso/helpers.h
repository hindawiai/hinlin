<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VDSO_HELPERS_H
#घोषणा __VDSO_HELPERS_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <vdso/datapage.h>

अटल __always_अंतरभूत u32 vdso_पढ़ो_begin(स्थिर काष्ठा vdso_data *vd)
अणु
	u32 seq;

	जबतक (unlikely((seq = READ_ONCE(vd->seq)) & 1))
		cpu_relax();

	smp_rmb();
	वापस seq;
पूर्ण

अटल __always_अंतरभूत u32 vdso_पढ़ो_retry(स्थिर काष्ठा vdso_data *vd,
					   u32 start)
अणु
	u32 seq;

	smp_rmb();
	seq = READ_ONCE(vd->seq);
	वापस seq != start;
पूर्ण

अटल __always_अंतरभूत व्योम vdso_ग_लिखो_begin(काष्ठा vdso_data *vd)
अणु
	/*
	 * WRITE_ONCE it is required otherwise the compiler can validly tear
	 * updates to vd[x].seq and it is possible that the value seen by the
	 * पढ़ोer it is inconsistent.
	 */
	WRITE_ONCE(vd[CS_HRES_COARSE].seq, vd[CS_HRES_COARSE].seq + 1);
	WRITE_ONCE(vd[CS_RAW].seq, vd[CS_RAW].seq + 1);
	smp_wmb();
पूर्ण

अटल __always_अंतरभूत व्योम vdso_ग_लिखो_end(काष्ठा vdso_data *vd)
अणु
	smp_wmb();
	/*
	 * WRITE_ONCE it is required otherwise the compiler can validly tear
	 * updates to vd[x].seq and it is possible that the value seen by the
	 * पढ़ोer it is inconsistent.
	 */
	WRITE_ONCE(vd[CS_HRES_COARSE].seq, vd[CS_HRES_COARSE].seq + 1);
	WRITE_ONCE(vd[CS_RAW].seq, vd[CS_RAW].seq + 1);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __VDSO_HELPERS_H */
