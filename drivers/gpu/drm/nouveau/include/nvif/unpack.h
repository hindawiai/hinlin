<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_UNPACK_H__
#घोषणा __NVIF_UNPACK_H__

#घोषणा nvअगर_unvers(r,d,s,m) (अणु                                                \
	व्योम **_data = (d); __u32 *_size = (s); पूर्णांक _ret = (r);                \
	अगर (_ret == -ENOSYS && *_size == माप(m)) अणु                          \
		*_data = शून्य;                                                 \
		*_size = _ret = 0;                                             \
	पूर्ण                                                                      \
	_ret;                                                                  \
पूर्ण)

#घोषणा nvअगर_unpack(r,d,s,m,vl,vh,x) (अणु                                        \
	व्योम **_data = (d); __u32 *_size = (s);                                \
	पूर्णांक _ret = (r), _vl = (vl), _vh = (vh);                                \
	अगर (_ret == -ENOSYS && *_size >= माप(m) &&                          \
	    (m).version >= _vl && (m).version <= _vh) अणु                        \
		*_data = (__u8 *)*_data + माप(m);                           \
		*_size = *_size - माप(m);                                   \
		अगर (_ret = 0, !(x)) अणु                                          \
			_ret = *_size ? -E2BIG : 0;                            \
			*_data = शून्य;                                         \
			*_size = 0;                                            \
		पूर्ण                                                              \
	पूर्ण                                                                      \
	_ret;                                                                  \
पूर्ण)
#पूर्ण_अगर
