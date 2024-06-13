# HECI Tool

## Overview

The HECI Tool communicates with the HECI using the HECI protocol. This tool demonstrates how communication with the HECI protocol works and provides insights into its functionalities.

## Background

The HECI protocol's GUID was discovered through reverse-engineering FPT.efi. By hooking multiple functions that FPT.efi calls, a general structure for most FPT versions was identified. Initially, the tool locates various shell and HII related protocols, followed by locating the EFI_PCI_ROOT_BRIDGE_IO protocol and the HECI protocol.

## Insights and Findings

- Protocol Check: The tool primarily checks for the existence of the HECI protocol.
- MMIO Operations: After locating the HECI protocol, the tool proceeds with MMIO reads and writes.
- Error Handling: Removing the HECI protocol completely results in ```Error 51: Could not access PCI device```.
- Completely overriding the protocol in memory causes FPT to freeze.
- Protocol Modifications: Modifying the protocol to return specific statuses such as ```ME_NOT_READY``` and ```ME_MODE_FAILED``` does not impact FPT functionality.
- Impact on FPT: To affect FPT's functionality (e.g., unlocking FPT write access), modifications would likely need to target MMIO rather than the protocol itself.

## Usage

This tool provides a framework for understanding and experimenting with the HECI protocol's communication. It showcases the available functions and their responses, particularly focusing on ME Status and ME Mode, which appear to be the only functions that return meaningful results. Although the tool supports additional functionalities, they tend to return device errors, potentially due to permission issues.
