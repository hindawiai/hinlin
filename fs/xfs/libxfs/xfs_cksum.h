<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XFS_CKSUM_H
#घोषणा _XFS_CKSUM_H 1

#घोषणा XFS_CRC_SEED	(~(uपूर्णांक32_t)0)

/*
 * Calculate the पूर्णांकermediate checksum क्रम a buffer that has the CRC field
 * inside it.  The offset of the 32bit crc fields is passed as the
 * cksum_offset parameter. We करो not modअगरy the buffer during verअगरication,
 * hence we have to split the CRC calculation across the cksum_offset.
 */
अटल अंतरभूत uपूर्णांक32_t
xfs_start_cksum_safe(अक्षर *buffer, माप_प्रकार length, अचिन्हित दीर्घ cksum_offset)
अणु
	uपूर्णांक32_t zero = 0;
	uपूर्णांक32_t crc;

	/* Calculate CRC up to the checksum. */
	crc = crc32c(XFS_CRC_SEED, buffer, cksum_offset);

	/* Skip checksum field */
	crc = crc32c(crc, &zero, माप(__u32));

	/* Calculate the rest of the CRC. */
	वापस crc32c(crc, &buffer[cksum_offset + माप(__be32)],
		      length - (cksum_offset + माप(__be32)));
पूर्ण

/*
 * Fast CRC method where the buffer is modअगरied. Callers must have exclusive
 * access to the buffer जबतक the calculation takes place.
 */
अटल अंतरभूत uपूर्णांक32_t
xfs_start_cksum_update(अक्षर *buffer, माप_प्रकार length, अचिन्हित दीर्घ cksum_offset)
अणु
	/* zero the CRC field */
	*(__le32 *)(buffer + cksum_offset) = 0;

	/* single pass CRC calculation क्रम the entire buffer */
	वापस crc32c(XFS_CRC_SEED, buffer, length);
पूर्ण

/*
 * Convert the पूर्णांकermediate checksum to the final ondisk क्रमmat.
 *
 * The CRC32c calculation uses LE क्रमmat even on BE machines, but वापसs the
 * result in host endian क्रमmat. Hence we need to byte swap it back to LE क्रमmat
 * so that it is consistent on disk.
 */
अटल अंतरभूत __le32
xfs_end_cksum(uपूर्णांक32_t crc)
अणु
	वापस ~cpu_to_le32(crc);
पूर्ण

/*
 * Helper to generate the checksum क्रम a buffer.
 *
 * This modअगरies the buffer temporarily - callers must have exclusive
 * access to the buffer जबतक the calculation takes place.
 */
अटल अंतरभूत व्योम
xfs_update_cksum(अक्षर *buffer, माप_प्रकार length, अचिन्हित दीर्घ cksum_offset)
अणु
	uपूर्णांक32_t crc = xfs_start_cksum_update(buffer, length, cksum_offset);

	*(__le32 *)(buffer + cksum_offset) = xfs_end_cksum(crc);
पूर्ण

/*
 * Helper to verअगरy the checksum क्रम a buffer.
 */
अटल अंतरभूत पूर्णांक
xfs_verअगरy_cksum(अक्षर *buffer, माप_प्रकार length, अचिन्हित दीर्घ cksum_offset)
अणु
	uपूर्णांक32_t crc = xfs_start_cksum_safe(buffer, length, cksum_offset);

	वापस *(__le32 *)(buffer + cksum_offset) == xfs_end_cksum(crc);
पूर्ण

#पूर्ण_अगर /* _XFS_CKSUM_H */
