import React from "react";
import { View, Text, Pressable, StyleSheet } from "react-native";

export default function HomeScreen() {
	return (
		<View style={styles.container}>
			<View style={styles.buttonContainer}>
				<Pressable
					style={({ pressed }) => [
						styles.button,
						pressed && styles.buttonPressed,
					]}
					onPress={() => console.log("Minus")}
				>
					<Text style={styles.buttonText}>-</Text>
				</Pressable>

				<Pressable
					style={({ pressed }) => [
						styles.button,
						pressed && styles.buttonPressed,
					]}
					onPress={() => console.log("Plus")}
				>
					<Text style={styles.buttonText}>+</Text>
				</Pressable>
			</View>
		</View>
	);
}

const styles = StyleSheet.create({
	container: {
		flex: 1,
		justifyContent: "center",
		alignItems: "center",
	},
	buttonContainer: {
		flexDirection: "row",
		gap: 20,
	},
	button: {
		paddingVertical: 12,
		paddingHorizontal: 24,
		borderWidth: 2,
		borderColor: "#707070",
		borderRadius: 8,
		backgroundColor: "#e4e4e4",
		justifyContent: "center",
		alignItems: "center",
	},
	buttonPressed: {
		backgroundColor: "#c0c0c0",
		borderColor: "#505050",
	},
	buttonText: {
		fontSize: 24,
		fontWeight: "bold",
		color: "#707070",
	},
});
