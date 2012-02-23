/*-
 * Copyright 2003-2011 Netlogic Microsystems (Netlogic). All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Netlogic Microsystems ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * NETLOGIC_BSD
 * $FreeBSD$
 */

#ifndef __NLM_BOARD_H__
#define __NLM_BOARD_H__

#define	XLP_NAE_NBLOCKS		5
#define	XLP_NAE_NPORTS		4
#define	XLP_I2C_MAXDEVICES	8

/*
 * EVP board EEPROM info
 */
#define	EEPROM_I2CBUS		1
#define	EEPROM_I2CADDR		0xAE
#define	EEPROM_SIZE	 	48
#define	EEPROM_MACADDR_OFFSET	2

#if !defined(LOCORE) && !defined(__ASSEMBLY__)

struct xlp_port_ivars {
	int	port;
	int	block;
	int	type;
	int	phy_addr;
};

struct xlp_block_ivars {
	int	block;
	int	type;
	u_int	portmask;
	struct xlp_port_ivars	port_ivars[XLP_NAE_NPORTS];
};

struct xlp_nae_ivars {
	int 	node;
	u_int	blockmask;
	struct xlp_block_ivars	block_ivars[XLP_NAE_NBLOCKS];
};

struct xlp_board_info {
	u_int	nodemask;
	struct xlp_node_info {
		struct xlp_nae_ivars	nae_ivars;
	} nodes[XLP_MAX_NODES];
};

int nlm_board_info_setup(void);

int nlm_board_eeprom_read(int i2cbus, int addr, int offs, uint8_t *buf,int sz);
uint64_t nlm_board_cpld_base(int node, int chipselect);
int nlm_board_cpld_majorversion(uint64_t cpldbase);
int nlm_board_cpld_minorversion(uint64_t cpldbase);
void nlm_board_cpld_reset(uint64_t cpldbase);
int nlm_board_cpld_dboard_type(uint64_t cpldbase, int slot);
#endif

#endif
