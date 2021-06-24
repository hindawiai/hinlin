<शैली गुरु>
/*
 * arch/arm/mach-omap1/include/mach/पन.स
 *
 * IO definitions क्रम TI OMAP processors and boards
 *
 * Copied from arch/arm/mach-sa1100/include/mach/पन.स
 * Copyright (C) 1997-1999 Russell King
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Modअगरications:
 *  06-12-1997	RMK	Created.
 *  07-04-1999	RMK	Major cleanup
 */

#अगर_अघोषित __ASM_ARM_ARCH_IO_H
#घोषणा __ASM_ARM_ARCH_IO_H

#घोषणा IO_SPACE_LIMIT 0xffffffff

/*
 * We करोn't actually have real ISA nor PCI buses, but there is so many
 * drivers out there that might just work अगर we fake them...
 */
#घोषणा __io(a)		__typesafe_io(a)

#पूर्ण_अगर
