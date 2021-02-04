cerberus_pfm_id = {}
result = {}
cerberus_data = {'status_code': 0, 'stderr': '', 'stdout': 'No valid PFM found for port 0, region 1\n\n'}
cerberus_pfm_id["ActiveIdentifier"] = 150

if "ActiveIdentifier" not in cerberus_pfm_id:
    print("Key is there")
else:
    result["Return Message"] = cerberus_data["stdout"]


print(result)