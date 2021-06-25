<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BARRIERS_H
#घोषणा BARRIERS_H

#घोषणा barrier() __यंत्र__ __अस्थिर__("" : : : "memory")

#अगर_घोषित RUN
#घोषणा smp_mb() __sync_synchronize()
#घोषणा smp_mb__after_unlock_lock() __sync_synchronize()
#अन्यथा
/*
 * Copied from CBMC's implementation of __sync_synchronize(), which
 * seems to be disabled by शेष.
 */
#घोषणा smp_mb() __CPROVER_fence("WWfence", "RRfence", "RWfence", "WRfence", \
				 "WWcumul", "RRcumul", "RWcumul", "WRcumul")
#घोषणा smp_mb__after_unlock_lock() __CPROVER_fence("WWfence", "RRfence", "RWfence", "WRfence", \
				    "WWcumul", "RRcumul", "RWcumul", "WRcumul")
#पूर्ण_अगर

/*
 * Allow memory barriers to be disabled in either the पढ़ो or ग_लिखो side
 * of SRCU inभागidually.
 */

#अगर_अघोषित NO_SYNC_SMP_MB
#घोषणा sync_smp_mb() smp_mb()
#अन्यथा
#घोषणा sync_smp_mb() करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित NO_READ_SIDE_SMP_MB
#घोषणा rs_smp_mb() smp_mb()
#अन्यथा
#घोषणा rs_smp_mb() करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा READ_ONCE(x) (*(अस्थिर typeof(x) *) &(x))
#घोषणा WRITE_ONCE(x) ((*(अस्थिर typeof(x) *) &(x)) = (val))

#पूर्ण_अगर
