<शैली गुरु>
#अगर_अघोषित LIBURING_BARRIER_H
#घोषणा LIBURING_BARRIER_H

#अगर defined(__x86_64) || defined(__i386__)
#घोषणा पढ़ो_barrier()	__यंत्र__ __अस्थिर__("":::"memory")
#घोषणा ग_लिखो_barrier()	__यंत्र__ __अस्थिर__("":::"memory")
#अन्यथा
/*
 * Add arch appropriate definitions. Be safe and use full barriers क्रम
 * archs we करोn't have support क्रम.
 */
#घोषणा पढ़ो_barrier()	__sync_synchronize()
#घोषणा ग_लिखो_barrier()	__sync_synchronize()
#पूर्ण_अगर

#पूर्ण_अगर
